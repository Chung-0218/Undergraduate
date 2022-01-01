#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define NAME_SIZE 21
#define CORP_SIZE 31
#define TEL_SIZE 16
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE) // �̸�, �Ҽ�, ��ȣ�� ũ�⸦ ����

typedef struct _card {       // Card�� ����ü�� ����
	char name[NAME_SIZE];
	char corp[CORP_SIZE];
	char tel[TEL_SIZE];
	struct _card* next;
}card;

card* head, * tail;  // Linked List�� ���� �� �������� ����

void init_card()     // Linked List�� ���� Initialization
{
	head = (card*)calloc(1, sizeof(card));
	tail = (card*)calloc(1, sizeof(card));
	head->next = tail;
	tail->next = tail;
}

void input_card()  // Insertion ����� ����
{
	card* t;
	t = (card*)calloc(1, sizeof(card));

	printf("\nInput namecard menu : ");
	printf("\nInput name : ");
	gets_s(t->name);
	printf("\nInput corporation : ");
	gets_s(t->corp);
	printf("\nInput telephone number : ");
	gets_s(t->tel);      // �̸�, �Ҽ�, ��ȣ�� string �Է� ����

	t->next = head->next;
	head->next = t;      // ���Ḯ��Ʈ �� ���� ���
}

int delete_card(char* s) // deletion ����� ����
{
	card* t, * p;
	p = head;
	t = p->next;
	while (strcmp(s, t->name) != 0 && t != tail) {
		p = p->next;
		t = p->next;
	}                        // delete �� �����͸� search
	if (t == tail) return 0; // ã�� key�� ���� ��
	p->next = t->next;
	free(t);                 // delete
	return 1;
}

card* search_card(char* s) { // search ����� ����
	card* t;
	t = head->next;
	while (strcmp(s, t->name) != 0 && t != tail) {
		t = t->next;
	}
	if (t == tail) return NULL;
	else return t;
}

void save_card(char* s) // save ����� ����
{
	FILE* fp; // ���� �����
	card* t;
	fopen_s(&fp, s, "wb"); // wb ���� ������ ����

	t = head->next;
	while (t != tail) {
		fwrite(t, REC_SIZE, 1, fp); // 1���� ������
		t = t->next;
	}
	fclose(fp);
}
void load_card(char* s) { // load ����� ����
	FILE* fp;
	card* t, * u;
	fopen_s(&fp, s, "rb"); // rb ���� ������ ����

	t = head->next;
	while (t != tail) {
		u = t;
		t = t->next;
		free(u);
	}                    // delete all
	head->next = tail;

	while (1) {
		t = (card*)calloc(1, sizeof(card));
		if (!fread(t, REC_SIZE, 1, fp)) {
			free(t);
			break;
		}
		t->next = head->next;
		head->next = t;      // Input ���
	}
	fclose(fp); // �������� ������ �ݾ���� ��
}

void print_header(FILE* f) { // ���� ��� ȭ�鿡�� ���̱� ���� ���
	fprintf(f, "\nName       "
		"Corportation        "
		"Telephone number");
	fprintf(f, "\n----------------   "
		"----------------------   "
		"-----------------");
}

void print_card(card* t, FILE* f) { // NameCard�� ��� �ϴ� ��� ����
	fprintf(f, "\n%-20s    %-30s    %-15s\n", t->name, t->corp, t->tel);
}

int select_menu() { // 1~7 ������ menu ��ɵ� ��� �� �Է� �޴� ��� ����
	int j;
	char s[10];
	printf("Name card Manager\n");
	printf("------------------\n");
	printf("1. Input name card\n");
	printf("2. Delete name card\n");
	printf("3. Search name card\n");
	printf("4. Load name card\n");
	printf("5. Save name card\n");
	printf("6. Show list\n");
	printf("7. Program end...\n");

	do {
		printf(": selection operation -> \n");
		j = atoi(gets_s(s)); // �޴� ��ȣ�� string�� �Է� �ް� Integer Ÿ������ ��ȯ 
	} while (j < 0 || j > 7);

	return j;
}

int main(void) { // ���� ���� �Լ�!
	char* fname = (char*)"Pro5"; // ó���� ��� �� �κ��� �� �� �ƾ���
	char name[NAME_SIZE];        // ���߿� �޺κп� (char*)�� �ٿ��� ������ Ÿ���� ��ȯ�ߴµ�
	int i;                       // 4, 5�� ����� ���� �� �� �Ǵ� �� ����
	card* t;                     // Linked List�� ���� ������ ���� t ����

	init_card();                 // ������ ������ Linked List�� ���� �Լ��� �ҷ���

	while ((i = select_menu()) != 7) { // 1~7 ������ �޴����� ���Ǹ� �� ��캰�� ���� �Լ��� �ҷ���
		switch (i) {                  
		case 1:
			input_card();
			break;
		case 2:
			printf("Input name to delete -> \n");
			gets_s(name);
			if (!delete_card(name)) printf("Can't find the name...\n");
			break;
		case 3:
			printf("Input name to search -> \n");
			gets_s(name);
			t = search_card(name);
			if (t == NULL) break;
			print_header(stdout);
			print_card(t, stdout);
			break;
		case 4:
			load_card(fname);
			break;
		case 5:
			save_card(fname);
			break;
		case 6:
			t = head->next;
			print_header(stdout);
			while (t != tail) { print_card(t, stdout); t = t->next; }
			break;
		}
	}
	return 0;
}