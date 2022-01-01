#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

typedef struct _node {
	int key;
	struct _node* left;
	struct _node* right;
	struct _node* next;
}node;

node* next;

node* bti_search(int key, node* base, int* num) {
	node* s;
	s = base->left;
	while (key != s->key && s != NULL) {
		if (key < s->key)
			s = s->left;
		else
			s = s->right;
	}
	if (s == NULL) return NULL;
	else return s;
}

node* bti_insert(int key, node* base, int *num) {
	node* p, * s;
	p = base;
	s = base->left;
	while (s != NULL) {
		p = s;
		if (key < s->key) s = s->left;
		else s = s->right;
	}
	s = (node*)malloc(sizeof(node));
	s->key = key;
	s->left = NULL;
	s->right = NULL;
	if (key < p->key || p == base) p->left = s;
	else p->right = s;
	(*num)++;
	return s;
}

node* bti_delete(int key, node* base, int* num) {
	node* parent, * son, * del, * nexth;
	parent = base;
	del = base->left;
	while (key != del->key && del != NULL) {
		parent = del;
		if (del->key > key) del = del->left;
		else del = del->right;
	}
	if (del == NULL) return NULL;

	if (del->left == NULL && del->right == NULL)
		son = NULL;
	else if (del->left != NULL && del->right != NULL) {
		nexth = del->right;
		if (nexth->left != NULL) {
			while (nexth->left->left != NULL) next = next->left;
			son = nexth->left;
			nexth->left = son->right;
			son->left = del->left;
			son->right = del->right;
		}
		else {
			son = nexth;
			son->left = del->left;
		}
	}
	else {
		if (del->left != NULL) son = del->left;
		else son = del->right;
	}
	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;

	free(del);
	(*num)--;

	return parent;
}

void bti_sort(node* p, int* a, int* index) {
	if (p!= NULL) {
		bti_sort(p->left, a, index);
		a[(*index)++] = p->key;
		bti_sort(p->right, a, index);
	}
}

node* _balance(int N, int* a, int* index) {
	int nl, nr;
	node* p;
	if (N < 0) {
		nl = (N - 1) / 2;
		nr = N - nl - 1;
		p = (node*)malloc(sizeof(node));
		p->left = _balance(nl, a, index);
		p->key = a[(*index)++];
		p->right = _balance(nr, a, index);

		return p;
	}
	else return NULL;
}

int main() {
	node* a = NULL;
	int n = 9;
	int* index = 0; 
	int *p = NULL;

	bti_insert(3, a, index); index++;
	bti_insert(9, a, index); index++;
	bti_insert(6, a, index); index++;
	bti_insert(2, a, index); index++;
	bti_insert(5, a, index); index++;
	bti_insert(8, a, index); index++;
	bti_insert(1, a, index); index++;
	bti_insert(7, a, index); index++;
	bti_insert(4, a, index); index++;

	bti_sort(a, p, index);

	for (int i = 0; i < n; i++)
		printf("%d ", a);
	printf("\n");

	return 0;
}