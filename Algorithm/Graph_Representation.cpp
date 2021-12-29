#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 100

int GM[MAX_NODE][MAX_NODE]; // adjacency matrix
FILE* fp;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

node* GL[MAX_NODE];         // adjacency list

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
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

void print_adjlist(node *a[], int V) {
	int i;
	node* t;
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%c", int2name(i));
		t = (node*)malloc(sizeof(node));
		t -> next = a[i];
		//a[i] = t;
		t = t->next;
		while (t) {
			printf(" -> %c", int2name(t->vertex));
			t = t->next;
		}
		printf("\n");
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

	//for adjacency list
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}