#include "example_commands.h"

const tinyterm_command_t example_commands[EXAMPLE_COMMANDS_COUNT] = {
    {"help", "Prints this help message", example_help},
    {"exit", "Exits the program", example_exit}
};

uint8_t* example_help(void* args)
{
    printf("Help\n");
}

uint8_t* example_exit(void* args)
{
    printf("exiting...\n");
    exit(0);
}
