#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX 10
#define is_stack_empty() (top < 0)

int stack[MAX];
int top;

void init_stack() {
	top = -1;
}

int push(int t) {
	if (top >= MAX - 1) {
		printf("Stack overflow !!\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}

int pop() {
	if (top < 0) {
		printf("Stack underflow !!\n");
		return -1;
	}
	return stack[top--];
}

void move(int from, int to) {
	printf("\nMove from %d to %d", from, to);
}
/*
void hanoi(int n, int from, int by, int to) {
	if (n == 1)
		move(from, to);
	else {
		hanoi(n - 1, from, to, by);
		move(from, to);
		hanoi(n - 1, by, from, to);
	}
}
*/
void nr_hanoi(int n, int from, int by, int to) {
	int done = 0;
	init_stack();
	while (!done) {
		while (n > 1) {
			push(to);
			push(by);
			push(from);
			push(n);

			n--;
			push(to);
			to = by;
			by = pop();
		}
		move(from, to);
	
		if (!is_stack_empty()) {
			n = pop();
			from = pop();
			by = pop();
			to = pop();
			move(from, to);

			n--;
			push(from);
			from = by;
			by = pop();
		}
		else done = 1;
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int j = 0;
	int height = 0;
	printf("\nIf you want to quit, input -1:");

	while (1) {
		printf("\n하노이 타워의 층수를 입력하시오: ");
		scanf("%d", &height);

		if (height <= 0) break;
		nr_hanoi(height, 1, 2, 3);
	}

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}