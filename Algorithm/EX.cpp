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
	printf("두 수를 입력하시오: ");
	scanf("%d, %d", &A, &B);
	
	// result = GCD_minus(A, B);
	result = GCD_mod(A, B);
	printf("두 수의 최대공약수는: %d\n", result);
	*/

	int i, j, n;
	printf("---소수 구하기---\n");
	printf("수를 입력하시오 ");
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
	printf("프로그램 실행시간: %.6f초\n", diff1);

	return 0;
}