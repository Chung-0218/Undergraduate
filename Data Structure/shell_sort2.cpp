#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define LEN 5

typedef struct _node{ struct _node * next; } node;
typedef int(*FCMP)(const void*, const void*);

void init_list(node** p) {
	*p = (node*)malloc(sizeof(node));
	(*p)->next = NULL;
}

int intcmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void* llv_insert(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* t;
	t = (node*)malloc(sizeof(node) + width);
	memcpy(t + 1, key, width);
	t->next = base->next;
	base->next = t;
	(*num)++;
	return t;
}

void* llv_search(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* t;
	t = base->next;
	while (fcmp(t + 1, key) != 0 && t != NULL) t = t->next;
	return (t == NULL ? NULL : t + 1);
}

void* llv_delete(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* t, *r;
	t = base;
	r = base->next;
	if (r != NULL) {
		if ((r = (node*)llv_search(key, base, num, width, fcmp)) == NULL)
			return NULL;
		r = r - 1;
		t = base;
		while(t->next != r)
			t = t->next;
		t->next = r->next;
		free(r);
		(*num)--;
		return t;
	}
	return NULL;
}

void* llfv_search(void* key, node* base, int* num, int width, FCMP fcmp) {
	void* v;
	void* t;

	if ((v = llv_search(key, base, num, width, fcmp)) == NULL)
		return v;
	t = malloc(width);
	memcpy(t, v, width);
	llv_delete(key, base, num, width, fcmp);
	v = llv_insert(t, base, num, width, fcmp);
	free(t);
	
	return v;
}

void shell_sort(int* a, int n) {  // 쉘 정렬 정의
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
	void* p;
	node* t, * head;
	int size = 0, key = 9;
	int data[LEN] = { 3,1,9,7,5 };

	init_list(&t);
	shell_sort(data, 5);

	int i;
	for (i = 0; i < 5; i++) {
		p = llv_insert(data + i, t, &size, sizeof(int), intcmp);
		printf("%d\n", *((node*)p + 1));
	}

	return 0;
}
