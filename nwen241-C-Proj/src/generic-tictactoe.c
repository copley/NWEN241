/*
 *
 * TICTACTOE -- human vs. computer
 *
 * Author: Ian Welch
 * Date: May 2015
 *
 * CHANGE LOG:
 *
 * 26.05 modified the user prompt to say (row,col) instead of x,y
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

typedef struct TicTacToe {
	int size;
	int winner;
	int **board;
} TicTacToe;

void init_game(TicTacToe* game, int size);
int check(TicTacToe* game);
void free_game(TicTacToe *game);
int player_move(TicTacToe* game);
void computer_move(TicTacToe* game);
void print_game(TicTacToe game);
char tokenstr(int token);
void print_result(TicTacToe game);
int check_move(TicTacToe* game, int, int);

int main(void) {
	int size = 0;
	int done = 0;
	TicTacToe game;

	printf("This is the game of Tic Tac Toe.\n");
	printf("You will be playing against the computer.\n");
	printf("How big is your board?\n");
	scanf("%d", &size);
	printf("Ok Sir, generating new board size: %dx%d\n", size, size);

	/* initialise the board */
	init_game(&game, size);

	do {
		print_game(game);
		do {
			done = player_move(&game);
		} while (!done); /* loop until valid move */
		if (check(&game) != FALSE)
			break; /* was a winner or a draw */
		computer_move(&game);
		if (check(&game) != FALSE)
			break;
	} while (TRUE);

	/* show final positions */
	print_result(game);
	print_game(game);

	/* free up memory allocations */
	free_game(&game);

	return 0;
}

/* Initialize the matrix. */
void init_game(TicTacToe* game, int size) {
	int i, j;
	/* initialise the 2D array for the board, first allocate mem for colums, then allocate memory for each row */
	game->size = size;
	game->board = malloc(sizeof(int *) * game->size);
	int x = 0;
	for (; x < game->size; x++) {
		game->board[x] = malloc(sizeof(int) * game->size);
	}

	/* now initialise it */
	for (i = 0; i < game->size; i++) {
		for (j = 0; j < game->size; j++) {
			game->board[i][j] = NONE;
		}
	}
}

/* Display the game board. */
void print_game(TicTacToe game) {
	int x, y;
	for (x = 0; x < game.size; x++) {
		for (y = 0; y < game.size; y++) {
			printf(" %c ", tokenstr(game.board[x][y]));
		}
		printf("\n");
	}
	printf("\n");
}

/* Get a player's move. */
int player_move(TicTacToe* game) {
	int x, y;
	int valid = FALSE;
	printf("Enter coordinates (row,column) for your move: ");
	scanf("%d%*c%d", &x, &y);
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

/* See if there is a winner: return true (0) if so otherwise false */
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

/* Get a move from the computer. */
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

/* Print the result */
void print_result(TicTacToe game) {
	if (game.winner == HUMAN)
		printf("You won!\n");
	else if (game.winner == COMPUTER)
		printf("I won!!!!\n");
	else
		printf("Draw :(\n");
}

/* Map the board token ID to a character. */
char tokenstr(int t) {
	if (t == HUMAN)
		return 'X';
	else if (t == COMPUTER)
		return 'O';
	return '.';
}

/* Deallocate the dynamically allocated memory */
void free_game(TicTacToe* game) {
	int i;
	for (i = 0; i < game->size; i++) {
		free(game->board[i]);
	}
	free(game->board);
}

