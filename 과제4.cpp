#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

typedef struct _node{
	int key;
	struct _node *next;
}node;

node* head, * tail;

void init_list() {
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;
}

node* ordered_list(int k=5) {
	node* s, * p, * r;
	p = head;
	s = p->next;
	while (s->key <= k && s != tail) {
		p = p->next;
		s = p->next;
	}
	r = (node*)calloc(1, sizeof(node));
	r->key = k;
	p->next = r;
	r->next = s;
	return r;
}

int main() {
	init_list();
	ordered_list(9);
	ordered_list(3);
	ordered_list(5);
	ordered_list(1);
	ordered_list(7);
	printf("%d" );

	return 0;

}