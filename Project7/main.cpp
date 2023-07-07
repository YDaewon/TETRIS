#include "헤더.h"

int blocks[7][4][4][4] = {
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}
};
int com_board_value[BOARD_Y][BOARD_X];
int com_drop_value[BOARD_Y][BOARD_X];
int com_path;

int com_x[15];
int com_y[15];
int com_r[15];
bool C_research;
int com_output;

int board[2][BOARD_Y][BOARD_X];
int board_buffer[2][BOARD_Y][BOARD_X];

int b_type[2];
int b_type_next[2];
int b_rotation[2];
int block_x[2];
int block_y[2];
int block_crush[2];
int new_block_flag[2];
int score[2];
int space_flag[2];
int line_count[2];
int over_player[2];
int player;
int flag[2];

int main(void)
{
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("mode con cols=112 lines=30");
	srand((unsigned)time(NULL));
	HideCursor(0);
	player = title();
	for (int i = 0; i < 2; i++)
	{
		over_player[i] = 1;
		flag[i] = 1;
	}

	if (player == 1)
	{
		system("cls");
		init();

		b_type_next[0] = rand() % 7;
		b_type_next[1] = rand() % 7;
		create_b(0);
		create_b(1);
		while (1)
		{
			for (int i = 0; i < 25; i++)
			{
				print_scoreboard();
				display();
				input_key();
				if (over_player[1])com_key();
				Sleep(5);
				if (over_player[0])
				{
					if (block_crush[0] && Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == false)
						Sleep(25);
					if (space_flag[0] == 1)
					{
						space_flag[0] == 0;
						break;
					}
				}
				if (over_player[1])
				{
					if (block_crush[1] && Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == false)
						Sleep(25);
					if (space_flag[1] == 1)
					{
						space_flag[1] == 0;
						break;
					}
				}
			}
			drop_block();
			for (int l = 0; l < 2; l++)
			{
				if (over_player[l])
				{
					check_line(l);
					Game_over(l);
					if (new_block_flag[l] == 1)
						create_b(l);
				}
			}
			if (over_player[0] == 0 && over_player[1] == 0)
			{
				system("cls");
				gotoxy(20, 12); printf("1P Score: %d", score[0]);
				gotoxy(20, 14); printf("Com Score: %d", score[1]);
				int winner = 1;
				if (score[0] < score[1])
				{
					gotoxy(20, 17); printf("Com Player Win!");
				}
				else if (score[0] == score[1])
				{
					gotoxy(20, 17); printf("Draw!");
				}
				else
				{
					gotoxy(20, 17); printf("%d Player Win!", winner);
				}
				while (1)
					if (_kbhit()) return 0;
			}
		}
	}
	else if (player == 2)
	{
		system("cls");
		init();

		b_type_next[0] = rand() % 7;
		b_type_next[1] = rand() % 7;
		create_b(0);
		create_b(1);

		while (1)
		{
			for (int i = 0; i < 25; i++)
			{
				print_scoreboard();
				display();
				input_key();
				Sleep(2);
				if (over_player[0])
				{
					if (block_crush[0] && Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == false)
						Sleep(15);
					if (space_flag[0] == 1)
					{
						space_flag[0] == 0;
						break;
					}
				}
				if (over_player[1])
				{
					if (block_crush[1] && Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == false)
						Sleep(15);
					if (space_flag[1] == 1)
					{
						space_flag[1] == 0;
						break;
					}
				}
			}
			drop_block();
			for (int l = 0; l < 2; l++)
			{
				if (over_player[l])
				{
					check_line(l);
					Game_over(l);
					if (new_block_flag[l] == 1)
						create_b(l);
				}
			}
			if (over_player[0] == 0 && over_player[1] == 0)
			{
				system("cls");
				gotoxy(20, 12); printf("1P Score: %d", score[0]);
				gotoxy(20, 14); printf("2P Score: %d", score[1]);
				int winner = 1;
				if (score[0] < score[1]) winner = 2;
				if (score[0] == score[1])
				{
					gotoxy(20, 17); printf("Draw!");
				}
				else
				{
					gotoxy(20, 17); printf("%d Player Win!", winner);
				}
				while (1)
					if (_kbhit()) return 0;
			}
		}
	}
	else
	{
		gotoxy(15, 26); printf("게임을 종료합니다"); Sleep(1000); printf("."); Sleep(1000); printf("."); Sleep(1000); printf("."); Sleep(1000);
		return 0;
	}

}