#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h.>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define SIZE 30  // 배열의 크기 정의

void select_sort(int* a, int N) {  // select 정렬 정의 *a는 data, N은 data의 length
	int min;      // 최소값 정의
	int min_idx;  // 최소값의 인덱스(주소) 정의
	int x, y;     // for loop를 위한 두 변수 정의

	for (y = 0; y < N - 1; y++) {  // y는 현재 진행되는 위치
		min_idx = y;   // 최소값의 인덱스를 y로 정의
		min = a[y];    // 최소값을 a의 y인덱스 값으로 정의
		for (x = y + 1; x < N; x++) { // 최소갑을 찾기 위한 반복문 
			if (min > a[x]) {  // min이 최소값이 아닐 경우
				min = a[x];    // min을 a의 x인덱스 값으로 정의
				min_idx = x;   // min의 인덱스를 x로 정의
			}
		}
		a[min_idx] = a[y];
		a[y] = y;          // a[y] 와 a[min_idx] 두 값을 exchange
	}
}

int intcmp(const void* a, const void* b) {// int 형으로 자료형을 변환해주는 함수 정의
	return (*(int*)a - *(int*)b);  // void pointer casting, pointer casting
}

 void gen_select_sort(void* base, int nelem, int width,
					 int (*fcmp)(const void*, const void*)) {   // void pointer, function pointer를 활용한
	void* min; // void형 최소값 정의                                select 정렬의 일반형 (모든 자료형에 대해)
	int min_idx;
	int x, y;

	min = malloc(width);  // min을 메모리 할당 받음
	for(y = 0; y < nelem-1; y++) { // 현재 진행위치 y에 대해 for loop 실행
		min_idx = y;  // min의 인덱스를 y로 정의
		memcpy(min, (char*)base + y * width, width);  // min = a[y]와 같은 의미
		for (x = y + 1; x < nelem; x++) { // 최소갑을 찾기 위한 반복문
			if (fcmp(min, (char*)base + x * width) > 0) { // min > a[x]일 때 실행과 같은 의미
				memcpy(min, (char*)base + x * width, width); // min = a[x]와 같은 의미
				min_idx = x; // min의 인덱스를 x로 정의
			}
		}
		memcpy((char*)base + min_idx * width, (char*)base + y * width, width); // a[min_idx] = a[y]와 같은 의미
		memcpy((char*)base + y * width, min, width);                           // a[y] = min와 같은 의미 즉, 두 값을 exchange
	}
	free(min); // 메모리 해제
} 

void main() {
	int number[SIZE] = { 9,4,5,1,3,9 }; // 정렬 할 배열 정의

	select_sort(number, 6); // select 정렬

	gen_select_sort(number, 6, sizeof(int), intcmp); // general select 정렬
}
