#pragma once

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> 
#include <mmsystem.h>
#include <process.h>

#define BOARD_X 12
#define BOARD_Y 23
#define ACTIVE_BLOCK -2 // ���� �����̴� ���
#define CEILLING -1      // õ��
#define EMPTY 0         // ��ĭ
#define WALL 1          // ��, �ٴ�
#define INACTIVE_BLOCK 2 // �̵��� �Ϸ�� ��ϰ� 
#define BOARD1_START_X 3
#define BOARD1_START_Y 1
#define BOARD2_START_X 40
#define BOARD2_START_Y 1

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define w 119
#define s 115
#define a 97
#define d 100
#define W 87
#define S 83
#define A 65
#define D 68
#define ENTER 13 

#pragma comment(lib,"winmm.lib")
#define SOUND_FILE_NAME "��Ʈ����.wav"//��������
//GUI
void display();//���� ���൵�� ����ϴ� �Լ�
void print_scoreboard();//�������� ����ϴ� �Լ�
int title(void);//ó�� ����ȭ���� ����ϴ� �Լ� (1: �̱�, 2:��Ƽ, 3: ����)
void HideCursor(char show);//Ŀ���� ����� �Լ�
void gotoxy(int x, int y); // �Է��� ��ǥ�� Ŀ���� �ű�� �Լ�

//Init
void init();//���带 �ʱ�ȭ ���ִ� �Լ�
void init_buffer();//�������� �����ϱ� ���� board_buffer�迭�� �ʱ�ȭ �ϴ� �Լ�
void gameset();//���� ������ �÷��̾��� ���带 �ʱ�ȭ ���ִ� �Լ�

//Tetris
void create_b(int b); // ���ο� ����� ����� �Լ�
void input_key(); //Ű�Է¿� ���� �ٸ� ����� ������ �Լ�
void move_block(int key);// ����� �ű�� �Լ�
bool Check_Inactive(int b, int block_x, int block_y, int b_rotation);
//�ش� x,y�� ����� �ű� �� �ִ��� �˻��ϴ� �Լ� ture: �浹x false: �浹��
void drop_block();//����� ��ĭ ������ �Լ�
void check_line(int b);// ������ �˻� ��, ����� �� ä������ ���ִ� �Լ�
void Game_over(int b);//���� ���� flag�� ����� �Լ�
void inactive_block1();// 1P�� ����� ��ĭ ������ �Լ�
void inactive_block2();// 2P�� ����� ��ĭ ������ �Լ�

//Com
void com_key(); // ��ǻ���� OutPut�� �ް� ����� �����̴� �Լ�
int com_AroundValue(int x, int y, int rotation);// ����� �ֺ����� ����ġ ���� ���Ͽ� ��ȯ�ϴ� �Լ�
void com_play();//com_AroundValue�� ��ȯ���� �̿��Ͽ� AI�� ����� �ùٸ����� ��ġ�ϵ��� ����� �Լ�


extern int blocks[7][4][4][4];//��Ʈ�ι̳� ��� ���� �迭
extern int board[2][BOARD_Y][BOARD_X];//�÷��̾� ����
extern int board_buffer[2][BOARD_Y][BOARD_X];//������ ����(ȭ�� �����Ÿ� ������)

extern int b_type[2];//��� Ÿ��
extern int b_type_next[2];//���� ��� Ÿ��
extern int b_rotation[2];// ����� ȸ�� (1~4)
extern int block_x[2];// ����� x��ǥ
extern int block_y[2];// ����� y��ǥ
extern int block_crush[2];// ����� �� �̻� ������ �� ������ Ȯ�� 1: �������� 0: ������ �� ����.
extern int new_block_flag[2];// ���ο� ����� ����� ���� flag
extern int score[2];//�÷����� ���� ���� �迭
extern int space_flag[2];// hard drop�� ���� flag
extern int line_count[2];// ����� ��ä�������� Ȯ���ϱ� ���� �迭
extern int over_player[2];// ���ӿ����� �÷��̾ üũ
extern int player;// �̱�, ��Ƽ ���� ����
extern int flag[2];// ���� �����Ǹ� ȭ���� �� �̻� �ݺ� ������� �ʰ� �ϱ� ���� flag


extern int com_board_value[BOARD_Y][BOARD_X];// ai�� ��θ� Ž���� �� �ֵ�� ���忡��	��ġ�� �ű��, ����
extern int com_drop_value[BOARD_Y][BOARD_X];// ai��ȸ�ؾ� �� ��츦 ���� ���� ��� �ؿ��� 1�� ����
extern int com_path;// ��ǻ���� ��� ����
extern int com_x[15];//path x��ǥ ����
extern int com_y[15];//path Y "
extern int com_r[15];// path ȸ���� ����
extern bool C_research; // AI�� ��θ� ��Ž���ϰ� �ϴ� ����
extern int com_output; // ��ǻ���� OutPut
