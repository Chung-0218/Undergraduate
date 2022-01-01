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

void shell_sort(int* a, int n) {  // �� ���� ����
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