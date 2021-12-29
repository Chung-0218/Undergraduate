#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 50

typedef struct _dnode {
	int key;
	struct _dnode* prev;
	struct _dnode* next;
}dnode;

dnode* head, * tail;
int check[MAX_NODE];

int GM[MAX_NODE][MAX_NODE]; // adjacency matrix
FILE* fp;

dnode* GL[MAX_NODE];        // adjacency list

void init_queue() {
	head = (dnode*)calloc(1, sizeof(dnode));
	tail = (dnode*)calloc(1, sizeof(dnode));
	head->prev = head;
	head->next = tail;
	tail->prev = head;
	tail->next = tail;
}

int name2int(char c) {
	return c - 'A';
}

int int2name(int i) {
	return i + 'A';
}

void visit(int i) {
	printf("%c ", int2name(i));
}

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k;
	printf("\nInput number of node & edge\n");
	scanf("%d""%d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = 0;
	for (i = 0; i < *V; i++)
		a[i][i] = 1;
	for (k = 0; k < *E; k++) {
		printf("\nInput two node consist of edge ->");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = 1;
		a[j][i] = 1;
	}
}

void print_adjmatrix(int a[][MAX_NODE], int V) {
	int i, j;
	printf("\n   "); // for display
	for (i = 0; i < V; i++)
		printf("%3c", int2name(i));
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%3c", int2name(i));
		for (j = 0; j < V; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
}

int put(int k) {
	dnode* t;
	if ((t = (dnode*)malloc(sizeof(dnode))) == NULL){
		printf("Out of memory !\n");
		return -1;
	}
	t->key = k;
	tail->prev->next = t;
	t->prev = tail->prev;
	tail->prev = t;
	t->next = tail;
	return k;
}

int get() {
	dnode* t;
	int k;
	t = head->next;
	if (t == tail) {
		printf("Queue underflow\n");
		return -1;
	}
	k = t->key;
	head->next = t->next;
	t->next->prev = head;
	free(t);
	return k;
}

bool queue_empty() {
	if (head->next == tail && tail->prev == head) return true;
	else return false;
}

void BFS_adjmatrix(int a[][MAX_NODE], int V) {
	int i, j;
	init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			put(i);
			check[i] = 1;
			while (!queue_empty()) {
				i = get();
				visit(i);
				for (j = 0; j < V; j++) {
					if (a[i][j] != 0) {
						if (check[j] == 0) {
							put(j);
							check[j] = 1;
						}
					}
				}
			}
		}
	}
}

void BFS_adjlist(dnode* a[], int V) {
	int i;
	dnode* t;
	init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			put(i);
			check[i] = 1;
			while (!queue_empty()) {
				i = get();
				visit(i);
				for(t=a[i]; t!= NULL; t=t->next)
					if (check[t->key] == 0) {
						put(t->key);
						check[t->key] = 1;
					}
			}
		}
	}
}

void count_components(int a[][MAX_NODE], int V) {
	int cnt = 0;
	int i, j;
	init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			++cnt;
			put(i);
			check[i] = 1;
			while (!queue_empty()) {
				i = get();
				printf("%c ", int2name(i));
				for (j = 0; j < V; j++) {
					if(a[i][j]!=0)
						if (check[j] == 0) {
							put(j);
							check[j] = 1;
						}
				}
			}
		}
	}
	printf("\n# of CC : %d\n", cnt);
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int V, E;

	// for adjacency matrix
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);
	
	// traverse the given graph
	printf("\n---adjmatrix---\n");
	BFS_adjmatrix(GM, V);	
	printf("\n---adjlist---\n");
	BFS_adjlist(GL, V);
	printf("\n---# of components---\n");
	count_components(GM, V);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}