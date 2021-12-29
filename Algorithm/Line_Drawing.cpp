#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define BLK 20

void recursive_line(int* canvas, int x1, int y1, int x2, int y2) {
	if (-1 <= (x1 - x2) <= 1 && -1 <= (y1 - y2) <= 1)
		return;
	else {
		int cx = (x1 + x2) / 2;
		int cy = (y1 + y2) / 2;
		recursive_line(canvas, x1, y1, cx, cy);
		recursive_line(canvas, cx, cy, x2, y2);
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int i, j;
	int* canvas = (int*)calloc(BLK * BLK, sizeof(int));

	recursive_line(canvas, 1, 1, 15, 15);

	for (i = 0; i < BLK; i++) {
		for (j = 0; j < BLK; j++) {
			printf("%-2d", canvas[i * BLK + j]);
		}
		printf("\n");
	}
	free(canvas);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}