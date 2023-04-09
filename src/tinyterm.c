
#include "tinyterm.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**********************************************************
*           Private definitions
***********************************************************/

enum parse_states_e
{
    PARSE_STATE_NEW = 0,
    PARSE_STATE_VALUE,
    PARSE_STATE_SKIP
};

enum receive_states_e
{
    RECEIVE_STATE_RECEIVING = 0,
    RECEIVE_STATE_COMPLETE,
    RECEIVE_STATE_FULL_BUFFER
};

/**********************************************************
*           Private variables
***********************************************************/


/**********************************************************
*           Public variables
***********************************************************/

/**********************************************************
*           Private functions declaration
***********************************************************/

uint32_t handlecommands(tinyterm_t* term, const char* const input, char** command);

/**********************************************************
*           Public functions
***********************************************************/

void tinyterm_init(tinyterm_t* termz, tinyterm_command_t* commands, uint32_t commands_size)
{
    printf("Initializing tinyterm...\n");
    termz->pointer = 0;
    termz->currentReceiveState = RECEIVE_STATE_RECEIVING;
    termz->commands = commands;
    termz->commands_size = commands_size;
}

uint8_t received = 0;
int tinyterm_receive(tinyterm_t* term, uint8_t* value, uint16_t length)
{
    received +=1;
    if (term->currentReceiveState == RECEIVE_STATE_RECEIVING)
    {
        int res = 0;
        if (length < TINYTERM_MAX_BUFFER - term->pointer)
            memcpy(&term->inputbuffer[term->pointer], value, length);
        else 
            res = -1;

        if(res == 0)
        {
            term->pointer += length;
            term->inputbuffer[term->pointer] = 0;
            if (term->inputbuffer[term->pointer-1] == '\n')
            {
                term->currentReceiveState = RECEIVE_STATE_COMPLETE;
            }
            return 0;
        }
        else
        {
            // it exeeds the size of 
            term->currentReceiveState = RECEIVE_STATE_FULL_BUFFER;
        }
    }

    return -1;
}

void tinyterm_update(tinyterm_t* term)
{
    if (term->currentReceiveState == RECEIVE_STATE_COMPLETE)
    {
        printf("receving is completed!\n");
        uint8_t* command = 0;
        int len = handlecommands(term, &term->inputbuffer[0], &command);
        term->pointer = 0;
        term->currentReceiveState = RECEIVE_STATE_RECEIVING;
    }
    else if (term->currentReceiveState == RECEIVE_STATE_FULL_BUFFER)
    {
        printf("buffer is too full.\n");
        term->pointer = 0;
        term->currentReceiveState = RECEIVE_STATE_RECEIVING;
    }
}

/**********************************************************
*           Private functions definitions
***********************************************************/

uint32_t getword(const char* const input, uint32_t len, char** word)
{
    char* p = input;
    char** output = 0;
    enum parse_states_e state = PARSE_STATE_SKIP; 
    int res = 0;
    while(*p != 0 || p >= input + TINYTERM_MAX_BUFFER)
    {

            if(*p == ' ' | *p == '\n' | *p == '\t')
            {
                p++;
                continue;
            }
            else
            {
                state = PARSE_STATE_NEW;
                *word = (char*)p;
                break;
            }
    }        
            
    while(*p != 0 || p >= input + TINYTERM_MAX_BUFFER)
    {
        if(*p == ' ' | *p == '\n' | *p == '\t')
        {
            break;
        }
        else
        {
            p++;
            res++;
        }
    }
    return res;
}


int cmp(const void* a, const void* b, int len)
{
    const char* p = a;
    const char* q = b;
    for (int i = 0; i < len; i++)
    {
        if (p[i] != q[i])
            return 1;
    }
    return 0;
}

uint32_t handlecommands(tinyterm_t* term, const char* const input, char** command)
{
    enum parse_states_e state = PARSE_STATE_SKIP; 
    uint32_t res = 0;
    res = getword(input, TINYTERM_MAX_BUFFER, command);

    for (int i = 0; i < term->commands_size; i++)
    {
        printf("comparing %d\n", i);
        if (cmp(term->commands[i].command, *command, res) == 0)
        {
            term->commands[i].callback(0);
            break;
        }
    }

    return res;
}

