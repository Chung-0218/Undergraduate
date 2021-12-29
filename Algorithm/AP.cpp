#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 100

int check[MAX_NODE];
int order;
int son_of_root;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

node* GL[MAX_NODE];   // adjacency list

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}

void visit(int i) {
	printf("%c ", int2name(i));
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

int AP_recur(node* a[], int i) {
	node* t;
	int min, m;
	check[i] = min = ++order;
	for (t = a[i]; t != NULL; t = t->next) {
		if (i == 0 && check[t->vertex] == 0)  
			son_of_root++;
		if (check[t->vertex] == 0) {
			m = AP_recur(a, t->vertex);
			if (m < min) min = m;
			if (m >= check[i] && i != 0)
				printf("* %c %2d : %d\n", int2name(i), check[i], m);
			else
				printf("%c %2d : %d\n", int2name(i), check[i], m);
		}
		else
			if (check[t->vertex] < min)
				min = check[t->vertex];
	}
	return min;
}

void AP_search(node* a[], int V) {
	int i, n = 0;
	node* t;

	for (i = 0; i < V; i++) check[i] = 0; // 방문 안한 상태로 set
	order = son_of_root = 0;
	AP_recur(a, 0);						  // 'A' 노드 부터 방문 시작 (root node)

	if (son_of_root > 1) printf("* ");    // 2이상 이면 단절점
	else printf("   ");
	printf("%c son : %d\n", int2name(0), son_of_root);
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int V, E;

	input_adjlist(GL, &V, &E);
	printf("\n---adjlist---");
	print_adjlist(GL, V);
	printf("---DFS---\n");
	DFS_adjlist(GL, V);
	printf("\n---Articulation point---\n");
	AP_search(GL, V);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}