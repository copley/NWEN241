#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tictactoe.h"

int size; /* aded to make mute the error checking */
int valid; /* aded to make mute the error checking */

typedef struct TicTacToe {
	int size;
	int **board;
	int winner;
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
int check_move(TicTacToe* game, int, int);
void client_continue(int clientfd);

int main(void) {
	int clientfd, serverfd, done, size = 0;
	char *clientpipe = "clientpipe";
	char *serverpipe = "serverpipe";
	TicTacToe game;

	/* create the FIFO (named pipe) and open for reading */
	mkfifo(serverpipe, 0666);
	mkfifo(clientpipe, 0666);
	serverfd = open(serverpipe, O_RDONLY);
	clientfd = open(clientpipe, O_WRONLY);

	printf("Tic Tac Toe: server online...  waiting for client ... \n");
	read(serverfd, &size, sizeof(size)); /* read from the pipe into buffer */
	printf("The game is %d by %d.\n", size, size);
	printf("Initialising game ....\n");

	init_game(&game, size);
	do {
		print_game(clientfd, game);
		do {
			done = player_move(serverfd, clientfd, &game);
		} while (!done); /* loop until valid move */
		if (check(&game) != FALSE) { /* check if there is a winner or run out of slots */
			write(clientfd, &TRUE, sizeof(TRUE));
			break; /* was a winner or a draw */
		}
		computer_move(&game);
		if (check(&game) != FALSE) {
			write(clientfd, &TRUE, sizeof(TRUE));
			break;
		}
		write(clientfd, &FALSE, sizeof(FALSE));
	} while (TRUE);

	/* send final board and print results*/
	print_game(clientfd, game);
	print_result(clientfd, game);

	/* free up memory allocations */
	free_game(&game);
	close(serverfd);
	unlink(serverpipe);
	return 0;
}

/* Initialize the matrix. */
void init_game(TicTacToe* game, int size) {
	int i, j;
	game->winner = NONE;
	game->size = size;
	/* initialise the 2D array for the board, first allocate
	 * mem for colums, then allocate memory for each row */
	game->board = malloc(sizeof(int *) * size);
	int x = 0;
	for (; x < size; x++) {
		game->board[x] = malloc(sizeof(int) * size);
	}
	/* now initialise it */
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			/* set to empty of tokens */
			game->board[i][j] = NONE;
		}
	}
}

/* Deallocate the dynamically allocated memory */
void free_game(TicTacToe* game) {
	int i;
	for (i = 0; i < game->size; i++) {
		free(game->board[i]);
	}
	free(game->board);
}

/* Get a player's move. */
int player_move(int serverfd, int clientfd, TicTacToe* game) {
	int x, y;
	int valid = FALSE;
	read(serverfd, &x, sizeof(x)); /* read x */
	read(serverfd, &y, sizeof(y)); /* read x */

	printf("Receiving x,y: %d %d\n", x, y);
	/* check if valid move or not */
	if (check_move(game, x, y)) {
		x--;
		y--;
		if (game->board[x][y] != NONE) {
			printf("Invalid move, try again.\n");
			valid = FALSE;
		} else {
			game->board[x][y] = HUMAN;
			valid = TRUE;
		}
	}

	/* return result to client */
	write(clientfd, &valid, sizeof(valid));
	return valid;
}

int check_move(TicTacToe* game, int x, int y) {
	if (x < 0 || x > game->size || y < 0 || y > game->size) {
		printf("Invalid move, try again.\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

/* Get a move from the computer. */
/* Return true (not 0) if can move */
/* Return false () if cannot move */
void computer_move(TicTacToe* game) {
	int i, j, cx, cy;
	cx = cy = -1;
	for (i = 0; i < game->size; i++) {
		for (j = 0; j < game->size; j++)
			if (game->board[i][j] == NONE) {
				cx = i;
				cy = j;
				break;
			}
		if (cx != -1) {
			game->board[cx][cy] = COMPUTER;
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
/* Do it a character at a time -- easy! */
void print_game(int clientfd, TicTacToe game) {
	int x, y;
	char c;
	/* write the board one character at a time */
	for (x = 0; x < game.size; x++) {
		for (y = 0; y < game.size; y++) {
			c = tokenstr(game.board[x][y]);
			write(clientfd, &c, sizeof(c));
			printf(" %c ", c);
		}
		printf("\n");
	}
	printf("\n");
}

/* See if there is a winner. */
/* return true (0) if so otherwise false */
int check(TicTacToe* game) {
	int x, y;
	int count;
	int countX;
	int countO;

	/* check rows */
	for (y = 0; y < game->size; y++) {
		countX = 0;
		countO = 0;
		for (x = 0; x < game->size; x++) {
			if (game->board[x][y] == -1)
				countX++;
			else if (game->board[x][y] == 1)
				countO++;
		}
		if (countX == game->size) {
			game->winner = -1;
			return TRUE;
		} else if (countO == game->size) {
			game->winner = 1;
			return TRUE;
		}
	}

	/* check colums */
	for (x = 0; x < game->size; x++) {
		countX = 0;
		countO = 0;
		for (y = 0; y < game->size; y++) {
			if (game->board[x][y] == -1)
				countX++;
			else if (game->board[x][y] == 1)
				countO++;
		}
		if (countX == game->size) {
			game->winner = -1;
			return TRUE;
		} else if (countO == game->size) {
			game->winner = 1;
			return TRUE;
		}
	}

	/* check diagonal */
	countX = 0;
	countO = 0;
	for (x = 0; x < game->size; x++) {
		if (game->board[x][x] == -1)
			countX++;
		else if (game->board[x][x] == 1)
			countO++;
	}
	if (countX == game->size) {
		game->winner = -1;
		return TRUE;
	} else if (countO == game->size) {
		game->winner = 1;
		return TRUE;
	}

	/* check reverse diagonal */
	countX = 0;
	countO = 0;
	for (x = 0; x < game->size; x++) {
		if (game->board[game->size - 1 - x][x] == -1)
			countX++;
		else if (game->board[game->size - 1 - x][x] == 1)
			countO++;
	}
	if (countX == game->size) {
		game->winner = -1;
		return TRUE;
	} else if (countO == game->size) {
		game->winner = 1;
		return TRUE;
	}

	/* test if out of space on the board */
	count = 0;
	for (x = 0; x < game->size; x++) {
		for (y = 0; y < game->size; y++) {
			if (game->board[x][y] == NONE)
				count++;
		}
	}
	if (count == 0) {
		game->winner = DRAW;
		return TRUE;
	}

	/* no-one and nor was there a draw */

	return FALSE;
}

/* Tell the client that game has ended and the result of the game */
void print_result(int clientfd, TicTacToe game) {
	write(clientfd, &game.winner, sizeof(NONE));
}

/* Tell the client to continue */
void client_continue(int clientfd) {
	write(clientfd, &NONE, sizeof(NONE));
}
