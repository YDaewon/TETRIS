#include "Çì´õ.h"

void init() {
	for (int b = 0; b < 2; b++)
	{
		for (int i = 0; i < BOARD_Y; i++) {
			for (int j = 0; j < BOARD_X; j++) {
				board[b][i][j] = 0;
				board_buffer[b][i][j] = 25;
			}
		}
		for (int j = 1; j < BOARD_X; j++) {
			board[b][3][j] = CEILLING;
		}
		for (int i = 1; i < BOARD_Y - 1; i++) { 
			board[b][i][0] = WALL;
			board[b][i][BOARD_X - 1] = WALL;
		}
		for (int j = 0; j < BOARD_X; j++) {
			board[b][BOARD_Y - 1][j] = WALL;
		}
	}
}

void init_buffer()
{
	for (int i = 0; i < BOARD_Y; i++) {
		for (int j = 0; j < BOARD_X; j++) {
			board_buffer[0][i][j] = 25;
			board_buffer[1][i][j] = 25;
		}
	}
}

void gameset()
{
	for (int b = 0; b < 2; b++)
	{
		if (over_player[b] == 0)
		{
			for (int i = 0; i < BOARD_Y; i++) { 
				for (int j = 0; j < BOARD_X; j++) {
					board[b][i][j] = 0;
					board_buffer[b][i][j] = 0;
				}
			}
		}
	}
}