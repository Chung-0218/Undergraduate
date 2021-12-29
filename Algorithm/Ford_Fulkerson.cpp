#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX_NODE 100
#define INT_MAX 100
#define SOURCE 'S'
#define SINK 'T'

FILE* fp;

int Capacity[MAX_NODE][MAX_NODE];
int Flow[MAX_NODE][MAX_NODE];
int Residual[MAX_NODE][MAX_NODE];
int check[MAX_NODE];
int parent[MAX_NODE];
int path[MAX_NODE];
int queue[MAX_NODE];
int front, rear;

void init_queue() {
	front = rear = 0;
}

int queue_empty() {
	if (front == rear) return 1;
	else return 0;
}

void put(int k) {
	queue[rear] = k;
	rear = ++rear % MAX_NODE;
}

int get() {
	int i;
	i = queue[front];
	front = ++front % MAX_NODE;
	return i;
}

int name2int(char c) {
	if (c == SOURCE) return 0;
	if (c == SINK) return 1;
	return c - 'A' + 2;
}

int int2name(int i) {
	if (i == 0) return SOURCE;
	if (i == 1) return SINK;
	return i + 'A' - 2;
}

void clear_matrix(int a[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			a[i][j] = 0;
}

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int capacity;
	int i, j, k;
	printf("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", V, E);
	clear_matrix(a, *V);
	for (k = 0; k < *E; k++) {
		printf("\n Input two Vertex consist of Edge & Capacity -> ");
		fscanf(fp, "%s %d", vertex, &capacity);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = capacity;
	}
}

void print_adjmatrix(int a[][MAX_NODE], int V) {
	int i, j;
	printf("   ");
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

void construct_residual(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			r[i][j] = c[i][j] - f[i][j];
}

void set_path() {
	int* temp;
	int i, count = 0;
	temp = (int*)calloc(MAX_NODE, sizeof(int));
	i = name2int(SINK);
	while (i >= 0) {
		temp[count] = i;
		i = parent[i];
		count++;
	}
	for (i = 0; i < count; i++)
		path[i] = temp[count - i - 1];
	path[i] = -1;
	free(temp);
}

int get_augment_path(int a[][MAX_NODE], int V, int S, int T) {
	int i, j;
	init_queue();
	for (i = 0; i < V; i++) {
		check[i] = 0;
		parent[i] = -1;
	}
	i = name2int(S);
	if (check[i] == 0) {
		put(i);
		check[i] = 1;
		while (!queue_empty()) {
			i = get();
			if (i == name2int(T)) break;
			for (j = 0; j < V; j++) {
				if (a[i][j] != 0) {
					if (check[j] == 0) {
						put(j);
						check[j] = 1;
						parent[j] = i;
					}
				}
			}
		}
	}
	set_path();
	if (i == name2int(T)) return 1;
	else return 0;
}

void network_flow(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V, int S, int T) {
	int i, min;
	clear_matrix(f, V);
	clear_matrix(r, V);
	construct_residual(c, f, r, V);
	print_adjmatrix(r, V);
	while (get_augment_path(r, V, S, T)) {
		min = INT_MAX;
		for (i = 1; path[i] >= 0; i++)
			if (min > r[path[i - 1]][path[i]]) min = r[path[i - 1]][path[i]];
		for (i = 1; path[i] >= 0; i++) {
			f[path[i - 1]][path[i]] = f[path[i - 1]][path[i]] + min;
			f[path[i]][path[i - 1]] = -f[path[i - 1]][path[i]];
		}
		construct_residual(c, f, r, V);
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int V, E;
	fp = fopen("C://Users//정현석//Desktop//4-1강의//알고리즘응용//capacity.txt", "rt");

	input_adjmatrix(Capacity, &V, &E);
	printf("\n\n\tNetwork\n");
	print_adjmatrix(Capacity, V);
	printf("\n");
	network_flow(Capacity, Flow, Residual, V, SOURCE, SINK);
	printf("\n");
	print_adjmatrix(Flow, V);
	fclose(fp);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}