#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX 100  // �迭�� ũ�� ����

typedef struct _node {  // ���� ���� ����Ʈ�� ����ü ��� ����
	int key;
	struct _node* left;
	struct _node* right;
}node;

node* head, * tail;
node* stack[MAX];
node* queue[MAX];      // �̶� ������ �Ѹ��� �ּҸ� �����Ƿ� array of pointer�� ����ߴ�!
int top, front, rear;  // ���� ����Ʈ, ����, ť�� ���� ���������� ����

void init_stack() {  // ������ �ʱ�ȭ
	top = -1;        // top = -1�� �ؼ� ������ ���
}

void init_queue() {  // ť�� �ʱ�ȭ
	front = rear = 0; // front = rear�� �ؼ� ť�� ���
}

int is_stack_empty() {  // ������ ����� ��
	return (top == -1);
}

int is_queue_empty() {  // ť�� ����� ��
	return (front == rear);
}

node* push(node* t) {   // ������ Ǫ�� ��� ����, �̋� ��� t�� �ּҰ��� ����
	stack[++top] = t;   // top�� �ּҸ� ���� �� data�� ����
	return t;
}

node* pop() {           // ������ �� ��� ����
	return stack[top--]; // data�� ������ top�� �ּҸ� ���� 
}

node* put(node* t) {    // ť�� put ��� ����
	queue[rear] = t;    
	rear = ++rear % MAX;
	return t;
}

node* get() {           // ť�� get ��� ����
	node* t;
	t = queue[front];
	front = ++front % MAX;
	return t;
}

void init_tree() {      // tree�� �ʱ�ȭ 
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->left = tail;
	head->right = tail;
	tail->left = tail;
	tail->right = tail;
}

int is_operator(int k) {  // ��Ģ������ �޴� ����� ����
	return (k == '+' || k == '-' || k == '*' || k == '/');
}

void visit(node* t) {     // ��带 �湮���� ���̱� ���� ��� ���
	printf("%c ", t->key);
}

node* make_parse_tree(char* p) {  // ���ڿ� postfix ���� �޴� tree �м� ����� ����, ��ǲ:postfix ��, �ƿ�ǲ: �Ѹ� ���
	node* t;  // ���� ��� ����
	while (*p) { // ���� ���� ����
		while (*p == ' ') p++;  // ���ڿ� �Է� p�� ������ �� ����
		t = (node*)calloc(1, sizeof(node)); // ��� t�� ����(�޸� �Ҵ�)
		t->key = *p; // ����� value�� p�� �ּ� ������ ����
		t->left = tail; // t�� ��ũ�� tail�� ����
		t->right = tail; // t�� ��ũ�� tail�� ����
		if(is_operator(*p)) { // ���ڿ� �Է� p�� ���� ��ȣ�� ��
			pop(); // ������ pop ��Ŵ
			visit(t); // ��� t�� �湮(���)
		}
		push(t);   // ���ÿ� ��� t�� Ǫ��
		p++;       // ���� �Է� p�� ���� ����
	}
	return pop();  // ������ pop ���Ѽ� ���� ����
}

void preorder_traverse(node* t) {   // preorder ��� (��� �Լ�)
	if (t != tail) {
		visit(t);
		preorder_traverse(t->left);
		preorder_traverse(t->right);
	}
}

void inorder_traverse(node* t) {    // inorder ���
	if (t != tail) {
		inorder_traverse(t->left);
		visit(t);
		inorder_traverse(t->right);
	}
}

void postorder_traverse(node* t) {  // postorder ���
	if (t != tail) {
		postorder_traverse(t->left);
		postorder_traverse(t->right);
		visit(t);
	}
}

void levelorder_traverse(node* t) { // levelorder ���
	put(t);
	while (!is_queue_empty()) {
		t = get();
		visit(t);

		if (t->left != tail)
			put(t->left);
		if (t->right != tail)
			put(t->right);
	}
}

void main() {
	char post[256];  // �Է� ���� postfix �� ����
	init_stack();    // ���� �ʱ�ȭ
	init_queue();    // ť �ʱ�ȭ
	init_tree();     // Ʈ�� �ʱ�ȭ

	while (1) {      // ���� ����
		printf("\n\nInput postfix expression -> ");
		gets_s(post);  // postfix ���� �Է� ����

		if (*post == NULL) break;  // �Է� ���� postfix ���� �����̸� ����

		head->right = make_parse_tree(post);  // �Է� ���� ���ڿ� p�� �Ѹ� �ּҸ� head�� ������ ���� ����

		printf("\nPre-order travese -> ");
		preorder_traverse(head->right);  // preorder ������� Ʈ���� ���� ������
	}
}