#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h.>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define SIZE 30  // �迭�� ũ�� ����

void select_sort(int* a, int N) {  // select ���� ���� *a�� data, N�� data�� length
	int min;      // �ּҰ� ����
	int min_idx;  // �ּҰ��� �ε���(�ּ�) ����
	int x, y;     // for loop�� ���� �� ���� ����

	for (y = 0; y < N - 1; y++) {  // y�� ���� ����Ǵ� ��ġ
		min_idx = y;   // �ּҰ��� �ε����� y�� ����
		min = a[y];    // �ּҰ��� a�� y�ε��� ������ ����
		for (x = y + 1; x < N; x++) { // �ּҰ��� ã�� ���� �ݺ��� 
			if (min > a[x]) {  // min�� �ּҰ��� �ƴ� ���
				min = a[x];    // min�� a�� x�ε��� ������ ����
				min_idx = x;   // min�� �ε����� x�� ����
			}
		}
		a[min_idx] = a[y];
		a[y] = y;          // a[y] �� a[min_idx] �� ���� exchange
	}
}

int intcmp(const void* a, const void* b) {// int ������ �ڷ����� ��ȯ���ִ� �Լ� ����
	return (*(int*)a - *(int*)b);  // void pointer casting, pointer casting
}

 void gen_select_sort(void* base, int nelem, int width,
					 int (*fcmp)(const void*, const void*)) {   // void pointer, function pointer�� Ȱ����
	void* min; // void�� �ּҰ� ����                                select ������ �Ϲ��� (��� �ڷ����� ����)
	int min_idx;
	int x, y;

	min = malloc(width);  // min�� �޸� �Ҵ� ����
	for(y = 0; y < nelem-1; y++) { // ���� ������ġ y�� ���� for loop ����
		min_idx = y;  // min�� �ε����� y�� ����
		memcpy(min, (char*)base + y * width, width);  // min = a[y]�� ���� �ǹ�
		for (x = y + 1; x < nelem; x++) { // �ּҰ��� ã�� ���� �ݺ���
			if (fcmp(min, (char*)base + x * width) > 0) { // min > a[x]�� �� ����� ���� �ǹ�
				memcpy(min, (char*)base + x * width, width); // min = a[x]�� ���� �ǹ�
				min_idx = x; // min�� �ε����� x�� ����
			}
		}
		memcpy((char*)base + min_idx * width, (char*)base + y * width, width); // a[min_idx] = a[y]�� ���� �ǹ�
		memcpy((char*)base + y * width, min, width);                           // a[y] = min�� ���� �ǹ� ��, �� ���� exchange
	}
	free(min); // �޸� ����
} 

void main() {
	int number[SIZE] = { 9,4,5,1,3,9 }; // ���� �� �迭 ����

	select_sort(number, 6); // select ����

	gen_select_sort(number, 6, sizeof(int), intcmp); // general select ����
}