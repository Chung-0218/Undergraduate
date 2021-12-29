#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

int factorial(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	
	return n *= factorial(n - 1);
}

int main() {
	int j, n, result;
	printf("숫자를 입력하세요 ");
	scanf("%d", &n);

	result = factorial(n);

	printf("factorial = %d\n", result);

	return 0;
}