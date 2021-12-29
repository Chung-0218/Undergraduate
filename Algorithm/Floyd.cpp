#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 100
#define INFINITE 100

int d[MAX_NODE][MAX_NODE];
FILE* fp;

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}

void visit(int i) {
	printf("%c ", int2name(i));
}

void input_adjmatrix(int d[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k, w;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);	
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			d[i][j] = INFINITE;
	for (i = 0; i < *V; i++)
		d[i][i] = 0;
	for (k = 0; k < *E; k++) {
		printf("\nInput two nodes constisting of edge and weight -> ");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		d[i][j] = w;
	}
}

void print_adjmatrix(int d[][MAX_NODE], int V) {
	int i, j;
	printf("\n   "); // for display
	for (i = 0; i < V; i++)
		printf("%3c", int2name(i));
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%3c", int2name(i));
		for (j = 0; j < V; j++)
			printf("%3d", d[i][j]);
		printf("\n");
	}
}

void floyd(int d[][MAX_NODE], int V) {
	int x, y, k;
	for (y = 0; y < V; y++)
		for (x = 0; x < V; x++)
			for (k = 0; k < V; k++)
				if (d[x][y] + d[y][k] < d[x][k])
					d[x][k] = d[x][y] + d[y][k];
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int V, E;
	fp = fopen("C://Users//정현석//Desktop//4-1강의//알고리즘응용//floyd_graph.txt", "rt");

	input_adjmatrix(d, &V, &E);
	printf("\n\tOriginal graph\n");
	print_adjmatrix(d, V);
	floyd(d, V);
	printf("\n\tResult of Floyd\n");
	print_adjmatrix(d, V);

	fclose(fp);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}