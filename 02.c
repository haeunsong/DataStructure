#include <stdio.h>
#include <string.h>
#define CAPACITY 100
#define BUFFER_SIZE 20

char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0; // ��� ��

void add() {
	// ���� �ʿ�
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1); // �̸� ����
	scanf("%s", buf2); // ���� ����

	int i = n - 1; // ������ ���
	while (i >= 0 && strcmp(names[i], buf1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = _strdup(buf1);
	numbers[i + 1] = _strdup(buf2);

	n++;

	printf("%s was added successfully.\n", buf1);

}

void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
		printf("No person named '%s' exists.\n", buf);
	else
		printf("%s\n", numbers[index]);
}


void status() {

	for (int i = 0; i < n; i++) {
		printf("%s  %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);

}

void remove() {
	char buf[BUFFER_SIZE]; // ������ ��� �̸�
	scanf("%s", buf);
	/*
	for (int i = 0; i < n; i++) {
		if (strcmp(buf, names[i]) == 0) {  // ���ڿ��� ���Ͽ� ��ġ�ϸ�(������ ����� ã��) 0�� ��ȯ�Ѵ�.
			// �� ������ ����� ������ �ڸ��� �ű��.
			names[i] = names[n - 1];
			numbers[i] = numbers[n - 1];
			n--;
			printf("'%s' was deleted successfully.\n", buf);
			return;
		}
	}
	*/ // �� ����� ���� ��� �氡(���������ϱ�) 

	int index = search(buf); // ����̸��� �������� ������ return -1
	if (index == -1) {
		printf("No person named '%s' exists.\n",buf);
		return;
	}
	// �����ϸ�
	int j = index; // ������ ��� �ε��� ��ȣ
	// ������ �� ���ڸ��� ä��� ���ؼ� ������ ��ĭ�� ����
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--; // ���������ϱ� ��� �� �پ����
	printf("'%s' was deleted successfully.\n",buf);
}

void load() {
	// ���Ͽ� �̹� ���ĵǾ� �ִ� ����
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE]; // �̸� ����
	char buf2[BUFFER_SIZE]; // ��ȭ��ȣ ����

	// ���� �̸��� �Է� �޴´�.
	scanf("%s", fileName);

	FILE* fp = fopen(fileName, "r"); // �б� ����
	// ���н� 
	if (fp == NULL) {
		printf("Opne failed.\n");
		return;
	}
	// ������
	// ���� ���� ������ ������ �ݺ��ؼ� �̸��� ��ȭ��ȣ�� �о �迭�� �����Ѵ�
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = _strdup(buf1);
		numbers[n] = _strdup(buf2);
		n++; // �� ����� �߰��Ǿ����Ƿ� 
	}

	fclose(fp); // ������ ���� ������ �ݵ�� �ݾ��־�� �Ѵ�

}

void save() {
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp); // 'as' ���� ���� 
	scanf("%s", fileName);


	FILE* fp = fopen(fileName, "w"); // ���� ������ ������ ������ ���
	// ���н� 
	if (fp == NULL) {
		printf("Opne failed.\n");
		return;
	}

	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}

int main() {

	char command[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0) // ��ġ�ϸ� 0��ȯ
			add();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0)
			remove();
		else if (strcmp(command, "exit") == 0)
			break;
		else if (strcmp(command, "read") == 0)
			load();
		else if (strcmp(command, "save") == 0)
			save();
	}

}