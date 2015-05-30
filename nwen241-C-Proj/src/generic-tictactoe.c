/*
 * generic-tictactoe.c
 *
 *  Created on: 28/05/2015
 *      Author: diego
 */
#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

typedef struct TicTacToe {
	int size; // this is the size of the game board
	int **board;
	// this is the game board
	int winner; // who won
} TicTacToe;

int check();
void init_game();
int player_move();
void computer_move();
void print_game();
char tokenstr(int token);
void print_result();

//int board[3][3]; // our tic tac toe board
//int **board; // 2D Array of board game
int winner; // who has won the game
TicTacToe game;  // TicTacToe game

int main(void) {

	printf("This is the game of Tic Tac Toe.\n");
	printf("You will be playing against the computer.\n");
	printf("How bigis your board? Remember: size matters !\n");
	scanf("%d", &game.size);
	printf("Ok Sir, generating new board size: %dx%d\n", game.size, game.size);

	init_game(); // initialise the board

	int done;
	do {
		print_game();
		do {
			done = player_move();
		} while (!done); // loop until valid move
		if (check() != FALSE)
			break; // was a winner or a draw
		computer_move();
		if (check() != FALSE)
			break; // was a winner or a draw
	} while (TRUE);

	print_result();
	print_game(); /* show final positions */

	return 0;
}

/* Initialize the matrix. */
void init_game() {
	int i, j;

	// initialise the 2D array for the board, first allocate mem for colums, then allocate memory for each row
	game.board = malloc(sizeof(int *)*game.size);
	int x = 0;
	for (; x < game.size; x++){
		game.board[x] = malloc(sizeof(int)*game.size);
	}

	// now initialise it
	for (i = 0; i < game.size; i++)
		for (j = 0; j < game.size; j++)
			// set to empty of tokens
			game.board[i][j] = NONE;
}

/* Get a player's move. */
int player_move() {
	int x, y;
	int valid = FALSE;

	// changed the print statement so it is clear that it is row,col (Ian 26.05)
	printf("Enter coordinates (row,column) for your move: ");
	scanf("%d%*c%d", &x, &y);

	x--;
	y--;

	if (game.board[x][y] != NONE) {
		printf("Invalid move, try again.\n");
		valid = FALSE;
	} else {
		game.board[x][y] = HUMAN;
		valid = TRUE;
	}
//	printf("\n board[%d][%d]:%d\n",x,y,game.board[x][y]);
	return valid;
}

/* Get a move from the computer. */
void computer_move() {
//	int done = FALSE;
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

/* Map the board token ID to a character. */
char tokenstr(int t) {
	if (t == HUMAN)
		return 'X';
	else if (t == COMPUTER)
		return 'O';
	return '.';
}

/* Display the game board. */
void print_game() {
	int i, j;

	// read and print the board one character at a time
//	printf("%d",game.size);
	for (i = 0; i < game.size; i++) {
		for (j = 0; j < game.size; j++) {
			printf(" %c ", tokenstr(game.board[i][j]));
		}
		printf("\n");
	}
	printf("\n");
}

/* See if there is a winner. */
/* return true (0) if so otherwise false */
int check() {
	int i, j;
	int isWinning = FALSE;
	int count;

	// loops though rows to check if there are n occurences of same seed
	for (i = 0; i < game.size; i++) { /* check rows */
		for (j = 0; j < game.size; j++){
			if (game.board[i][j] != NONE &&  game.board[i][j] == game.board[i][j+1]) {
				isWinning = TRUE;
				winner = game.board[i][j];
			} else {
				isWinning = FALSE;
			}
		}
	}
	if (isWinning) return TRUE;

	for (j = 0; j < game.size; j++) { /* check columns */
		for (i=0; i < game.size; i++){
			if (game.board[i][j] != NONE && game.board[i][j] == game.board[i+1][j]) {
				isWinning = TRUE;
				winner = game.board[i][j];
			} else {
				isWinning = FALSE;
			}
		}
	}
	if (isWinning) return TRUE;

	/* test diagonals */
	for (i = 0; i < game.size; i++) {
		if (game.board[i][i] != NONE && game.board[i][i] == game.board[i+1][i+1]){
			isWinning = TRUE;
			winner = game.board[i][j];
		} else {
			isWinning = FALSE;
		}
	}
	if (isWinning) return TRUE;

	for (j = game.size-1; j >= 0; j--) { /* check columns */
		if (game.board[j][game.size-j] != NONE && game.board[j][game.size-j] == game.board[j-1][game.size-(j-1)]){
			isWinning = TRUE;
			winner = game.board[i][j];
		} else {
			isWinning = FALSE;
		}
	}
	if (isWinning) return TRUE;

	/* test if out of space on the board */
	count = 0;
	for (i = 0; i < game.size; i++) {
		for (j = 0; j < game.size; j++) {
			if (game.board[i][j] == NONE)
				count++;
		}
	}
	if (count == 0) {
		winner = DRAW;
		return TRUE;
	}

	// no-one and nor was there a draw
	return FALSE;
}

/* Print the result */
void print_result() {
	if (winner == HUMAN)
		printf("You won!\n");
	else if (winner == COMPUTER)
		printf("I won!!!!\n");
	else
		printf("Draw :(\n");


	//////// REMEMBER TO FREE THE MEMORY !!!!
}

