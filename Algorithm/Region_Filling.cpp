#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

int canvas[7][7] = { 0,0,0,0,0,0,0,
					0,0,0,2,0,0,0,
					0,0,0,1,0,0,0,
					0,1,1,1,1,0,0,
					0,0,0,0,0,1,0,
					0,0,0,0,0,0,0,
					0,0,0,0,0,0,0 };

void recur_fill(int x, int y) {
	if (canvas[y][x] == 0 || canvas[y][x] == 2)
		return;
	else {
		canvas[y][x] = 2;
		recur_fill(x - 1, y);
		recur_fill(x + 1, y);
		recur_fill(x, y - 1);
		recur_fill(x, y + 1);
		recur_fill(x + 1, y + 1); // 대각 성분
		recur_fill(x - 1, y - 1);
		recur_fill(x + 1, y - 1);
		recur_fill(x - 1, y + 1);
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	recur_fill(2, 3); // Seed

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			printf("%-2d", canvas[i][j]);
		}
		printf("\n");
	}

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}