#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void shell_sort(int *a, int n) {  // 쉘 정렬 정의
	int i, j, k, h, v;            // 쉘 정렬을 위한 변수들 정의
	for (h = 1; h < n; h = 3 * h + 1); // h=3h+1 로 intervasl을 설정함
	for (h /= 3; h > 0; h /= 3) { // h를 3으로 나눠가면서 반복문 시행
		for (i = 0; i < h; i++) { // 배열에 대한 반복문 시행
			for (j = i + h; j < n; j += h) { // insertion 정렬과 동일, interval을 비교
				v = a[j]; // 값의 위치를 변경하기 위해 중간에 거치는 값 v에 저장
				k = j;    // 값의 위치를 변경하기 위해 중간에 거치는 값 k에 저장
				while ((k > h - 1) && (a[k - h] > v)) { // 값을 비교하고 더 작은 값을 배열의 앞으로 바꾸는 반복문
					a[k] = a[k - h]; // 배열의 값을 교환
					k -= h; // 다음 값에 대해 반복 시행
				}
				a[k] = v; // 배열의 값을 교환
			}
		}
	}
}

int main() {
	int a[10]; // 크기가 10인 배열 정의
	srand((unsigned int)time(NULL)); // 랜덤 함수를 제대로 실행하기 위해 씀

	for (int i = 0; i < 10; i++) {
		a[i] = rand() % 100 + 1;   // 배열 a의 값들을 1~100 중 랜덤하게 설정
	}

	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);       // 정렬 하기 전 초기 배열 a를 출력
	}
	printf("\n");

	shell_sort(a, 10);  // 배열 a를 shell sort

	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);       // 정렬 후 배열 a를 출력 
	}
	printf("\n");

	return 0;
}