#include "헤더.h"

void display()
{
	for (int j = 1; j < BOARD_X - 1; j++) {
		if (board[0][3][j] == EMPTY) board[0][3][j] = CEILLING;
	}
	for (int j = 1; j < BOARD_X - 1; j++) {
		if (board[1][3][j] == EMPTY) board[1][3][j] = CEILLING;
	}
	if (over_player[0])
	{
		for (int i = 0; i < BOARD_Y; i++) {
			for (int j = 0; j < BOARD_X; j++) {
				if (board_buffer[0][i][j] != board[0][i][j]) { //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
					gotoxy(BOARD1_START_X + j, BOARD1_START_Y + i);
					switch (board[0][i][j]) {
					case EMPTY: //빈칸모양 
						printf("  ");
						break;
					case CEILLING: //천장모양 
						printf("- ");
						break;
					case WALL: //벽모양 
						printf("▩");
						break;
					case INACTIVE_BLOCK: //굳은 블럭 모양  
						printf("■");
						break;
					case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
						printf("□");
						break;
					}
				}
			}
		}
	}
	else
	{
		if (flag[0])
		{
			for (int i = 0; i < BOARD_Y; i++) {
				for (int j = 0; j < BOARD_X; j++) {
					gotoxy(BOARD1_START_X + j, BOARD1_START_Y + i);
					printf("  ");
				}
			}
			gotoxy((BOARD1_START_X + BOARD_X) / 2 + 3, BOARD1_START_Y + (BOARD_Y / 2) - 2); printf("Game Over");
			gotoxy((BOARD1_START_X + BOARD_X) / 2 + 3, BOARD1_START_Y + (BOARD_Y / 2) - 1); printf("점수: %d점", score[0]);
			flag[0] = 0;
		}
	}
	if (over_player[1])
	{
		for (int i = 0; i < BOARD_Y; i++) {
			for (int j = 0; j < BOARD_X; j++) {
				if (board_buffer[1][i][j] != board[1][i][j]) { //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
					gotoxy(BOARD2_START_X + j, BOARD2_START_Y + i);
					switch (board[1][i][j]) {
					case EMPTY: //빈칸모양 
						printf("  ");
						break;
					case CEILLING: //천장모양 
						printf("- ");
						break;
					case WALL: //벽모양 
						printf("▩");
						break;
					case INACTIVE_BLOCK: //굳은 블럭 모양  
						printf("■");
						break;
					case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
						printf("□");
						break;
					}
				}
			}
		}
	}
	else
	{
		if (flag[1])
		{
			for (int i = 0; i < BOARD_Y; i++) {
				for (int j = 0; j < BOARD_X; j++) {
					gotoxy(BOARD2_START_X + j, BOARD2_START_Y + i);
					printf("  ");
				}
			}
			gotoxy(BOARD2_START_X + (BOARD_X / 2) - 4, BOARD2_START_Y + (BOARD_Y / 2) - 2); printf("Game Over");
			gotoxy(BOARD2_START_X + (BOARD_X / 2) - 4, BOARD2_START_Y + (BOARD_Y / 2) - 1); printf("점수: %d점", score[1]);
			flag[1] = 0;
		}
	}
	for (int i = 0; i < BOARD_Y; i++) { //게임판을 그린 후 main_cpy에 복사  
		for (int j = 0; j < BOARD_X; j++) {
			board_buffer[0][i][j] = board[0][i][j];
			board_buffer[1][i][j] = board[1][i][j];
		}
	}
}

void print_scoreboard()
{
	int x = 16, y = 12;
	if (over_player[0])
	{
		gotoxy(x, 6); printf("────Next────");
		gotoxy(x, 10); printf("────────────");
		gotoxy(x, y); printf("Score:   %5d", score[0]);
	}
	else
	{
		gotoxy(x, 6); printf("            ");
		gotoxy(x, 10); printf("             ");
		gotoxy(x, y); printf("                ");
	}
	for (int i = 0; i < 30; i++)
	{
		gotoxy(26, i); printf("|");
	}
	if (over_player[1])
	{
		gotoxy(31, 6); printf("────Next────");
		gotoxy(31, 10); printf("────────────");
		gotoxy(31, y); printf("Score:   %5d", score[1]);
	}
	else
	{
		gotoxy(31, 6); printf("            ");
		gotoxy(31, 10); printf("             ");
		gotoxy(31, y); printf("                ");
	}
}

int title(void)
{
	int x = 5;
	int y = 4; 

	gotoxy(x, y + 0); printf("■■■■■      ■■■■■      ■■■■■      ■■■■■      ■■■      ■■■■■"); Sleep(500);
	gotoxy(x, y + 1); printf("    ■          ■                  ■          ■      ■        ■        ■        "); Sleep(500);
	gotoxy(x, y + 2); printf("    ■          ■■■■■          ■          ■■■■          ■        ■■■■■"); Sleep(500);
	gotoxy(x, y + 3); printf("    ■          ■                  ■          ■    ■          ■                ■"); Sleep(500);
	gotoxy(x, y + 4); printf("    ■          ■■■■■          ■          ■      ■      ■■■      ■■■■■"); Sleep(500);
	x += 13;
	gotoxy(x, y + 7); printf("  1P         2P   ");
	gotoxy(x, y + 9); printf("  ↑    |    W     : Turn a block");
	gotoxy(x, y + 10); printf("←  →  |  A   D   : Left / Right");
	gotoxy(x, y + 11); printf("  ↓    |    S     : Soft Drop");
	gotoxy(x, y + 12); printf(" SPACE  |  R_Enter : Hard Drop");

	gotoxy(x, y + 16); printf("> Single Player( with Com )");
	gotoxy(x, y + 17); printf("  Multi Player( with 2Player )");
	gotoxy(x, y + 18); printf("  Exit");
	gotoxy(x, y + 20); printf("please Enter key to Choice");

	y = 20;
	while (1)
	{
		if (_kbhit())
		{
			int key = _getch();
			switch (key)
			{
			case UP:
				if (y > 19)
				{
					gotoxy(x, y); printf(" ");
					gotoxy(x, --y); printf(">");
				}
				break;
			case DOWN:
				if (y < 22)
				{
					gotoxy(x, y); printf(" ");
					gotoxy(x, ++y); printf(">");
				}
				break;
			case ENTER:
				return (y - 19);
			}
		}
	}
}

void HideCursor(char show)//커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y) {
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}//gotoxy함수 