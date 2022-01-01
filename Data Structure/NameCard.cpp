#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define NAME_SIZE 21
#define CORP_SIZE 31
#define TEL_SIZE 16
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE)

typedef struct _card{
	char name[NAME_SIZE];
	char corp[CORP_SIZE];
	char tel[TEL_SIZE];
	struct _card* next;
}card;

card* head, * tail;

void init_card()
{
	head = (card*)calloc(1, sizeof(card));
	tail = (card*)calloc(1, sizeof(card));
	head->next = tail;
	tail->next = tail;
}

void input_card()
{
	card* t;
	t = (card*)calloc(1, sizeof(card));

	printf("\nInput namecard menu : ");
	printf("\nInput name : ");
	gets_s(t->name);
	printf("\nInput corporation : ");
	gets_s(t->corp);
	printf("\nInput telephone number : ");
	gets_s(t->tel);

	t->next = head->next;
	head->next = t;
}

int delete_card(char* s)
{
	card* t, * p;
	p = head;
	t = p->next;
	while (strcmp(s, t->name) != 0 && t != tail) {
		p = p->next;
		t = p->next;
	}
	if (t == tail) return 0;
	p->next = t->next;
	free(t);
	return 1;
}

card* search_card(char* s) {
	card* t;
	t = head->next;
	while (strcmp(s, t->name) != 0 && t != tail) {
		t = t->next;
	}
	if (t == tail) return NULL;
	else return t;
}

void save_card(char* s)
{
	FILE* fp;
	card* t;
	fopen_s(&fp, s, "wb");

	t = head->next;
	while (t != tail) {
		fwrite(t, REC_SIZE, 1, fp);
		t = t->next;
	}
	fclose(fp);
}
void load_card(char* s) {
	FILE* fp;
	card* t, * u;
	fopen_s(&fp, s, "rb");

	t = head->next;
	while (t != tail) {
		u = t;
		t = t->next;
		free(u);
	}
	head->next = tail;

	while (1) {
		t = (card*)calloc(1, sizeof(card));
		if (!fread(t, REC_SIZE, 1, fp)) {
			free(t);
			break;
		}
		t->next = head->next;
		head->next = t;
	}
	fclose(fp);
}

void print_header(FILE* f) {
	fprintf(f, "\nName       "
		       "Corportation        "
		       "Telephone number");
	fprintf(f, "\n----------------   "
		       "----------------------   "
		       "-----------------");
}

void print_card(card* t, FILE* f) {
	fprintf(f, "\n%-20s    %-30s    #-15s\n", t->name, t->corp, t->tel);
}

int select_menu() {
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
		j = atoi(gets_s(s));
	}while (j < 0 || j > 7);
	
	return j;
}

int main(void) {
	char fname[] = "임베디드자료구조_과제5";
	char name[NAME_SIZE];
	int i;
	card* t;

	init_card();

	while ((i = select_menu()) != 7) {
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