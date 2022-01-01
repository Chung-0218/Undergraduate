#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define MAX 100  // 배열의 크기 정의

typedef struct _node {  // 더블 연결 리스트의 구조체 노드 정의
	int key;
	struct _node* left;
	struct _node* right;
}node;

node* head, * tail;
node* stack[MAX];
node* queue[MAX];      // 이때 스택은 뿌리의 주소를 받으므로 array of pointer를 사용했다!
int top, front, rear;  // 연결 리스트, 스택, 큐에 쓰일 전역변수들 정의

void init_stack() {  // 스택을 초기화
	top = -1;        // top = -1로 해서 스택을 비움
}

void init_queue() {  // 큐를 초기화
	front = rear = 0; // front = rear로 해서 큐를 비움
}

int is_stack_empty() {  // 스택이 비었을 때
	return (top == -1);
}

int is_queue_empty() {  // 큐가 비었을 때
	return (front == rear);
}

node* push(node* t) {   // 스택의 푸쉬 기능 정의, 이떄 노드 t의 주소값을 리턴
	stack[++top] = t;   // top의 주소를 증가 후 data를 넣음
	return t;
}

node* pop() {           // 스택의 팝 기능 정의
	return stack[top--]; // data를 빼고나서 top의 주소를 감소 
}

node* put(node* t) {    // 큐의 put 기능 정의
	queue[rear] = t;    
	rear = ++rear % MAX;
	return t;
}

node* get() {           // 큐의 get 기능 정의
	node* t;
	t = queue[front];
	front = ++front % MAX;
	return t;
}

void init_tree() {      // tree를 초기화 
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->left = tail;
	head->right = tail;
	tail->left = tail;
	tail->right = tail;
}

int is_operator(int k) {  // 사칙연산을 받는 기능을 정의
	return (k == '+' || k == '-' || k == '*' || k == '/');
}

void visit(node* t) {     // 노드를 방문함을 보이기 위한 출력 기능
	printf("%c ", t->key);
}

node* make_parse_tree(char* p) {  // 문자열 postfix 식을 받는 tree 분석 기능을 정의, 인풋:postfix 식, 아웃풋: 뿌리 노드
	node* t;  // 받을 노드 정의
	while (*p) { // 무한 루프 정의
		while (*p == ' ') p++;  // 문자열 입력 p가 공백일 때 종료
		t = (node*)calloc(1, sizeof(node)); // 노드 t를 생성(메모리 할당)
		t->key = *p; // 노드의 value를 p의 주소 값으로 받음
		t->left = tail; // t의 링크를 tail에 연결
		t->right = tail; // t의 링크를 tail에 연결
		if(is_operator(*p)) { // 문자열 입력 p가 연산 기호일 때
			pop(); // 스택을 pop 시킴
			visit(t); // 노드 t를 방문(출력)
		}
		push(t);   // 스택에 노드 t를 푸쉬
		p++;       // 다음 입력 p에 대해 실행
	}
	return pop();  // 스택을 pop 시켜서 최종 종료
}

void preorder_traverse(node* t) {   // preorder 방법 (재귀 함수)
	if (t != tail) {
		visit(t);
		preorder_traverse(t->left);
		preorder_traverse(t->right);
	}
}

void inorder_traverse(node* t) {    // inorder 방법
	if (t != tail) {
		inorder_traverse(t->left);
		visit(t);
		inorder_traverse(t->right);
	}
}

void postorder_traverse(node* t) {  // postorder 방법
	if (t != tail) {
		postorder_traverse(t->left);
		postorder_traverse(t->right);
		visit(t);
	}
}

void levelorder_traverse(node* t) { // levelorder 방법
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
	char post[256];  // 입력 받을 postfix 식 저장
	init_stack();    // 스택 초기화
	init_queue();    // 큐 초기화
	init_tree();     // 트리 초기화

	while (1) {      // 무한 루프
		printf("\n\nInput postfix expression -> ");
		gets_s(post);  // postfix 식을 입력 받음

		if (*post == NULL) break;  // 입력 받은 postfix 식이 공백이면 종료

		head->right = make_parse_tree(post);  // 입력 받은 문자열 p의 뿌리 주소를 head의 오른쪽 노드로 보냄

		printf("\nPre-order travese -> ");
		preorder_traverse(head->right);  // preorder 방법으로 트리를 전부 지나감
	}
}