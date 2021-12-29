#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 50
#define MAX_EDGE 100
#define ONLY_FIND 0
#define UNION 1

int parent[MAX_NODE];
int height[MAX_NODE];
int cost = 0;
int nheap = 0;
int heap[MAX_NODE];
FILE* fp;

typedef struct edge {
	int v1, v2;
	int weight;
}edge;

edge Edge[MAX_NODE];

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}

void find_init(int elem) {
	int i;
	for (i = 0; i < elem; i++)
		parent[i] = -1;
}

void union_set(int elem, int asso) {
	parent[elem] = asso;
}

int find_set(int elem, int asso, int flag) {
	int i = elem, j = asso;
	while (parent[i] >= 0)
		i = parent[i];
	while (parent[j] >= 0)
		j = parent[j];
	if (flag == UNION && i != j)
		union_set(i, j);
	return (i != j);
}

int pq_empty() {
	if (nheap == 0) return 1;
	return 0;
}

void pq_init() {
	nheap = 0;
}


void visit(int e) {
	printf("%c%c ", int2name(Edge[e].v1), int2name(Edge[e].v2));
	cost += Edge[e].weight;
}

void upheap(int e[], int k) {
	int v;
	v = e[k];
	while (e[k / 2] <= v && k / 2 > 0) {
		e[k] = e[k / 2];
		k /= 2;
	}
	e[k] = v;
}

void downheap(int e[], int k) {
	int i, v;
	v = e[k];
	while (k <= nheap / 2) {
		i = k << 1;
		if (i < nheap && e[i] < e[i + 1]) i++;
		if (v >= e[i]) break;
		e[k] = e[i];
		k = i;
	}
	e[k] = v;
}

void pq_insert(int h[], int v) {
	h[++nheap] = v;
	upheap(h, nheap);
}

int pq_extract(int h[]) {
	int v = h[1];
	h[1] = h[nheap--];
	downheap(h, 1);
	return v;
}

void kruskal(edge e[], int V, int E) {
	int n, val = 0;
	find_init(V);
	pq_init();
	for (n = 0; n < E; n++)
		pq_insert(heap, n);

	n = 0;
	while (!pq_empty()) {
		val = pq_extract(heap);
		if (find_set(e[val].v1, e[val].v2, UNION)) {
			visit(val);
			n++;
		}
		if (n == V - 1)
			break;
	}
}

void input_edge(edge e[], int* V, int* E) {
	char vertex[3];
	int i, j, w;
	printf("\nInput number of nodes and edges\n");
	fscanf(fp, "%d %d", V, E);
	for (j = 0; j < *E; j++) {
		printf("\nInput two nodes consisting of edge and its weight ->");
		fscanf(fp, "%s %d", vertex, &w);

		vertex[2] = NULL;

		e[j].v1 = name2int(vertex[0]);
		e[j].v2 = name2int(vertex[1]);
		e[j].weight = w;
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point
	
	int V, E;

	fp = fopen("C://Users//정현석//Desktop//4-1강의//알고리즘응용//graph.txt", "rt");

	input_edge(Edge, &V, &E);
	printf("\n\nVisited edge of minimum spanning tree\n");
	kruskal(Edge, V, E);
	printf("\n\nMinimum cost is %d\n", cost);
	fclose(fp);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}