#include <tinyterm.h>

#define EXAMPLE_COMMANDS_COUNT 2
extern const tinyterm_command_t example_commands[EXAMPLE_COMMANDS_COUNT];

uint8_t* example_help(void* args);

uint8_t* example_exit(void* args);


