#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define UP 1
#define RIGHT 2
#define DOWN 4
#define LEFT 8
#define MAZE_SIZE 19
#define MOUSE 2

int* rec;
int sx = MAZE_SIZE - 1;
int sy = MAZE_SIZE - 2;

int maze[MAZE_SIZE][MAZE_SIZE] = 
{ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void record(int x, int y) {
	static int index = 0;
	rec[index++] = x;
	rec[index++] = y;
}

void delay(int n) {
	for (int i = 0; i < 50000000; i++) {}
}

void forward(int* x, int* y, int dir) {
	gotoxy(*x + 1, *y + 1);
	putch(' ');

	*x = (dir == LEFT) ? --(*x) : (dir == RIGHT) ? ++(*x) : *x;
	*y = (dir == UP) ? --(*y) : (dir == DOWN) ? ++(*y) : *y;

	record(*x, *y);
	gotoxy(*x + 1, *y + 1);
	putch(MOUSE);
}

int still_in_maze(int x, int y) {
	if (x > 0 && x < MAZE_SIZE - 1 && y>0 && y < MAZE_SIZE - 1)
		return 1;
	else return 0;
}

int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir) {
	x = (dir == LEFT) ? --x : (dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y : (dir == DOWN) ? ++y : y;
	
	return m[y][x];
}

void right(int* dir) {
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}

void left(int* dir) {
	*dir >>= 1;
	*dir = (*dir == 0) ? LEFT : *dir;
}

void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir) {
	gotoxy(x + 1, y + 1);
	putch(MOUSE);

	forward(&x, &y, dir);
	while (still_in_maze(x, y)) {
		delay(100);     // for display
		right(&dir);
		while (wall_ahead(m, x, y, dir))
			left(&dir);
		forward(&x, &y, dir);
	}
	record(-1, -1);
}

int del_path(int i, int j) {
	int k = i;

	while (rec[j] >= 0)
		rec[i++] = rec[j++];
	rec[i] = -1;

	return k;
}

void shortest_path(void)
{
	int i = 0;
	int x, y;
	int j;
	int x1, y1;

	while (rec[i] >= 0)
	{
		x = rec[i];
		y = rec[i + 1];
		j = i + 2;
		while (rec[j] >= 0)
		{
			x1 = rec[j];
			y1 = rec[j + 1];
			if (x == x1 && y == y1)
				j = del_path(i, j);
			j++;
			j++;
		}
		i++;
		i++;
	}
	i = 0;
	while (rec[i] >= 0)
	{
		x = rec[i++];
		y = rec[i++];
		gotoxy(x + 1, y + 1);
		putch(MOUSE);
		delay(100);
		gotoxy(x + 1, y + 1);
		putch(' ');
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	rec = (int*)calloc(MAZE_SIZE * MAZE_SIZE, sizeof(int));
	system("cls");
	int x, y;
	for (y = 0; y < MAZE_SIZE; y++) {
		if (y == 0) gotoxy(0, 1);

		for (x = 0; x < MAZE_SIZE; x++) {
			if (x == 0) printf(" ");

			if (maze[y][x] == 1) printf("%%");
			else printf(" ");
		}
		printf("\n");
	}

	right_hand_on_wall(maze, sx, sy, LEFT);  // 1회차

	shortest_path();                         // 2회차(최단거리)

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}