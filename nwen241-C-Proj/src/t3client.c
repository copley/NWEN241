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

/*
 * implement a very simple client that sends and receives
 * all other logic, just send and receive strings
 * extension is to add extra clients
 * @author diego
 */
int main(void) {

	int clientfd, serverfd, size;
	char *clientpipe = "clientpipe";
	char *serverpipe = "serverpipe";

	/* create the FIFO (named pipe) and open for reading */
	mkfifo(clientpipe, 0666);
	mkfifo(serverpipe, 0666);
	serverfd = open(serverpipe, O_WRONLY);
	clientfd = open(clientpipe, O_RDONLY);

	printf("This is the game of Tic Tac Toe.\n");
	printf("You will be playing against the computer.\n");

	int done;
	int game_over;

	size = init_game(serverfd);

	do {
		print_game(clientfd, size);
		do {
			done = player_move(clientfd, serverfd);
		        } while (!done);
		        if (check() != FALSE)
		            break; /* was a winner or a draw */
		        computer_move();
		        if (check() != FALSE)
		            break; /* was a winner or a draw */
		    } while (TRUE);
//
//		    print_result();
//		    print_game(); /* show final positions */
//
//		    for (i=0; i<game.size; i++){
//		        free(game.board[i]);
//		    }

//		    free(game.board);

//		    return 0;



	// client exits loop if game is over
	// client should continue if receives continue message

	// tidy up
	close(clientfd);
	unlink(clientpipe);

	return 0;
}

/* Start the game by telling server size of the board */
int init_game(int serverfd) {
	int size;
	printf("How big is your board?\n");
	scanf("%d", &size);
	write(serverfd, &size, sizeof(size));
  return size;
}

/* Send player's move to the server and check if was valid. */
int player_move(int clientfd, int serverfd) {
    int x, y;
    int valid;

	// ask the player
    printf("Enter coordinates (row,column) for your move: ");
    scanf("%d%*c%d", &y, &x);
    x--;
    y--;

	/* send the details X,Y */
    write(serverfd, &x, sizeof(x));
    write(serverfd, &y, sizeof(y));

	/* check on server if is a valid move */
    read(clientfd, &valid, sizeof(valid));
    if (valid == FALSE) {
    	printf("Invalid move, try again.\n");
    }
    return valid;
}

/* Display the game on the screen. */
void print_game(int clientfd, int size) {
	int x, y;
	char value;

	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++) {
			// read from the pipe clientfd into
			read(clientfd, &value, sizeof(value));
			printf(" %c ", value);
		}
		printf("\n");
	}
	printf("\n");
}

/* Check whether game has ended or whether computer is waiting for the next move */
int check(int clientfd) {

	return TRUE;
}

/* Receive the final results from the server */
void print_winner(int clientfd) {
}

