#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define NAME_SIZE 21
#define CORP_SIZE 31
#define TEL_SIZE 16
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE) // 이름, 소속, 번호의 크기를 정의

typedef struct _card {       // Card의 구조체를 정의
	char name[NAME_SIZE];
	char corp[CORP_SIZE];
	char tel[TEL_SIZE];
	struct _card* next;
}card;

card* head, * tail;  // Linked List에 쓰일 두 전역변수 정의

void init_card()     // Linked List를 위한 Initialization
{
	head = (card*)calloc(1, sizeof(card));
	tail = (card*)calloc(1, sizeof(card));
	head->next = tail;
	tail->next = tail;
}

void input_card()  // Insertion 기능을 정의
{
	card* t;
	t = (card*)calloc(1, sizeof(card));

	printf("\nInput namecard menu : ");
	printf("\nInput name : ");
	gets_s(t->name);
	printf("\nInput corporation : ");
	gets_s(t->corp);
	printf("\nInput telephone number : ");
	gets_s(t->tel);      // 이름, 소속, 번호를 string 입력 받음

	t->next = head->next;
	head->next = t;      // 연결리스트 중 삽입 기능
}

int delete_card(char* s) // deletion 기능을 정의
{
	card* t, * p;
	p = head;
	t = p->next;
	while (strcmp(s, t->name) != 0 && t != tail) {
		p = p->next;
		t = p->next;
	}                        // delete 할 데이터를 search
	if (t == tail) return 0; // 찾는 key가 없을 때
	p->next = t->next;
	free(t);                 // delete
	return 1;
}

card* search_card(char* s) { // search 기능을 정의
	card* t;
	t = head->next;
	while (strcmp(s, t->name) != 0 && t != tail) {
		t = t->next;
	}
	if (t == tail) return NULL;
	else return t;
}

void save_card(char* s) // save 기능을 정의
{
	FILE* fp; // 파일 입출력
	card* t;
	fopen_s(&fp, s, "wb"); // wb 모드로 파일을 오픈

	t = head->next;
	while (t != tail) {
		fwrite(t, REC_SIZE, 1, fp); // 1개씩 저장함
		t = t->next;
	}
	fclose(fp);
}
void load_card(char* s) { // load 기능을 정의
	FILE* fp;
	card* t, * u;
	fopen_s(&fp, s, "rb"); // rb 모드로 파일을 오픈

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
		head->next = t;      // Input 기능
	}
	fclose(fp); // 마지막에 파일을 닫아줘야 함
}

void print_header(FILE* f) { // 단지 출력 화면에서 보이기 위한 기능
	fprintf(f, "\nName       "
		"Corportation        "
		"Telephone number");
	fprintf(f, "\n----------------   "
		"----------------------   "
		"-----------------");
}

void print_card(card* t, FILE* f) { // NameCard를 출력 하는 기능 정의
	fprintf(f, "\n%-20s    %-30s    %-15s\n", t->name, t->corp, t->tel);
}

int select_menu() { // 1~7 까지의 menu 기능들 출력 및 입력 받는 기능 정의
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
		j = atoi(gets_s(s)); // 메뉴 번호를 string로 입력 받고 Integer 타입으로 변환 
	} while (j < 0 || j > 7);

	return j;
}

int main(void) { // 드디어 메인 함수!
	char* fname = (char*)"Pro5"; // 처음에 계속 이 부분이 잘 안 됐었다
	char name[NAME_SIZE];        // 나중에 뒷부분에 (char*)을 붙여서 강제로 타입을 변환했는데
	int i;                       // 4, 5번 기능이 아직 잘 안 되는 것 같다
	card* t;                     // Linked List를 위한 포인터 변수 t 정의

	init_card();                 // 위에서 정의한 Linked List를 메인 함수에 불러옴

	while ((i = select_menu()) != 7) { // 1~7 까지의 메뉴들의 정의를 각 경우별로 메인 함수로 불러옴
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