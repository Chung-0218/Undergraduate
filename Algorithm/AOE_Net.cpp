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

typedef struct _node {
	int vertex;
	int weight;
	struct _node* next;
}node;

typedef struct _head {
	int count;
	struct _node* next;
}head;

head network[MAX_NODE];
int stack[MAX];
int top;
int check[MAX_NODE];
int earliest[MAX_NODE];
int latest[MAX_NODE];
FILE* fp;

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

void input_adjlist(head net[], int* V, int* E) {
	char vertex[3];
	int i, j, w;
	node* t;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++) net[i].next = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two nodes consist of edge & weight -> ");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->weight = w;
		t->next = net[name2int(vertex[0])].next;
		net[name2int(vertex[0])].next = t;
	}
}

void print_adjlist(head net[], int V) {
	int i;
	node* t;
	for (i = 0; i < V; i++) {
		printf("\n%c : ", int2name(i));
		for (t = net[i].next; t != NULL; t = t->next)
			printf("-> %c : %d ", int2name(t->vertex), t->weight);
	}
}

void set_count_indegree(head net[], int V) {
	int i, j;
	int count;
	node* t;
	for (i = 0; i < V; i++) {
		count = 0;
		for (j = 0; j < V; j++)
			for (t = net[j].next; t; t = t->next)
				if (t->vertex == i) count++;
		net[i].count = count;
	}
}

void topsort(head net[], int V) {
	int i, j, k;
	node* ptr;
	init_stack();

	set_count_indegree(net, V);

	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (stack_empty()) exit(1);
		else {
			j = pop();
			printf("%c, ", int2name(j));
			for (ptr = net[j].next; ptr; ptr = ptr->next) {
				k = ptr->vertex;
				net[k].count--;
				if (!net[k].count)
					push(k);
			}
		}
	}
}

void set_count_outdegree(head net[], int V) {
	int i, count;
	node* t;
	for (i = 0; i < V; i++) {
		count = 0;
		for (t = net[i].next; t; t = t->next)
			count++;
		net[i].count = count;
	}
}

void revtopsort(head net[], int V) {
	int i, j, k;
	node* ptr;
	init_stack();

	set_count_outdegree(net, V);

	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (stack_empty()) exit(1);
		else {
			j = pop();
			printf("%c, ", int2name(j));
			for (k = 0; k < V; k++)
				for (ptr = net[k].next; ptr; ptr = ptr->next)
					if (ptr->vertex == j) {
						net[k].count--;
						if (!net[k].count)
							push(k);
					}
		}
	}
}

void forward_stage(head net[], int V) {
	int i, j, k;
	node* ptr;

	init_stack();
	set_count_indegree(net, V);

	for (i = 0; i < V; i++) earliest[i] = 0;
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (!stack_empty()) {
			j = pop();
			for (ptr = net[j].next; ptr; ptr = ptr->next) {
				k = ptr->vertex;
				net[k].count--;
				if (!net[k].count)
					push(k);
				if (earliest[k] < earliest[j] + ptr->weight)
					earliest[k] = earliest[j] + ptr->weight;
			}
		}
	}
}

void backward_stage(head net[], int V) {
	int i, j, k, l;
	node* ptr;

	init_stack();
	set_count_outdegree(net, V);

	for (i = 0; i < V; i++)
		latest[i] = earliest[V - 1];
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (!stack_empty()) {
			j = pop();
			for (l = 0; l < V; l++) {
				for (ptr = net[l].next; ptr; ptr = ptr->next) {
					if (ptr->vertex == j) {
						k = l;
						net[k].count--;
						if (!net[k].count)
							push(k);
						if (latest[k] > latest[j] - ptr->weight)
							latest[k] = latest[j] - ptr->weight;
					}
				}
			}
		}
	}
}

void print_critical_activity(head net[], int V) {
	int i;
	int e, l;
	node* t;

	printf("\n\nCritical Activities");
	printf("\n 간선    Early     Late     Late-Early   임계?"
		 "\n-----    -----    ------    ----------  ------");
	for (i = 0; i < V; i++) {
		for (t = net[i].next; t; t = t->next) {
			e = earliest[i];
			l = latest[t->vertex] - t->weight;
			printf("\n<%c,%c>  "
				"   %-4d       %-4d      %-4d       %-4s",
				int2name(i), int2name(t->vertex), e, l, l - e,
				(l - e == 0) ? "Y" : "N");
		}
	}
}

int main() {

	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start);  // starting point

	int k, V, E;
	fp = fopen("C://Users//정현석//Desktop//4-1강의//알고리즘응용//AOE_network.txt", "rt");

	input_adjlist(network, &V, &E);
	printf("\n\nOriginal graph\n");
	print_adjlist(network, V);

	forward_stage(network, V);
	backward_stage(network, V);
	print_critical_activity(network, V);
	fclose(fp);

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("\n");
	printf("프로그램 실행시간: %.6f초\n", diff);

	return 0;
}