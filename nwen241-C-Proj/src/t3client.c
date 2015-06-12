#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tictactoe.h"

int size; /* aded to make mute the error checking */
int valid; /* aded to make mute the error checking */

int init_game(int serverfd);
int check(int clientfd);
int player_move(int clientfd, int serverfd);
void print_game(int clientfd, int size);
void print_winner(int clientfd);

/**
 * implement a very simple client that sends and receives
 * all other logic, just send and receive strings
 * extension is to add extra clients
 * @author diego
 */
int main(void) {
	int done; /* used to check validity of move */
	int clientfd, serverfd;
	char *clientpipe = "clientpipe";
	char *serverpipe = "serverpipe";

	/* create the FIFO (named pipe) and open for reading */
	mkfifo(clientpipe, 0666);
	mkfifo(serverpipe, 0666);
	serverfd = open(serverpipe, O_WRONLY);
	clientfd = open(clientpipe, O_RDONLY);

	/* get the board size form user and send info to server */
	size = init_game(serverfd);

	do {
		print_game(clientfd, size);
		do {
			done = player_move(clientfd, serverfd);
		} while (!done);
		if (check(clientfd) != FALSE)
			break; /* was a winner or a draw */
	} while (TRUE);

	/* display final board */
	print_game(clientfd, size);
	/* display winner */
	print_winner(clientfd);

	/* tidy up */
	close(clientfd);
	unlink(clientpipe);

	return 0;
}

/* Start the game by telling server size of the board */
int init_game(int serverfd) {
	int size = 0;

	printf("How big is your board?\n");
	scanf("%d", &size);
	write(serverfd, &size, sizeof(size));
	return size;
}

/* Send player's move to the server and check if was valid. */
int player_move(int clientfd, int serverfd) {
	int x, y;
	int valid = FALSE;

	printf("Enter coordinates (row,column) for your move: \n");
	scanf("%d%*c%d", &x, &y);

	printf("Sending x,y: %d %d\n", x, y);

	/* send the details X,Y to server */
	write(serverfd, &x, sizeof(x));
	write(serverfd, &y, sizeof(y));

	/* check from server if is a valid move */
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
	for (x = 0; x < size; x++) {
		for (y = 0; y < size; y++) {
			/* read from the pipe clientfd into */
			read(clientfd, &value, sizeof(value));
			printf(" %c ", value);
		}
		printf("\n");
	}
	printf("\n");
}

/* Check whether game has ended or whether computer is waiting 
 for the next move */
int check(int clientfd) {
	int check;
	read(clientfd, &check, sizeof(check));
	return check;
}

/* Receive the final results from the server */
void print_winner(int clientfd) {
	int check;
	read(clientfd, &check, sizeof(check));
	if (check == HUMAN)
		printf("You won!\n");
	else if (check == COMPUTER)
		printf("I won!!!!\n");
	else if (check == DRAW)
		printf("Draw\n");
}

