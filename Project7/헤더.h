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
#define ACTIVE_BLOCK -2 // 지금 움직이는 블록
#define CEILLING -1      // 천장
#define EMPTY 0         // 빈칸
#define WALL 1          // 벽, 바닥
#define INACTIVE_BLOCK 2 // 이동이 완료된 블록값 
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
#define SOUND_FILE_NAME "테트리스.wav"//음악파일
//GUI
void display();//게임 진행도를 출력하는 함수
void print_scoreboard();//점수판을 출력하는 함수
int title(void);//처음 시작화면을 출력하는 함수 (1: 싱글, 2:멀티, 3: 종료)
void HideCursor(char show);//커서를 숨기는 함수
void gotoxy(int x, int y); // 입력한 좌표로 커서를 옮기는 함수

//Init
void init();//보드를 초기화 해주는 함수
void init_buffer();//깜빡임을 방지하기 위한 board_buffer배열을 초기화 하는 함수
void gameset();//게임 오버된 플레이어의 보드를 초기화 해주는 함수

//Tetris
void create_b(int b); // 새로운 블록을 만드는 함수
void input_key(); //키입력에 따라 다른 명령을 내리는 함수
void move_block(int key);// 블록을 옮기는 함수
bool Check_Inactive(int b, int block_x, int block_y, int b_rotation);
//해당 x,y로 블록을 옮길 수 있는지 검사하는 함수 ture: 충돌x false: 충돌ㅇ
void drop_block();//블록을 한칸 내리는 함수
void check_line(int b);// 라인을 검사 후, 블록이 다 채워지면 없애는 함수
void Game_over(int b);//게임 오버 flag를 세우는 함수
void inactive_block1();// 1P의 블록을 한칸 내리는 함수
void inactive_block2();// 2P의 블록을 한칸 내리는 함수

//Com
void com_key(); // 컴퓨터의 OutPut을 받고 블록을 움직이는 함수
int com_AroundValue(int x, int y, int rotation);// 블록의 주변값의 가중치 값을 더하여 반환하는 함수
void com_play();//com_AroundValue의 반환값을 이용하여 AI가 블록을 올바른곳에 배치하도록 만드는 함수


extern int blocks[7][4][4][4];//테트로미노 블록 저장 배열
extern int board[2][BOARD_Y][BOARD_X];//플레이어 보드
extern int board_buffer[2][BOARD_Y][BOARD_X];//보드의 버퍼(화면 깜빡거림 수정용)

extern int b_type[2];//블록 타입
extern int b_type_next[2];//다음 블록 타입
extern int b_rotation[2];// 블록의 회전 (1~4)
extern int block_x[2];// 블록의 x좌표
extern int block_y[2];// 블록의 y좌표
extern int block_crush[2];// 블록이 더 이상 움직일 수 없는지 확인 1: 못움직임 0: 움직일 수 있음.
extern int new_block_flag[2];// 새로운 블록을 만들기 위한 flag
extern int score[2];//플레이의 점수 저장 배열
extern int space_flag[2];// hard drop을 위한 flag
extern int line_count[2];// 블록이 다채워졌는지 확인하기 위한 배열
extern int over_player[2];// 게임오버된 플레이어를 체크
extern int player;// 싱글, 멀티 선택 변수
extern int flag[2];// 게임 오버되면 화면을 더 이상 반복 출력하지 않게 하기 위한 flag


extern int com_board_value[BOARD_Y][BOARD_X];// ai가 경로를 탐색할 수 있드록 보드에가	중치를 매긴뒤, 저장
extern int com_drop_value[BOARD_Y][BOARD_X];// ai우회해야 할 경우를 위해 막힌 블록 밑에는 1을 지정
extern int com_path;// 컴퓨터의 경로 순서
extern int com_x[15];//path x좌표 모음
extern int com_y[15];//path Y "
extern int com_r[15];// path 회전값 ‘’
extern bool C_research; // AI가 경로를 재탐색하게 하는 변수
extern int com_output; // 컴퓨터의 OutPut
