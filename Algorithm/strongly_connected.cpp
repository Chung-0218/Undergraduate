#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 100
#define MAX 100
#define INFINITE 100
#define is_stack_empty() (top < 0)

FILE* fp;
int top;
int stack[MAX];
int check[MAX_NODE];
int order;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

node* G[MAX_NODE];

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

void visit(int i) {
	printf("%c ", int2name(i));
}

void input_adjlist(node* a[], int* V, int* E)
{
	char vertex[3];
	int i, j;
	node* t;
	printf("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++)
	{
		printf("\nInput two Vertex consist of Edge  -> ");
		fscanf(fp, "%s", vertex);

		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
	}
}

void print_adjlist(node* a[], int V)
{
	int i;
	node* t;
	for (i = 0; i < V; i++)
	{
		printf("\n%c : ", int2name(i));
		for (t = a[i]; t != NULL; t = t->next)
			printf("-> %c ", int2name(t->vertex));
	}
}

int strong_recur(node* g[], int i) {
	int m, min, k, flag;
	node* t;
	check[i] = min = ++order;
	push(i);
	for (t = g[i]; t != NULL; t = t->next) {
		if (check[t->vertex] == 0)
			m = strong_recur(g, t->vertex);
		else
			m = check[t->vertex];
		if (m < min) min = m;
	}
	if (min == check[i]) {
		flag = 0;
		while ((k = pop()) != i) {
			printf("%c ", int2name(k));
			check[k] = MAX_NODE + 1;
			flag = 1;
		}
		if (flag) printf("%c\n", int2name(k));
	}
	return min;
}

void strong(node* g[], int V) {
	int x;
	for (x = 0; x < V; x++)
		check[x] = 0;
	for (x = 0; x < V; x++) {
		if (check[x] == 0)
			strong_recur(g, x);
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int V, E;

	fp = fopen("C://Users//정현석//Desktop//4-1강의//알고리즘응용//directed_graph.txt", "rt");

	input_adjlist(G, &V, &E);
	printf("\nOriginal Graph");
	print_adjlist(G, V);
	printf("\n\nStrongly connected components\n");
	strong(G, V);

	fclose(fp);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}