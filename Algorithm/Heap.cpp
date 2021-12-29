#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void upheap(int* a, int k) {
	int v;
	v = a[k];
	a[0] = INT_MAX;
	while (a[k / 2] <= v && k / 2 > 0) {
		a[k] = a[k / 2];
		k /= 2;
	}
	a[k] = v;
}

void downheap(int* a, int N, int k) {
	int i, v;
	v = a[k];
	while (k <= N / 2) {
		i = k << 1;
		if (i < N && a[i] < a[i + 1]) i++;
		if (v >= a[i]) break;
		a[k] = a[i];
		k = i;
	}
	a[k] = v;
}

void insert(int* a, int* N, int v) {
	a[++(*N)] = v;
	upheap(a, *N);
}

int extract(int* a, int* N) {
	int v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);
	
	return v;
}

void heap_sort(int* a, int N) {
	int i;
	int hn = 0;
	for (i = 1; i <= N; i++)
		insert(a, &hn, a[i]);
	for (i = hn; i >= 1; i--)
		a[i] = extract(a, &hn);
}

void print_data(int *a, int N) {
	int i;
	for (i = 0; i < N; i++) {
		printf("%-3d", a[i]);
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int N;
	int* data;
	printf("Input data >> ");
	scanf("%C", &data);
	printf("\n");
	heap_sort(data, N);
	print_data(data, N);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}