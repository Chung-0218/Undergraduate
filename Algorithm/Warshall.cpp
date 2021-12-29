#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX 100
#define MAX_NODE 100
#define is_stack_empty() (top < 0)
#define UNSEEN (-INT_MAX)

typedef struct node {
	int vertex;
	int weight;
	struct node* next;
}node;

node* G[MAX_NODE];
int GM[MAX_NODE][MAX_NODE];

FILE* fp;
int check[MAX_NODE];
int parent[MAX_NODE];
int stack[MAX];
int top;
int nheap = 0;
int heap[MAX_NODE];

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}

int stack_empty() {
	return (top < 0);
}

void init_stack() {
	top = -1;
}

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

void visit(int i) {
	printf("%c ", int2name(i));
}

void input_adjmatrix(int g[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 0;
	for (i = 0; i < *V; i++)
		g[i][i] = 0;
	for (k = 0; k < *E; k++) {
		printf("\nInput two nodes constisting of edge -> ");
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = 1;
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

void DFS_directed(node* a[], int V) {
	int i, j;
	node* t;
	init_stack();
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++)
			check[j] = 0;

		push(i);
		check[i] = 1;
		printf("\n%c : ", int2name(i));
		while (!stack_empty()) {
			j = pop();
			visit(j);
			for (t = a[j]; t != NULL; t = t->next) {
				if (check[t->vertex] == 0) {
					push(t->vertex);
					check[t->vertex] = 1;
				}
			}
		}
	}
}

void warshall(int a[][MAX_NODE], int V) {
	int x, y, k;

	for (x = 0; x < V; x++)
		a[x][x] = 1;

	for (y = 0; y < V; y++) {
		for (x = 0; x < V; x++) {
			if (a[x][y] == 1) {
				for (k = 0; k < V; k++) {
					if (a[y][k] == 1)
						a[x][k] = 1;
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
	fp = fopen("C://Users//정현석//Desktop//4-1강의//알고리즘응용//directed_graph.txt", "rt");

	input_adjmatrix(GM, &V, &E);
	printf("\n\tOriginal graph\n");
	print_adjmatrix(GM, V);
	// DFS_directed(G, V);
	warshall(GM, V);
	printf("\n\tReachability graph\n");
	print_adjmatrix(GM, V);
	
	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}