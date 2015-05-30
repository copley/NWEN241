#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tictactoe.h"

typedef struct TicTacToe
{
  int size;      // this is the size of the game board
  int **board;   // this is the game board
  int winner;    // who won the game
} TicTacToe;

int check(TicTacToe* game);
void init_game(TicTacToe* game, int size);
void free_game(TicTacToe *game);
int player_move(int serverfd, int clientfd, TicTacToe* game);
void computer_move(TicTacToe* game);
void print_game(int clientfd, TicTacToe game);
char tokenstr(int token);
void print_result(int clientfd, TicTacToe game);
void client_continue(int clientfd);

int main(void)
{
  // define our variables related to pipes
  int clientfd, serverfd;
  char *clientpipe = "clientpipe";
  char *serverpipe = "serverpipe";

  // create the FIFO (named pipe) and open for reading 
  mkfifo(serverpipe, 0666);
  mkfifo(clientpipe, 0666);
  serverfd = open(serverpipe, O_RDONLY); // client talks to server
  clientfd = open(clientpipe, O_WRONLY); // server talks to client

  printf("This is the game of Tic Tac Toe.\n");
  printf("You will be playing against the computer.\n");

  // wait for a client to tell us how large is the game board
  printf("The game board is %d by %d.\n",size, size);

  // initialise the board
  TicTacToe game;   
  init_game(&game,size); 
 
  // as for the generic solution with addition of pipes

  // clean up
  close(serverfd);
  unlink(serverpipe);
  free_game(&game);
  return 0;
}

/* Initialize the matrix. */
void init_game(TicTacToe* game,int size)
{
  // set the size of the board
  // set winner to undecided
  // use malloc to dynamically allocate 2D array  
  // now initialise it
}

/* Deallocate the dynamically allocated memory */
void free_game(TicTacToe* game)
{
  // code goes here, as for your generic solution
}

/* Get a player's move. */ 
int get_player_move(int serverfd, int clientfd, TicTacToe* game)
{
  // read move from client one int at a time
  // check if valid move or not
  // return result to client
  return valid;
}

/* Get a move from the computer. */
/* Return true (not 0) if can move */
/* Return false () if cannot move */
void computer_move(TicTacToe* game)
{
  // as for your generic solution
}

/* Map the board token ID into a character */
char tokenstr(int t) 
{
  if(t==HUMAN) 
    return 'X';
  else if (t==COMPUTER)
    return 'O';
  return '.';
}

/* Send the game result to the client */
/* Do it a character at a time -- easy! */
void print_game(int clientfd, TicTacToe game)
{
  // write out the board one character at a time
}

/* See if there is a winner. */
/* return true (0) if so otherwise false */
int check(TicTacToe* game)
{
  // code is the same as your generic version
  return NONE;
}

/* Tell the client that game has ended and the result of the game */
void print_result(int clientfd, TicTacToe game) 
{
  // send game over
  // tell the client the winner
}

/* Tell the client to continue */
void client_continue(int clientfd) 
{
  // tell the client that it should continue playing
}
