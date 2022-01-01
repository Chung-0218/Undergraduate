#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node     // Simple Linked List�� ���� node ����
{
	int key;             // data ������ ���� variable
	struct _node* next;  // ����� ������ ǥ�� �� �ּ� ��(���� ��带 ����)
}node;                   // ����ü node

node* head, * tail;      // �� �������� ���� head�� ù��° ���, tail�� ������ ���

void init_list()         // Linked List�� �ʱ�ȭ
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;   // �� ���������� ���� �޸� �Ҵ��� �ϰ�, �ʱ�ȭ ��
}

node* insert_after(int k, node* t)  // ��带 �����ϴ� ��� ����
{
	node* temp;  // ���ο� ����� �ּ� �� ����
	temp = (node*)calloc(1, sizeof(node)); // ��忡 �޸� �Ҵ�
	temp->key = k;         // ���ο� ��忡 data �� k�� ����
	temp->next = t->next;  // temp ����� next�� ���� ����� data ���� ����
	t->next = temp;        // ���� ����� next�� temp�� data ���� ����

	return temp;           // tail�� �� �� ���� �ݺ� ����(�ٽ� temp�� ����)
}

int delete_next(node* t)      // ��� t�� ���� ��带 �����ϴ� ��� ����
{
	node* temp;               // ���ο� ��� temp ����
	if (t->next == tail)      // tail�� �� �� ���� ���� (���� ��� ��ġ�� Ȯ��)
		return 0;             // tail�̸� ���� (list�� ����ִ� ���)
	temp = t->next;           // ��� t�� next�� temp�� ����
	t->next = t->next->next;  // ��� t�� next�� �� �ٴ��� ���� ����
	free(temp);               // temp ��带 �޸� ����(����)

	return 1;                 // ���� ����
}

node* find_node(int k)        // data �� k�� ���� Ư�� ��带 ã�� ���
{
	node* temp;               // ���ο� ����� �ּҸ� temp�� ����

	temp = head->next;        // head�� ���� ����� ������ �ּҸ� temp�� ����
	while (temp->key != k && temp != tail)  // temp�� data ���� k�� �ƴϰ� temp ��尡 �������� �ƴ� �� ������ ����
		temp = temp->next;    // temp�� ���� ���� ����, ���� ��忡 ���� ����

	return temp;              // temp�� �����ؼ� ��� ����
}

int delete_node(int k)        // Ư�� data �� k�� �����ϴ� ��带 �����ϴ� ���
{
	node* s, * p;             // ���� ����� �ּ� s�� ���� ����� �ּ� p�� ����
	p = head;                 // ó���� p�� head�� �ּҷ� ����
	s = p->next;              // s�� p�� ���� ����� �ּҷ� ����
	while (s->key != k && s != tail)  // s�� data ���� k�� �ƴϰ�
	{                                 // s�� tail�� �ƴ� �� ������ ����
		p = p->next;          // p�� �� ���� ���� ����
		s = p->next;          // s�� p ���� ���� ����
	}
	if (s != tail) {          // s�� tail��尡 �ƴ� �� ������ ����(Ư�� ���� ��带 ã���� ��)
		p->next = s->next;    // p�� next�� s�� next�� ����
		free(s);              // ��� s�� �޸� ����(����)
		return 1;             // 1�� �����Ͽ� ���� ����
	}
	else return 0;            // data �� k�� ã�� �� ���� ����
}

node* insert_node(int t, int k)  // data �� t�� k �� ����� ���� ����
{
	node* s, * p, * r;  // �� ����� �ּ� �� ����
	p = head;           // p�� �ּҸ� head�� ����
	s = p->next;        // s�� �ּҸ� p�� ���� ���� ����
	while (s->key != k && s != tail) {  // ��� s�� ���� k�� �ƴϰ� s�� tail �ƴ� �� ���� 
		p = p->next;    // p�� �� ���� ���� ����
		s = p->next;    // s�� p ���� ���� ����
	}
	if (s != tail) {    // s�� tail�� �ƴ� �� ����
		r = (node*)calloc(1, sizeof(node)); // ��� r�� �޸� �Ҵ� ����(���� ����)
		r->key = t;     // r�� data ���� t�� ����
		p->next = r;    // p�� ���� ��带 r�� ����
		r->next = s;    // r�� ���� ��带 s�� ����
	}
	return p->next;     // ������ ����� �ּҷ� ����
}

node* ordered_insert(int k)  // k ���� ���� ��带 ã�� �����ϴ� ���
{
	node* s, * p, * r;  // �� ����� �ּ� �� ����
	p = head;           // ��� p�� head�� ����(head�� �ּ� �� = p)
	s = p->next;        // s�� ��� p�� ���� ����� �ּ� ������ ����
	while (s->key <= k && s != tail) { // ��� s�� ���� k ���� �̰�, ��� s�� tail�� �ƴ� �� ������ ����
		p = p->next;    // p�� �� ���� ���� ����
		s = p->next;;   // s�� p ���� ���� ����
	}                   // �� while �ݺ����� ������ ������ ����
	r = (node*)calloc(1, sizeof(node)); // ��� r�� �޸� �Ҵ� ����(���� ����)
	r->key = k;         // ��� r�� data ���� k�� ����
	p->next = r;        // p�� ���� ��带 r�� ����
	r->next = s;        // r�� ���� ��带 s�� ����
	return r;           // ��� r�� ����
}

node* delete_all()      // ��� ��带 ���� �ϴ� ���
{
	node* s;
	node* t;            // �� ����� �ּ� �� ����
	t = head->next;     // ��� t�� head�� ���� ���� ����
	while (t!= tail) {  // ��� t�� tail�� �ƴ� �� ������ �ݺ� ����
		s = t;          // ��� s�� ��� t�� ����
		t = t->next;    // ��� t�� t�� ���� ���� ����
		free(s);        // ��� s�� ����(�޸� ����)
	}                   // ��� s�� tail ��� �϶� ���� ����
	head->next = tail;  // head�� ���� ��带 tail�� ����
	return head;        // head�� ����
}

node* print_node(node* t)    // ���� ����Ʈ(��� ���)�� ����ϴ� ���
{
	t = head->next;
	while (t != tail) {
		if (head == tail) {  // ���� list�� �ƹ� ���� ���� ���
			printf("List�� ���� �����ϴ� \n");
			t = t->next;     // ���� ��忡 ���� ����
			return 0;
		}
		else{
			printf("%d ", (int)t->key); // ���� ������ data ���� ������� ���
			t = t->next;     // ���� ��忡 ���� ����
			
		}
	}
	printf("\n----------------\n");
}

int main() {
	node* t = NULL;      // ��� t�� ����

	init_list();         // ���� ����Ʈ �ʱ�ȭ
	ordered_insert(9);
	ordered_insert(3);
	ordered_insert(5); 
	ordered_insert(1); 
	ordered_insert(7);   // �� ���� ����

	print_node(t);       // ���� ���� ����Ʈ�� ���

	ordered_insert(5);   // ��� 5�� ����
	find_node(5);        // ��� 5�� ã��
	
	insert_node(6, 5);   // ��� 6�� 5 ������ ����

	print_node(t);       // ���� ���� ����Ʈ�� ���

	delete_node(5);      // ��� 5�� ����

	print_node(t);       // ���� ���� ����Ʈ�� ���

	delete_all();        // ��� ��带 ����

	print_node(t);       // ���� ���� ����Ʈ�� ���

	return 0;
}