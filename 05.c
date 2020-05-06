#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_LENGTH 100
#define INIT_CAPACITY 100

typedef struct {
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

Person** directory;
int capacity;
int n;

void init() {
	directory = (Person**)malloc(INIT_CAPACITY * sizeof(Person*));
	capacity = INIT_CAPACITY;
	n = 0;
}
void reallocate() {
	capacity *= 2;
	Person** tmp = (Person**)malloc(capacity * sizeof(Person*));
	for (int i = 0; i < n; i++)
		tmp[i] = directory[i]; 
	free(directory);  // free �ʼ�!!
	directory = tmp;  // ��ü�� '�ּ�'�� ����Ǵ°���!!
}
void add_info(char* name, char* number, char* email, char* group) { 
	// �Ѿ�� ���Ҵ�
	if (n >= capacity)
		reallocate();	
	// ����
	int i = n - 1;

	while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
		directory[i + 1] = directory[i]; 
		i--;
	}
	directory[i + 1] = (Person*)malloc(sizeof(Person)); // �߿�!!!

	directory[i + 1]->name = _strdup(name);      // strdup �ʼ�!!!��!!
	directory[i + 1]->number = _strdup(number);
	directory[i + 1]->email = _strdup(email);
	directory[i + 1]->group = _strdup(group);
	n++;
}

// Ű����Ӹ��ƴ϶� ���Ϸκ��͵� ���� �� �ֵ��� ��
int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
	return i; // �̸� ö�� ���� ����
}
void load(char* fileName) {
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;
	char* token;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;
		name = strtok(buffer, "#"); 
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			number = NULL;
		else number = _strdup(token);
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			email = NULL;
		else email = _strdup(token);
		if (strcmp(token, " ") == 0)
			group = NULL;
		else group = _strdup(token);
		add_info(_strdup(name), number, email, group); // ���� add_info�Լ����� dup�޴µ� �׳� ���⼭ �ع���. �̹� ������ �� �ѱ�.
	}
	fclose(fp);
}
// command_line�� �����ִ� ��ū���� ��� ���� �̸��� ��Ÿ���� ���ڿ��� �����Ѵ�.
// ��ū�� ��ū ���̿� �ϳ��� ���鹮�ڸ� �����Ѵ�.

int compose_name(char str[], int limit) {
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " ");  // �ι�° ��ū(ù��° ��ū�� ��ɾ�command)
	if (ptr == NULL)  // ����̸��� ���ٴ� ��
		return 0;
	strcpy(str, ptr);
	length += strlen(ptr);

	while ((ptr == strtok(NULL, " ")) != NULL) {  // �����÷ο� ������
		if (length + strlen(ptr) + 1 < limit) { // �ι��ڶ����� +1
			str[length++] = ' ';
			str[length] = '\0';
			strcat(str, ptr);
			length += strlen(ptr);
		}
	}
	return length;
}
void handle_add(char* name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " ";

	printf("  Phone: ");
	read_line(stdin, number, BUFFER_LENGTH); // number ö�� ���� ����

	printf("  Email: ");
	read_line(stdin, email, BUFFER_LENGTH);  // email ö�� ���� ����

	printf("  Group: ");
	read_line(stdin, group, BUFFER_LENGTH);
	     
	add_info(name, (strlen(number) > 0 ? number : empty),
		(strlen(email) > 0 ? email : empty),
		(strlen(group) > 0 ? group : empty));

}
void release_person(Person* p) {

	free(p->name);
	if (p->number != NULL) free(p->number); // �ΰ��ε� ���� ������ų �ʿ�����ϱ� if�� ���
	if (p->email != NULL) free(p->email);
	if (p->group != NULL) free(p->group);
	free(p);
}
void remove_info(char* name) {
	int i = search(name);
	if (i == -1) {
		printf("No person name '%s' exists.\n", name);
		return;
	}
	Person* p = directory[i];
	for (int j = i; j < n - 1; j++)
		directory[j] = directory[j + 1];
	n--;
	release_person(p);  // �Ϻη� �Լ��� ����. free(p)�� �ȵǴ°� �ȿ� �ִ� �͵��� ��� �������� �Ҵ�Ǿ��־ ���� �����������.
	printf("'%s' was deleted successfully.\n",name);

}
void save(char* fileName) {
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[i]->name);
		fprintf(fp, "%s#", directory[i]->number);
		fprintf(fp, "%s#", directory[i]->email);
		fprintf(fp, "%s#\n", directory[i]->group);
	}
	fclose(fp);
}
int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, directory[i]->name) == 0) {
			return i;
		}
	}
	return -1;
}
void print_person(Person *p) {
	printf("%s:\n", p->name);
	printf("  Phone: %s\n", p->number);
	printf("  Email: %s\n", p->email);
	printf("  Group: %s\n", p->group);
}
void status() {
	for (int i = 0; i < n; i++) {
		print_person(directory[i]);
	}
	printf("Total %d persons.\n", n);
}
void find(char* name) {
	int index = search(name);
	if (index == -1)
		printf("No person named '%s' exists.\n", name);
	else
		print_person(directory[index]);
}
int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument;
	char name_str[BUFFER_LENGTH];
	
	init();

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) // �ƹ��Է��� ������ 0
			continue;
		command = strtok(command_line, " ");

		if (strcmp(command, "add") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) { // �̸��� �־����� ������
				printf("Name required.\n");
				continue;
			}
			handle_add(name_str);
		}
		else if (strcmp(command, "read") == 0) {
			argument = strtok(NULL, " ");  // �ι�° ���� ���ϸ�
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument);
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			remove_info(name_str);
		}
		else if (strcmp(command, "save") == 0) {
			argument = strtok(NULL, " ");   // ù��° ���� 'as'
			if (strcmp(argument, "as") != 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			argument = strtok(NULL, " ");   // �ι�° ���� ���ϸ�
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}







