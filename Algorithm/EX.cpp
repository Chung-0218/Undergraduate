#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

int GCD_minus(int a, int b) {
	while (a) {
		if (a < b) {
			int tmp;
			tmp = a;
			a = b;
			b = tmp;
		}
		a -= b;
	}
	return b;
}

int GCD_mod(int a, int b) {
	int tmp;
	while (b) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff1, diff2;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point
	
	/*
	int A, B, result;
	printf("�� ���� �Է��Ͻÿ�: ");
	scanf("%d, %d", &A, &B);
	
	// result = GCD_minus(A, B);
	result = GCD_mod(A, B);
	printf("�� ���� �ִ�������: %d\n", result);
	*/

	int i, j, n;
	printf("---�Ҽ� ���ϱ�---\n");
	printf("���� �Է��Ͻÿ� ");
	scanf("%d", &n);
	for (i = 2; i <= n; i++) {
		for (j = 2; j < i; j++) {
			if (i % j == 0) break;
		}
		if (i == j) printf("%d ", i);
	}

	QueryPerformanceCounter(&stop);   // stopping point
	diff1 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	
	printf("\n");
	printf("���α׷� ����ð�: %.6f��\n", diff1);

	return 0;
}