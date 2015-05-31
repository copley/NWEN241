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
void send_board();
char tokenstr(int token);
void send_result();
void client_continue();
int check_move(int, int);

TicTacToe game;

/**
 * Server program, which handles the logic of the game and is responsible for checking if there is a winner or if the game is a draw
 * @author diego
 */
int main(void) {
	int done;
	char *clientpipe = "clientpipe";
	char *serverpipe = "serverpipe";

	/* create the FIFO (named pipe) and open for reading */
	mkfifo(serverpipe, 0666);
	mkfifo(clientpipe, 0666);
	game.serverfd = open(serverpipe, O_RDONLY);
	game.clientfd = open(clientpipe, O_WRONLY);

	printf("Tic Tac Toe: server online...  waiting for client ... \n");

	int size;
	read(game.serverfd, &size, sizeof(size)); /* read from the pipe into buffer */
	printf("The game board is %d by %d.\n", size, size);

	game.size = size;
	init_game();

	do {
		send_board();
		do {
			done = get_player_move();
		} while (!done); /* loop until valid move */
		if (check() != FALSE) /* check if there is a winner or run out of slots */
			break; /* was a winner or a draw */
		computer_move();
		if (check() != FALSE) {
			break;
		}
	} while (TRUE);

	send_board(); /* send final board */
	send_result(); /* sends result of game to client */

	/* clean up */
	free(game.board);
	close(game.serverfd);
	unlink(serverpipe);
	return 0;
}

/* Initialize the matrix. */
void init_game() {
	int i, j;
	game.winner = NONE;
	/* initialise the 2D array for the board, first allocate mem for colums, then allocate memory for each row */
	game.board = malloc(sizeof(int *) * game.size);
	int x = 0;
	for (; x < game.size; x++) {
		game.board[x] = malloc(sizeof(int) * game.size);
	}

	/* now initialise it */
	for (i = 0; i < game.size; i++)
		for (j = 0; j < game.size; j++)
			/* set to empty of tokens */
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
	int x, y;
	int valid = FALSE;

	read(game.serverfd, &x, sizeof(x)); /* read x */
	read(game.serverfd, &y, sizeof(y)); /* read x */

	/* check if valid move or not */
	if (check_move(x, y)) {
		x--;
		y--;
		if (game.board[x][y] != NONE) {
			printf("Invalid move, try again.\n");
			valid = FALSE;
		} else {
			game.board[x][y] = HUMAN;
			valid = TRUE;
		}
	}

	/* return result to client */
	write(game.clientfd, &valid, sizeof(valid));
	return valid;
}

int check_move(int x, int y) {
	if (x < 0 || x > game.size || y < 0 || y > game.size) {
		printf("Invalid move, try again.\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

/* Get a move from the computer. */
void computer_move() {
	    int i, j, cx, cy;
	    cx = cy = -1;
	    for (i = 0; i < game.size; i++) {
	        for (j = 0; j < game.size; j++)
	            if (game.board[i][j] == NONE) {
	                cx = i;
	                cy = j;
	                break;
	            }
	        if (cx != -1) {
	            game.board[cx][cy] = COMPUTER;
	            break;
	        }
	    }
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
void send_board() {
	int x, y;
	char c;
	/* write the board one character at a time */
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

	/* check rows */
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
			write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
			return TRUE;
		} else if (countO == game.size) {
			game.winner = 1;
			write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
			return TRUE;
		}
	}

	/* check colums */
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
			write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
			return TRUE;
		} else if (countO == game.size) {
			game.winner = 1;
			write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
			return TRUE;
		}
	}

	/* check diagonal */
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
		write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
		return TRUE;
	} else if (countO == game.size) {
		game.winner = 1;
		write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
		return TRUE;
	}

	/* check reverse diagonal */
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
		write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
		return TRUE;
	} else if (countO == game.size) {
		game.winner = 1;
		write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
		return TRUE;
	}

	/* test if out of space on the board */
	count = 0;
	for (x = 0; x < game.size; x++) {
		for (y = 0; y < game.size; y++) {
			if (game.board[x][y] == NONE)
				count++;
		}
	}
	if (count == 0) {
		game.winner = DRAW;
		write(game.clientfd, &game.winner, sizeof(game.winner)); /* sends message back to client */
		return TRUE;
	}

	write(game.clientfd, &FALSE, sizeof(FALSE)); /* sends message back to client */
	return FALSE;
}

/* Tell the client that game has ended and the result of the game */
void send_result() {
	write(game.clientfd, &game.winner, sizeof(game.winner));
}

/* Tell the client to continue */
void client_continue() {
	write(game.clientfd, &NONE, sizeof(NONE));
}
