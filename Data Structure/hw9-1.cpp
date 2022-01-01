#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void shell_sort(int *a, int n) {  // �� ���� ����
	int i, j, k, h, v;            // �� ������ ���� ������ ����
	for (h = 1; h < n; h = 3 * h + 1); // h=3h+1 �� intervasl�� ������
	for (h /= 3; h > 0; h /= 3) { // h�� 3���� �������鼭 �ݺ��� ����
		for (i = 0; i < h; i++) { // �迭�� ���� �ݺ��� ����
			for (j = i + h; j < n; j += h) { // insertion ���İ� ����, interval�� ��
				v = a[j]; // ���� ��ġ�� �����ϱ� ���� �߰��� ��ġ�� �� v�� ����
				k = j;    // ���� ��ġ�� �����ϱ� ���� �߰��� ��ġ�� �� k�� ����
				while ((k > h - 1) && (a[k - h] > v)) { // ���� ���ϰ� �� ���� ���� �迭�� ������ �ٲٴ� �ݺ���
					a[k] = a[k - h]; // �迭�� ���� ��ȯ
					k -= h; // ���� ���� ���� �ݺ� ����
				}
				a[k] = v; // �迭�� ���� ��ȯ
			}
		}
	}
}

int main() {
	int a[10]; // ũ�Ⱑ 10�� �迭 ����
	srand((unsigned int)time(NULL)); // ���� �Լ��� ����� �����ϱ� ���� ��

	for (int i = 0; i < 10; i++) {
		a[i] = rand() % 100 + 1;   // �迭 a�� ������ 1~100 �� �����ϰ� ����
	}

	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);       // ���� �ϱ� �� �ʱ� �迭 a�� ���
	}
	printf("\n");

	shell_sort(a, 10);  // �迭 a�� shell sort

	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);       // ���� �� �迭 a�� ��� 
	}
	printf("\n");

	return 0;
}