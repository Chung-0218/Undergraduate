#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX 10

int stack[MAX];
int top;

void init_stack(void) {
	top = -1;
}

int push(int t) {
	if (top >= MAX - 1) {
		printf("\n   Stack overflow !!");
		return -1;
	}
	stack[++top] = t;
	return t;
}

int pop() {
	if (top < 0) {
		printf("\n   Stack underflow !!");
		return -1;
	}
	return stack[top--];
}

void print_stack(void) {
	int i;
	printf("\n   Stack: ");
	for (i = top; i >= 0; i--) {
		printf("%-3d", stack[i]);
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point
	
	int i;
	init_stack();
	
	printf("1. Push 3, 6, 9, 1, 6, 3");
	push(3);
	push(6);
	push(9);
	push(1);
	push(6);
	push(3);
	print_stack();
	
	printf("\n2. Pop");
	pop();
	print_stack();

	printf("\n3. Push 4, 8, 7, 2, 0, 5");
	push(4);
	push(8);
	push(7);
	push(2);
	push(0);
	push(5);
	print_stack();

	printf("\n4. Initialize stack");
	init_stack();
	print_stack();

	printf("\n5. Pop");
	pop();
	print_stack();
	printf("\n");

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}