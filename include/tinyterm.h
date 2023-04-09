#ifndef __TINYTERM__
#define __TINYTERM__

#include <stdint.h>
#include "tinyterm_config.h"

typedef struct tinyterm_command_s
{
    uint8_t* command;
    uint8_t* description;
    uint8_t* (*callback)(void*);
}tinyterm_command_t;

typedef struct tinyterm_s
{
    uint8_t inputbuffer[TINYTERM_MAX_BUFFER];
    uint8_t state;
    uint32_t pointer;

    tinyterm_command_t* commands;
    uint32_t commands_size;

    uint8_t currentReceiveState;
} tinyterm_t;



void tinyterm_init(tinyterm_t* term, tinyterm_command_t* commands, uint32_t commands_size);
int tinyterm_receive(tinyterm_t* term, uint8_t* value, uint16_t length);
void tinyterm_update(tinyterm_t* term);

#endif
