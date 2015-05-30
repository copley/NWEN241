#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tictactoe.h"

int init_game(int serverfd);
int check(int clientfd);
int player_move(int clientfd, int serverfd);
void print_game(int clientfd, int size);
void print_winner(int clientfd);

// implement a very simple client that sends and receives
// all other logic, just send and receive strings
// extension is to add extra clients
int main(void)
{
  // define our variables related to pipes
  int clientfd, serverfd;
  char *clientpipe = "clientpipe";
  char *serverpipe = "serverpipe";

  // create the FIFO (named pipe) and open for reading 
  mkfifo(clientpipe, 0666);
  mkfifo(serverpipe, 0666);
  serverfd = open(serverpipe, O_WRONLY);
  clientfd = open(clientpipe, O_RDONLY);

  printf("This is the game of Tic Tac Toe.\n");
  printf("You will be playing against the computer.\n");

  int done;  // used to check validity of move
  int game_over; // used to check if game has completed

  // client must send commands and wait for responses
  // client exits loop if game is over
  // client should continue if receives continue message

  // tidy up
  close(clientfd);
  unlink(clientpipe);

  return 0;
}

/* Start the game by telling server size of the board */
int init_game(int serverfd) 
{
  // ask the player
  // tell the server
  return size;
}

/* Send player's move to the server and check if was valid. */
int player_move(int clientfd, int serverfd)
{
  // ask the player
  // send the details
  // check the result
  return valid;
}

/* Display the game on the screen. */
void print_game(int clientfd, int size)
{
  // read and print the board one character at a time
}

/* Check whether game has ended or whether computer is waiting 
   for the next move */
int check(int clientfd) 
{
  // what does the server tell us? do we continue?
  // someone did win, so the game is over
  return TRUE;
}

/* Receive the final results from the server */
void print_winner(int clientfd)
{
}

