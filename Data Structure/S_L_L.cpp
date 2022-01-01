#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node     // Simple Linked List를 위한 node 정의
{
	int key;             // data 저장을 위한 variable
	struct _node* next;  // 노드의 다음을 표시 할 주소 값(노드와 노드를 연결)
}node;                   // 구조체 node

node* head, * tail;      // 두 전역변수 정의 head는 첫번째 노드, tail은 마지막 노드

void init_list()         // Linked List의 초기화
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;   // 두 전역변수에 동적 메모리 할당을 하고, 초기화 함
}

node* insert_after(int k, node* t)  // 노드를 삽입하는 기능 정의
{
	node* temp;  // 새로운 노드의 주소 값 정의
	temp = (node*)calloc(1, sizeof(node)); // 노드에 메모리 할당
	temp->key = k;         // 새로운 노드에 data 값 k를 넣음
	temp->next = t->next;  // temp 노드의 next를 다음 노드의 data 값에 연결
	t->next = temp;        // 이전 노드의 next를 temp의 data 값에 연결

	return temp;           // tail에 갈 때 까지 반복 시행(다시 temp로 리턴)
}

int delete_next(node* t)      // 노드 t의 다음 노드를 삭제하는 기능 정의
{
	node* temp;               // 새로운 노드 temp 정의
	if (t->next == tail)      // tail에 갈 때 까지 시행 (현재 노드 위치를 확인)
		return 0;             // tail이면 종료 (list가 비어있는 경우)
	temp = t->next;           // 노드 t의 next를 temp에 연결
	t->next = t->next->next;  // 노드 t의 next를 그 다다음 노드로 연결
	free(temp);               // temp 노드를 메모리 해제(삭제)

	return 1;                 // 시행 종료
}

node* find_node(int k)        // data 값 k를 갖는 특정 노드를 찾는 기능
{
	node* temp;               // 새로운 노드의 주소를 temp로 정의

	temp = head->next;        // head의 다음 노드의 포인터 주소를 temp로 정의
	while (temp->key != k && temp != tail)  // temp의 data 값이 k가 아니고 temp 노드가 마지막이 아닐 때 다음을 시행
		temp = temp->next;    // temp를 다음 노드로 연결, 다음 노드에 대해 시행

	return temp;              // temp로 리턴해서 계속 시행
}

int delete_node(int k)        // 특정 data 값 k를 포함하는 노드를 삭제하는 기능
{
	node* s, * p;             // 현재 노드의 주소 s와 이전 노드의 주소 p를 정의
	p = head;                 // 처음에 p를 head의 주소로 정의
	s = p->next;              // s는 p의 다음 노드의 주소로 정의
	while (s->key != k && s != tail)  // s의 data 값이 k가 아니고
	{                                 // s가 tail이 아닐 때 다음을 시행
		p = p->next;          // p를 그 다음 노드로 정의
		s = p->next;          // s를 p 다음 노드로 정의
	}
	if (s != tail) {          // s가 tail노드가 아닐 때 다음을 시행(특정 값의 노드를 찾았을 때)
		p->next = s->next;    // p의 next를 s의 next로 연결
		free(s);              // 노드 s의 메모리 해제(삭제)
		return 1;             // 1로 리턴하여 시행 종료
	}
	else return 0;            // data 값 k를 찾을 때 까지 시행
}

node* insert_node(int t, int k)  // data 값 t를 k 앞 노드의 값에 삽입
{
	node* s, * p, * r;  // 세 노드의 주소 값 정의
	p = head;           // p의 주소를 head로 정의
	s = p->next;        // s의 주소를 p의 다음 노드로 정의
	while (s->key != k && s != tail) {  // 노드 s의 값이 k가 아니고 s가 tail 아닐 때 시행 
		p = p->next;    // p를 그 다음 노드로 정의
		s = p->next;    // s를 p 다음 노드로 정의
	}
	if (s != tail) {    // s가 tail이 아닐 때 시행
		r = (node*)calloc(1, sizeof(node)); // 노드 r을 메모리 할당 받음(새로 정의)
		r->key = t;     // r의 data 값을 t로 정의
		p->next = r;    // p의 다음 노드를 r로 정의
		r->next = s;    // r의 다음 노드를 s로 정의
	}
	return p->next;     // 삽입한 노드의 주소로 리턴
}

node* ordered_insert(int k)  // k 값을 갖는 노드를 찾고 정렬하는 기능
{
	node* s, * p, * r;  // 세 노드의 주소 값 정의
	p = head;           // 노드 p를 head로 정의(head의 주소 값 = p)
	s = p->next;        // s를 노드 p의 다음 노드의 주소 값으로 정의
	while (s->key <= k && s != tail) { // 노드 s의 값이 k 이하 이고, 노드 s가 tail이 아닐 때 다음을 시행
		p = p->next;    // p를 그 다음 노드로 정의
		s = p->next;;   // s를 p 다음 노드로 정의
	}                   // 위 while 반복문이 끝나면 다음을 시행
	r = (node*)calloc(1, sizeof(node)); // 노드 r을 메모리 할당 받음(새로 정의)
	r->key = k;         // 노드 r의 data 값을 k로 정의
	p->next = r;        // p의 다음 노드를 r로 정의
	r->next = s;        // r의 다음 노드를 s로 정의
	return r;           // 노드 r을 리턴
}

node* delete_all()      // 모든 노드를 삭제 하는 기능
{
	node* s;
	node* t;            // 두 노드의 주소 값 정의
	t = head->next;     // 노드 t를 head의 다음 노드로 정의
	while (t!= tail) {  // 노드 t가 tail이 아닐 때 다음을 반복 시행
		s = t;          // 노드 s를 노드 t로 정의
		t = t->next;    // 노드 t를 t의 다음 노드로 시행
		free(s);        // 노드 s를 삭제(메모리 해제)
	}                   // 노드 s가 tail 노드 일때 시행 종료
	head->next = tail;  // head의 다음 노드를 tail로 정의
	return head;        // head를 리턴
}

node* print_node(node* t)    // 현재 리스트(모든 노드)를 출력하는 기능
{
	t = head->next;
	while (t != tail) {
		if (head == tail) {  // 현재 list에 아무 값도 없을 경우
			printf("List에 값이 없습니다 \n");
			t = t->next;     // 다음 노드에 대해 시행
			return 0;
		}
		else{
			printf("%d ", (int)t->key); // 현재 노드들의 data 값을 순서대로 출력
			t = t->next;     // 다음 노드에 대해 시행
			
		}
	}
	printf("\n----------------\n");
}

int main() {
	node* t = NULL;      // 노드 t를 정의

	init_list();         // 연결 리스트 초기화
	ordered_insert(9);
	ordered_insert(3);
	ordered_insert(5); 
	ordered_insert(1); 
	ordered_insert(7);   // 각 노드들 삽입

	print_node(t);       // 현재 연결 리스트를 출력

	ordered_insert(5);   // 노드 5를 정렬
	find_node(5);        // 노드 5를 찾음
	
	insert_node(6, 5);   // 노드 6을 5 다음에 삽입

	print_node(t);       // 현재 연결 리스트를 출력

	delete_node(5);      // 노드 5를 삭제

	print_node(t);       // 현재 연결 리스트를 출력

	delete_all();        // 모든 노드를 삭제

	print_node(t);       // 현재 연결 리스트를 출력

	return 0;
}