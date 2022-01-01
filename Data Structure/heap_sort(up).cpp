#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void upheap(int* a, int k) {
	int v;
	v = a[k];
	while (0 < v / 2 && a[k / 2] <= v) {
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

void heap_sort(int* a, int N) {
	int i, temp;
	a = a - 1;
	for (i = 2; i <= N; i++) {
		upheap(a, i);
	}
	for (i = N; i > 1; i--) {
		temp = a[1];
		a[1] = a[i];
		a[i] = temp;
		downheap(a, i - 1, 1);
	}
}

void heap_sort2(int* a, int N) {
	int i, temp;
	a = a - 1;
	for (i = N / 2; i >= 1; i--)
		downheap(a, N, i);
	for (i = N; i > 1; i--) {
		temp = a[1];
		a[1] = a[i];
		a[i] = temp;
		downheap(a, i - 1, 1);
	}	
}

int main() {
	int n = 9;
	int heap[9] = { 8,7,6,4,5,3,9,1,2 };
	
	for (int i = 0; i < n; i++) {
		printf("%d ", heap[i]);
	}
	printf("\n");
	heap_sort(heap, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", heap[i]);
	}
	printf("\n");
	
	return 0;
}