#include "헤더.h"

void create_b(int b)
{
	if (player == 1) C_research = true;
	new_block_flag[b] = 0;
	block_x[b] = 5;
	block_y[b] = 0;
	b_type[b] = b_type_next[b]; 
	b_type_next[b] = rand() % 7;
	b_rotation[b] = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[b_type[b]][b_rotation[b]][i][j] == 1)
			{
				board[b][block_y[b] + i][block_x[b] + j] = ACTIVE_BLOCK;
			}
		}
	}
	for (int i = 1; i < 3; i++) {
		if (over_player[0])
		{
			for (int j = 0; j < 4; j++) {
				if (blocks[b_type_next[0]][0][i][j] == 1) {
					gotoxy(15 + 2 + j, i + 6);
					printf("■");
				}
				else {
					gotoxy(15 + 2 + j, i + 6);
					printf("  ");
				}
			}
		}
		else
		{
			for (int j = 0; j < 4; j++) {
				gotoxy(15 + 2 + j, i + 6);
				printf("  ");
			}
		}
		if (over_player[1])
		{
			for (int j = 0; j < 4; j++) {
				if (blocks[b_type_next[1]][0][i][j] == 1) {
					gotoxy(30 + 2 + j, i + 6);
					printf("■");
				}
				else {
					gotoxy(30 + 2 + j, i + 6);
					printf("  ");
				}
			}
		}
		else
		{
			for (int j = 0; j < 4; j++) {
				gotoxy(30 + 2 + j, i + 6);
				printf("  ");
			}
		}
	}
}

void input_key()
{
	int key = 0;

	if (_kbhit())
	{
		key = _getch();
		if (key == 224)// 방향키
		{
			key = _getch();
			switch (key)
			{
			case LEFT:
				if (Check_Inactive(0, block_x[0] - 1, block_y[0], b_rotation[0]))
					move_block(LEFT);
				break;
			case RIGHT:
				if (Check_Inactive(0, block_x[0] + 1, block_y[0], b_rotation[0]))
					move_block(RIGHT);
				break;
			case UP:
				if (Check_Inactive(0, block_x[0], block_y[0], (b_rotation[0] + 1) % 4))
					move_block(UP);
				else if (block_crush[0] == 1 && Check_Inactive(0, block_x[0], block_y[0], (b_rotation[0] + 1) % 4) == true)
					move_block(1727);
				break;
			case DOWN:
				if (Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]))
					move_block(DOWN);
				break;
			}
		}
		else
		{
			switch (key)
			{
			case A:
				if (Check_Inactive(1, block_x[1] - 1, block_y[1], b_rotation[1]))
					move_block(A);
				break;
			case D:
				if (Check_Inactive(1, block_x[1] + 1, block_y[1], b_rotation[1]))
					move_block(D);
				break;
			case W:
				if (Check_Inactive(1, block_x[1], block_y[1], (b_rotation[1] + 1) % 4))
					move_block(W);
				else if (block_crush[1] == 1 && Check_Inactive(1, block_x[1], block_y[1], (b_rotation[1] + 1) % 4) == true)
					move_block(777);
				break;
			case S:
				if (Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]))
					move_block(S);
				break;
			case a:
				if (Check_Inactive(1, block_x[1] - 1, block_y[1], b_rotation[1]))
					move_block(A);
				break;
			case d:
				if (Check_Inactive(1, block_x[1] + 1, block_y[1], b_rotation[1]))
					move_block(D);
				break;
			case w:
				if (Check_Inactive(1, block_x[1], block_y[1], (b_rotation[1] + 1) % 4))
					move_block(W);
				else if (block_crush[1] == 1 && Check_Inactive(1, block_x[1], block_y[1], (b_rotation[1] + 1) % 4) == true)
					move_block(777);
				break;
			case s:
				if (Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]))
					move_block(S);
				break;
			case SPACE:
				while (block_crush[0] == 0)
				{
					inactive_block1();
				}
				break;
			case ENTER:
				while (block_crush[1] == 0)
				{
					inactive_block2();
				}
				break;
			}
		}
	}
	while (_kbhit())_getch();
}

void move_block(int key)
{
	switch (key) {
	case LEFT:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j - 1] = ACTIVE_BLOCK;
				}
			}
		}
		block_x[0]--;
		break;

	case RIGHT:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j + 1] = ACTIVE_BLOCK;
				}
			}
		}
		block_x[0]++;
		break;
	case UP:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j] = EMPTY;
				}
			}
		}
		b_rotation[0] = (b_rotation[0] + 1) % 4;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j] = ACTIVE_BLOCK;
				}
			}
		}
		break;
	case DOWN:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i + 1][block_x[0] + j] = ACTIVE_BLOCK;
				}
			}
		}
		block_y[0]++;
		break;
	case 1727:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i][block_x[0] + j] = EMPTY;
				}
			}
		}
		b_rotation[0] = (b_rotation[0] + 1) % 4;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[0]][b_rotation[0]][i][j] == 1)
				{
					board[0][block_y[0] + i - 1][block_x[0] + j] = ACTIVE_BLOCK;
				}
			}
		}
		block_y[0]--;
		break;
	case A:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j - 1] = ACTIVE_BLOCK;
				}
			}
		}
		block_x[1]--;
		break;

	case D:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j + 1] = ACTIVE_BLOCK;
				}
			}
		}
		block_x[1]++;
		break;
	case W:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j] = EMPTY;
				}
			}
		}
		b_rotation[1] = (b_rotation[1] + 1) % 4;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j] = ACTIVE_BLOCK;
				}
			}
		}
		break;
	case S:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i + 1][block_x[1] + j] = ACTIVE_BLOCK;
				}
			}
		}
		block_y[1]++;
		break;
	case 777:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i][block_x[1] + j] = EMPTY;
				}
			}
		}
		b_rotation[1] = (b_rotation[1] + 1) % 4;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[b_type[1]][b_rotation[1]][i][j] == 1)
				{
					board[1][block_y[1] + i - 1][block_x[1] + j] = ACTIVE_BLOCK;
				}
			}
		}
		block_y[1]--;
		break;
	}
}

bool Check_Inactive(int b, int block_x, int block_y, int b_rotation) // true: 충돌x false: 충돌ㅇ
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[b_type[b]][b_rotation][i][j] == 1 && board[b][block_y + i][block_x + j] > 0)
				return false;
		}
	}
	return true;
}

void drop_block()
{
	if (block_crush[0] && Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == true) block_crush[0] = 0;
	if (block_crush[0] && Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == false) {
		for (int i = 0; i < BOARD_Y; i++) { //현재 조작중인 블럭을 굳힘 
			for (int j = 0; j < BOARD_X; j++) {
				if (board[0][i][j] == ACTIVE_BLOCK)
					board[0][i][j] = INACTIVE_BLOCK;
			}
		}
		block_crush[0] = 0; 
		new_block_flag[0] = 1;   
		return;
	}

	if (block_crush[1] && Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == true) block_crush[1] = 0;
	if (block_crush[1] && Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == false) {
		for (int i = 0; i < BOARD_Y; i++) { //현재 조작중인 블럭을 굳힘 
			for (int j = 0; j < BOARD_X; j++) {
				if (board[1][i][j] == ACTIVE_BLOCK)
					board[1][i][j] = INACTIVE_BLOCK;
			}
		}
		block_crush[1] = 0;
		new_block_flag[1] = 1;  
		return;
	}

	if (over_player[0])
	{
		if (Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == true)move_block(DOWN);
		if (Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == false) block_crush[0]++; //밑으로 이동이 안되면  crush flag를 켬
	}
	if (over_player[1])
	{
		if (Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == true)move_block(S); 
		if (Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == false) block_crush[1]++; 
	}
}

void inactive_block1()
{
	if (block_crush[0] && Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == true) block_crush[0] = 0;
	if (block_crush[0] && Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == false) {
		for (int i = 0; i < BOARD_Y; i++) {
			for (int j = 0; j < BOARD_X; j++) {
				if (board[0][i][j] == ACTIVE_BLOCK)
					board[0][i][j] = INACTIVE_BLOCK;
			}
		}
		block_crush[0] = 0;
		new_block_flag[0] = 1; 
		return;
	}
	if (Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == true)
	{
		move_block(DOWN);
	}
	if (Check_Inactive(0, block_x[0], block_y[0] + 1, b_rotation[0]) == false) block_crush[0]++;
}

void inactive_block2()
{
	if (block_crush[1] && Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == true) block_crush[1] = 0;
	if (block_crush[1] && Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == false) {
		for (int i = 0; i < BOARD_Y; i++) {
			for (int j = 0; j < BOARD_X; j++) {
				if (board[1][i][j] == ACTIVE_BLOCK)
					board[1][i][j] = INACTIVE_BLOCK;
			}
		}
		block_crush[1] = 0;
		new_block_flag[1] = 1;  
		return;
	}

	if (Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == true)
	{
		move_block(S);
	}
	if (Check_Inactive(1, block_x[1], block_y[1] + 1, b_rotation[1]) == false) block_crush[1]++;
}

void check_line(int b)
{
	int flag[2] = { 0 };
	int block_count;
	for (int i = BOARD_Y - 2; i > 3;)
	{
		block_count = 0;
		for (int j = 1; j < BOARD_X - 1; j++)
		{
			if (board[b][i][j] > 0)
				block_count++;
		}
		if (block_count == 10)
		{
			score[b] = score[b] + 100;
			flag[b]++;

			for (int k = i; k > 1; k--)
			{
				for (int l = 1; l < BOARD_X - 1; l++)
				{
					if (board[b][k][l] != CEILLING)
						board[b][k][l] = board[b][k - 1][l];
					if (board[b][k][l] == CEILLING)
						board[b][k][l] = EMPTY;
				}
			}
		}
		else i--;
	}
	if (flag[0]) { 
		if (flag[0] > 1) { //2콤보이상인 경우 경우 보너스및 메세지를 게임판에 띄웠다가 지움 
			gotoxy(BOARD1_START_X + (BOARD_X / 2) - 2, BOARD1_START_Y + block_y[0] - 2); printf("%d COMBO!", flag[0]);
			Sleep(100);
			score[0] += (flag[0] * 100);
			init_buffer();
		}
	}
	if (flag[1]) {
		if (flag[1] > 1) {
			gotoxy(BOARD2_START_X + (BOARD_X / 2) - 2, BOARD2_START_Y + block_y[1] - 2); printf("%d COMBO!", flag[1]);
			Sleep(100);
			score[1] += (flag[1] * 100);
			init_buffer();
		}
	}
}

void Game_over(int b)
{
	for (int l = 1; l < BOARD_X - 1; l++)
	{
		if (board[b][3][l] > 0)
		{
			over_player[b] = 0;
			gameset();
		}
	}
}
