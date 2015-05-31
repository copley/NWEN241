#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tictactoe.h"

#define MAX_BUF 1024

typedef struct TicTacToe {
	int size;
	int **board;
	int winner;
	int clientfd;
	int serverfd;
} TicTacToe;

int check();
void init_game();
void free_game();
int get_player_move();
void computer_move();
void print_game();
char tokenstr(int token);
void print_result();
void client_continue();

TicTacToe game;

/**
 * Server program, which handles the logic of the game and is responsible for checking if there is a winner or if the game is a draw
 * @author diego
 */
int main(void) {
	int i, j, done;
	char *clientpipe = "clientpipe";
	char *serverpipe = "serverpipe";
	char buffer[MAX_BUF];

	// create the FIFO (named pipe) and open for reading
	mkfifo(serverpipe, 0666);
	mkfifo(clientpipe, 0666);
	game.serverfd = open(serverpipe, O_RDONLY); // client talks to server
	game.clientfd = open(clientpipe, O_WRONLY); // server talks to client

	printf("This is the game of Tic Tac Toe.\n");
	printf("You will be playing against the computer.\n");

	// wait for a client to tell us how large is the game board
	int size;
	read(game.serverfd, &size, sizeof(size)); /* read from the pipe into buf */
	printf("The game board is %d by %d.\n", size, size);

	// initialise the board
	game.size = size;
	// as for the generic solution with addition of pipes
	// initialise the 2D array for the board, first allocate mem for colums, then allocate memory for each row
	init_game();

	do {
	        print_game();
	        do {
	            done = get_player_move();
	        } while (!done); /* loop until valid move */
	        if (check() != FALSE) { /* check if there is a winner or run out of slots */
	        	// sends result to client ?
	            break; /* was a winner or a draw */
	        }
	        computer_move();
	        if (check() != FALSE) {
	            break; // was a winner or a draw
	        }
	    } while (TRUE);

	    print_result();
	    print_game(); /* show final positions */

	    for (i=0; i<game.size; i++){
	        free(game.board[i]);
	    }


	    /* clean up */
	    free(game.board);
	    close(game.serverfd);
	    unlink(serverpipe);
	    return 0;
}

/* Initialize the matrix. */
void init_game() {
	int i, j;
	// initialise the 2D array for the board, first allocate mem for colums, then allocate memory for each row
	game.board = malloc(sizeof(int *) * game.size);
	int x = 0;
	for (; x < game.size; x++) {
		game.board[x] = malloc(sizeof(int) * game.size);
	}

	// now initialise it
	for (i = 0; i < game.size; i++)
		for (j = 0; j < game.size; j++)
			// set to empty of tokens
			game.board[i][j] = NONE;
}

/* Deallocate the dynamically allocated memory */
void free_game() {
	int i;
	for (i = 0; i < game.size; i++) {
		free(game.board[i]);
	}
	free(game.board);
}

/* Get a player's move. */
int get_player_move() {
	int valid;
	int x,y;
	read(game.serverfd, &x, sizeof(x)); /* read x */
	read(game.serverfd, &y, sizeof(y)); /* read x */

	/* check if valid move or not */
    if (game.board[x][y] != NONE) {
        printf("Invalid move, try again.\n");
        valid = FALSE;
    } else {
        game.board[x][y] = HUMAN;
        valid = TRUE;
    }

	/* return result to client */
    write(game.clientfd, &valid, sizeof(valid));
	return valid;
}

/* Get a move from the computer. */
/* Return true (not 0) if can move */
/* Return false () if cannot move */
void computer_move() {
	// as for your generic solution
}

/* Map the board token ID into a character */
char tokenstr(int t) {
	if (t == HUMAN)
		return 'X';
	else if (t == COMPUTER)
		return 'O';
	return '.';
}

/* Send the game result to the client */
void print_game() {
	int x,y;
	char c;
	    /* read and print the board one character at a time */
	    for (y = 0; y < game.size; y++) {
	        for (x = 0; x < game.size; x++) {
	        	c = tokenstr(game.board[x][y]);
	            write(game.clientfd, &c, sizeof(c));
	        }
	    }
	}

/* See if there is a winner. */
int check() {
	int x, y;
	int count;
	int countX;
	int countO;

	// check rows
	for (y = 0; y < game.size; y++) {
		countX = 0;
		countO = 0;
		for (x = 0; x < game.size; x++) {
			if (game.board[x][y] == -1)
				countX++;
			else if (game.board[x][y] == 1)
				countO++;
		}
		if (countX == game.size) {
			game.winner = -1;
			return TRUE;
		} else if (countO == game.size) {
			game.winner = 1;
			return TRUE;
		}
	}

	// check colums
	for (x = 0; x < game.size; x++) {
		countX = 0;
		countO = 0;
		for (y = 0; y < game.size; y++) {
			if (game.board[x][y] == -1)
				countX++;
			else if (game.board[x][y] == 1)
				countO++;
		}
		if (countX == game.size) {
			game.winner = -1;
			return TRUE;
		} else if (countO == game.size) {
			game.winner = 1;
			return TRUE;
		}
	}

	// check diagonal
	countX = 0;
	countO = 0;
	for (x = 0; x < game.size; x++) {
		if (game.board[x][x] == -1)
			countX++;
		else if (game.board[x][x] == 1)
			countO++;
	}
	if (countX == game.size) {
		game.winner = -1;
		return TRUE;
	} else if (countO == game.size) {
		game.winner = 1;
		return TRUE;
	}

	// check reverse diagonal
	countX = 0;
	countO = 0;
	for (x = 0; x < game.size; x++) {
		if (game.board[game.size - 1 - x][x] == -1)
			countX++;
		else if (game.board[game.size - 1 - x][x] == 1)
			countO++;
	}
	if (countX == game.size) {
		game.winner = -1;
		return TRUE;
	} else if (countO == game.size) {
		game.winner = 1;
		return TRUE;
	}

	// test if out of space on the board
	count = 0;
	for (x = 0; x < game.size; x++) {
		for (y = 0; y < game.size; y++) {
			if (game.board[x][y] == NONE)
				count++;
		}
	}
	if (count == 0) {
		game.winner = DRAW;
		return TRUE;
	}

	// no-one and nor was there a draw
	return FALSE;
}

/* Tell the client that game has ended and the result of the game */
void print_result() {
	if (game.winner == HUMAN)
		printf("You won!\n");
	else if (game.winner == COMPUTER)
		printf("I won!!!!\n");
	else
		printf("Draw :(\n");
	/* tell the client the winner */
	write(game.clientfd, &game.winner, sizeof(game.winner));
}

/* Tell the client to continue */
void client_continue() {
	/* tell the client that it should continue playing */
	write(game.clientfd, &NONE, sizeof(NONE));
}
