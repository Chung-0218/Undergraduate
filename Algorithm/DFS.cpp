#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 100
#define MAX 100
#define is_stack_empty() (top < 0)

int stack[MAX];
int top;
int check[MAX_NODE]; // marker information

int push(int t) {
	if (top >= MAX - 1) {
		printf("Stack overflow !!\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}

int pop() {
	if (top < 0) {
		printf("Stack underflow !!\n");
		return -1;
	}
	return stack[top--];
}

int stack_empty() {
	return (top < 0);
}

void init_stack() {
	top = -1;
}

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}

int GM[MAX_NODE][MAX_NODE]; // adjacency matrix
FILE* fp;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

node* GL[MAX_NODE];   // adjacency list

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

void input_adjlist(node* a[], int* V, int* E) {
	char vertex[3];
	int i, j;
	node* t;
	printf("\nInput number of node & edge\n");
	scanf("%d""%d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge ->");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
		i = name2int(vertex[1]);          // for symmetric
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
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

void print_adjlist(node* a[], int V) {
	int i;
	node* t;
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%c", int2name(i));
		t = (node*)malloc(sizeof(node));
		t->next = a[i];
		//a[i] = t;
		t = t->next;
		while (t) {
			printf(" -> %c", int2name(t->vertex));
			t = t->next;
		}
		printf("\n");
	}
}

// Assignment 5
void visit(int i) {
	printf("%c ", int2name(i)); // print popped nodes
}

void DFS_recur_matrix(int a[][MAX_NODE], int V, int i) {
	int j;
	check[i] = 1;
	visit(i);
	for (j = 0; j < V; j++) {
		if (a[i][j] != 0)
			if (check[j] == 0)
				DFS_recur_matrix(a, V, j);
	}
}

void DFS_adjmatrix(int a[][MAX_NODE], int V) {
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_matrix(a, V, i);
}

void nrDFS_adjmatrix(int a[][MAX_NODE], int V) {
	int i, j;
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			push(i);
			check[i] = 1;
			while (!stack_empty()) {
				i = pop();
				visit(i);
				for (j = 0; j < V; j++) {
					if (a[i][j] != 0) {
						if (check[j] == 0) {
							push(j);
							check[j] = 1;
						}
					}
				}
			}
		}
	}
}

void DFS_recur_list(node* a[], int V, int i) {
	node* t;
	check[i] = 1;
	visit(i);
	for (t = a[i]; t != NULL; t = t->next)
		if (check[t->vertex] == 0)
			DFS_recur_list(a, V, t->vertex);
}

void DFS_adjlist(node* a[], int V) {
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_list(a, V, i);
}

void nrDFS_adjlist(node* a[], int V) {
	node* t;
	int i;
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			push(i);
			check[i] = 1;
			while (!stack_empty()) {
				i = pop();
				visit(i);
				for (t = a[i]; t != NULL; t = t->next) {
					if (check[t->vertex] == 0) {
						push(t->vertex);
						check[t->vertex] = 1;
					}
				}
			}
		}
	}
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
	printf("\n--adjmatrix--\n");

	// traverse the given graph
	DFS_adjmatrix(GM, V);
	printf("\n");
	nrDFS_adjmatrix(GM, V);
	printf("\n--adjlist--\n");

	// for adjacency list
	DFS_adjlist(GL, V);
	printf("\n");
	nrDFS_adjlist(GL, V);
	printf("\n");
	
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);
	DFS_adjlist(GL, V);
	nrDFS_adjlist(GL, V);
	
	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}