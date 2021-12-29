#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 100
#define UNSEEN (-INT_MAX)
#define INFINITE 100

int GM[MAX_NODE][MAX_NODE];

int check[MAX_NODE];
int parent[MAX_NODE];
int distance[MAX_NODE];
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

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k, w;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = INFINITE;
	for (i = 0; i < *V; i++)
		a[i][i] = 0;
	for (k = 0; k < *E; k++) {
		printf("\nInput two nodes constisting of edge and weight -> ");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = a[j][i] = w;
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

void print_distance(int distance[], int s, int V) {
	int i;
	printf("\n   ");
	for (i = 0; i < V; i++)
		printf("%3d ", distance[i]);
}

void print_parent(int g[], int V) {    // print parent node
	printf("\n");
	for (int i = 1; i < V; i++) {
		printf("%c ", int2name(parent[i]));
	}
}

void dijkstra(int a[][MAX_NODE], int s, int V) {
	int x = 0, y, d;
	int i, checked = 0;
	for (x = 0; x < V; x++) {
		distance[x] = a[s][x];
		if (x != s) parent[x] = s;
	}
	check[s] = 1;
	checked++;

	print_distance(distance, s, V);

	while (checked < V) {
		x = 0;
		while (check[x]) x++;
		for (i = x; i < V; i++)
			if (check[i] == 0 && distance[i] < distance[x]) x = i;		
		check[x] = 1;
		checked++;

		for (y = 0; y < V; y++) {
			if (x == y || a[x][y] >= INFINITE || check[y]) continue;
			d = distance[x] + a[x][y];
			if (d < distance[y]) {
				distance[y] = d;
				parent[y] = x;
			}
		}
		print_distance(distance, x, V);
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int V, E;
	fp = fopen("C://Users//정현석//Desktop//4-1강의//알고리즘응용//graph.txt", "rt");

	input_adjmatrix(GM, &V, &E);
	printf("\nOriginal graph");
	print_adjmatrix(GM, V);
	printf("\nResult of dijkstra\n");
	dijkstra(GM, 5, V);
	printf("\n\nParent node");
	print_parent(parent, V);
	fclose(fp);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}