#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

int test_sample(int* a, int N) {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			sum += a[i] * a[j];
		}
	}
	return sum;
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int A, B;
	printf("A, B를 입력하시오: ");
	scanf("%d, %d", &A, &B);
	int C = 0;

	while (A > 0) {
		if (A % 2 == 1)
			C += B;
		A /= 2, B *= 2;
	}

	printf("Result: %d\n", C);
		
	/*
	int sum = 0;
	int j;


	for (j = 1; j <= 30; j++) {
		sum += j;
	}

	printf("Sum (1-30) : %d\n", sum);
	*/

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}
