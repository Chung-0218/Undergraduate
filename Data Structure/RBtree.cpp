#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

typedef struct _node {
	int key;
	char data;
	char color;
	struct _node* left, * right;
	struct _node* red, * black;
}node;

node* head, * tail;

node* rotate(int key, node* pivot, node* base) {
	node* child, * gchild;
	if (key < pivot->key || pivot == head)
		child = pivot->left;
	if (key < child->key) {
		gchild = child->left;
		child->left = gchild->right;
		gchild->right = child;
	}
	else {
		gchild = child->right;
		child->right = gchild->left;
		gchild->left = child;
	}
	if (key < pivot->key || pivot == base)
		pivot->left = gchild;
	else
		pivot->right = gchild;

	return gchild;
}

node* rbti_insert(int key, node* base, int* num) {
	node* t, * parent, * gparent, * ggparent;
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (key == t->key) return NULL;
		if (t->left && t->right && t->left->red && t->right->red) {
			t->red = 1;
			t->left->red = t->right->red = 0;
			if (parent->red) {
				gparent->red = 1;
				if (key < gparent->key != key < parent->key)
					parent = rotate(key, gparent, base);
				t = rotate(key, ggparent, base);
				t->red = 0;
			}
			base->left->red = 0;
		}
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	t = (node*)malloc(sizeof(node));
	t->key = key;
	t->left = NULL;
	t->right = NULL;
	if (key < parent->key || parent == base) parent->left = t;
	else parent->right = t;
	(*num)++;
	t->red = 1;
	if (parent->red) {
		gparent->red = 1;
		if (key < gparent->key != key < parent->key)
			parent = rotate(key, gparent, base);
		t = rotate(key, ggparent, base);
		t->red = 0;
	}
	base->left->red = 0;

	return t;
}

int main() {

	node* n; int *index;

	rbti_insert('y', n, index);
	rbti_insert('o', n, index);
	rbti_insert('u', n, index);
	rbti_insert(' ', n, index);
	rbti_insert('d', n, index);
	rbti_insert('i', n, index);
	rbti_insert('d', n, index);
	rbti_insert(' ', n, index);
	rbti_insert('a', n, index);
	rbti_insert(' ', n, index);
	rbti_insert('g', n, index);
	rbti_insert('o', n, index);
	rbti_insert('o', n, index);
	rbti_insert('d', n, index);
	rbti_insert(' ', n, index);
	rbti_insert('j', n, index);
	rbti_insert('o', n, index);
	rbti_insert('b', n, index);

	return 0;
}