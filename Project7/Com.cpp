#include "헤더.h"

int com_AroundValue(int x, int y, int rotation) {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[b_type[1]][rotation][i][j] == 1) {
				for (int k = 0; k < 4; k++) {
					switch (k) {
					case 0:
						if (((i == 0) && (com_board_value[y + i - 1][x + j] > 0))
							|| ((i != 0) && (blocks[b_type[1]][rotation][i - 1][j] != 1) && (com_board_value[y + i - 1][x + j] > 0)))//한위치의 윗쪽을 검사
							sum += com_board_value[y + i - 1][x + j];
						break;
					case 1:
						if ((i == 4) ||
							(blocks[b_type[1]][rotation][i + 1][j] != 1)) sum += com_board_value[y + i + 1][x + j];//아래쪽을 검사
						break;
					case 2:
						if (((j == 0) && (com_board_value[y + i][x + j - 1] > 0)) ||
							((j != 0) && (blocks[b_type[1]][rotation][i][j - 1] != 1) && (com_board_value[y + i][x + j - 1] > 0))) sum += com_board_value[y + i][x + j - 1];//왼쪽을 검사
						break;
					case 3:
						if (((j == 4) && com_board_value[y + i][x + j + 1] > 0) ||
							((j != 4) && (blocks[b_type[1]][rotation][i][j + 1] != 1) && (com_board_value[y + i][x + j + 1] > 0))) sum += com_board_value[y + i][x + j + 1];//오른쪽을 검사
						break;
					}
				}
			}
		}
	}
	return sum;
}

void com_play()
{
	int value = 0;

	if (C_research == true)
	{
		for (int i = 0; i < 15; i++)
		{
			com_x[i] = 0;
			com_y[i] = 0;
			com_r[i] = 0;
		}
		com_path = 0;

		for (int i = 0; i < BOARD_Y; i++)
		{
			for (int j = 0; j < BOARD_X; j++)
			{
				if (board[1][i][j] > 0) com_board_value[i][j] = i + 1;
				else com_board_value[i][j] = 0;
			}
		}
		for (int i = 0; i < BOARD_Y - 1; i++)
		{
			for (int j = 0; j < BOARD_X; j++)
			{
				if (com_board_value[i][j] == 0 && (com_board_value[i][j - 1] > 0 || com_board_value[i][j + 1] > 0)) com_board_value[i][j] = -1 * (i + 1);
			}
		}
		for (int i = 0; i < BOARD_Y; i++) {
			for (int j = 0; j < BOARD_X; j++) {
				com_drop_value[i][j] = 0;
			}
		}
		for (int i = 0; i < BOARD_Y; i++) {
			for (int j = 1; j < BOARD_X - 1; j++) {
				if (board[1][i][j] > 0 && board[1][i - 1][j] == 0) {
					for (int k = i - 1; k > 0; k--) {
						if (board[1][k][j] > 0) {
							for (int m = i - 1; m > k; m--) com_drop_value[m][j] = 1;
							break;
						}
					}
				}
			}
		}// 보드 리빌딩
		for (int i = 0; i < BOARD_Y - 2; i++)
		{
			for (int j = 0; j < BOARD_X; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					if (Check_Inactive(1, j, i + 1, k) == false && com_AroundValue(j, i, k) > value && Check_Inactive(1, j, i, k) == true)
					{
						bool bypass = false;
						for (int m = 0; m < 4; m++) {
							for (int n = 0; n < 4; n++) {
								if (blocks[b_type[1]][k][m][n] == 1 && com_drop_value[i + m][j + n] == 1) {
									bypass = true;
								}
							}
						}
						if (bypass == false) {
							com_path = 0;
							value = com_AroundValue(j, i, k);
							com_x[0] = j;
							com_y[0] = i;
							com_r[0] = k;
						}
						if (bypass == true)
						{
							com_path = 0;
							if (Check_Inactive(1, j + 1, i, k) == false && Check_Inactive(1, j - 1, i, k) == false && Check_Inactive(1, j, i - 1, k) == false) break;

							int tempX1 = j;
							int tempY1 = i;
							int tempX2 = j;
							int tempY2 = i;
							int temp_path = 0;

							bool underStuck = true; //이 공간이 갇혀 있는지 아닌지를 판별. 무조건 갇혀 있다고 생각하고 출구가 있으면 false
							for (int e = 1; e > -2; e -= 2) { //현재 한번 우회해서 갈수 있는지만 판별할수 있음..
								for (int x = 0; x < BOARD_X; x++) {
									if (underStuck == false) break;
									for (int y = 0; y < BOARD_Y; y++) {
										if (tempY1 - y == 0) {
											underStuck = false;
											temp_path++;
											com_x[temp_path] = j + x * e;
											com_y[temp_path] = tempY1;
											com_r[temp_path] = k;
											break;
										}
										else if (Check_Inactive(1, j + x * e, tempY1 - y, k) == true) {
											tempX2 = j + x * e;
											tempY2 = tempY1 - y;
										}
										else if (Check_Inactive(1, tempX1 + x * e, tempY1 - y, k) == false) break;
									}
									if (tempX1 == tempX2 && tempY1 == tempY2 && x != 0) break;
									else {
										tempX1 = tempX2;
										tempY1 = tempY2;
									}
								}
							}

							if (underStuck == false) { //1차로 우회가 가능한 경우 최종 path업데이트
								value = com_AroundValue(j, i, k);
								com_x[0] = j;
								com_y[0] = i;
								com_r[0] = k;
								com_path = temp_path;
							}
						}
					}
				}
			}

		}
		C_research = false;
	}
	if (b_rotation[1] != com_r[com_path]) com_output = W;
	else if (com_x[com_path] > block_x[1]) com_output = D;
	else if (com_x[com_path] < block_x[1]) com_output = A;
	else if (com_x[com_path] == block_x[1])  if (com_path == 0)com_output = ENTER;
	else  com_output = S;

	if (com_x[com_path] == block_x[1] && com_y[com_path] == block_y[1] && com_r[com_path] == b_rotation[1] && com_path > 0) com_path--;
}

void com_key()
{
	com_play();
	int key = com_output;
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
	case ENTER:
		if (over_player[0] == 0)while (block_crush[1] == 0)	inactive_block2();
		break;
	}
}