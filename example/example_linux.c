#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <tinyterm.h>
#include <pthread.h>
#include <ncurses.h>
#include "example_commands.h"
tinyterm_t terminal;



void *receive_thread(void *arg)
{
    // initialize ncurses
    // initscr();
    // cbreak();  // disable line buffering
    // noecho();  // disable echoing of typed characters

        // Save the current terminal settings
    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;

    // Disable canonical mode and echo
    new_tio.c_lflag &= (~ICANON & ~ECHO);

    // Apply the new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    while(1)
    {
        uint8_t c = getchar();
        putchar(c);
        tinyterm_receive(&terminal, &c, 1);
    }
}

pthread_t receiving_thread;
void start_receiving()
{
   // create a thread to receive data
   
   pthread_create(&receiving_thread, NULL, receive_thread, NULL);
   
   // start the thread
   
}



int main(int argc, char *argv[]) 
{

  printf("Starting loop (press i or q)...\n");

  tinyterm_init(&terminal, example_commands, EXAMPLE_COMMANDS_COUNT);

  start_receiving();

  while(1) {
    tinyterm_update(&terminal);
  }

  pthread_join(receiving_thread, NULL);
  return 0; 
}