#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 30 
#define BUFFER_SIZE 50

// void remove(char* name);
// ���� �޸� �Ҵ��� ���� ������ ������ ���
char** names;
char** numbers;

int n = 0; // ��� ��
int capacity = CAPACITY; // ���� �迭�� ������ 
char delim[] = " "; // strtok ���й���

void delete_info(char* name) {
	int index = search(name); // ����̸��� �������� ������ return -1
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
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
	printf("'%s' was deleted successfully.\n", name);
}

int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void reallocate() {
	capacity *= 2;
	// ũ�Ⱑ 2���� �迭 �Ҵ�
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	// ���� �迭 names�� numbers�� ���� ���ο� �迭�� ��� ����
	for (int i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}
	//strcpy(tmp1, names);
	//strcpy(tmp2, names);

	free(names);
	free(numbers);

	// names�� numbers�� ���ο� �迭�� ����Ű����
	// (�迭�� �̸��� ������ �����̴�)

	names = tmp1;
    numbers = tmp2;


}

void add(char *name,char *number) {
	// �迭�� ���� ��� ���Ҵ��Ѵ�.
	if (n >= capacity)
		reallocate();

	// ���� �ʿ�
	int i = n - 1; // ������ ���
	while (i >= 0 && strcmp(names[i], name) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}

	names[i + 1] = _strdup(name);
	numbers[i + 1] = _strdup(number);
	n++;

	printf("%s was added successfully.\n", name);

}
void find(char *name) {

	int index = search(name);
	if (index == -1)
		printf("No person named '%s' exists.\n", name);
	else
		printf("%s\n", numbers[index]);
}
void status() {

	for (int i = 0; i < n; i++) {
		printf("%s  %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);

}

void load(char *fileName) {
	// ���Ͽ� �̹� ���ĵǾ� �ִ� ����
	char buf1[BUFFER_SIZE]; // �̸� ����
	char buf2[BUFFER_SIZE]; // ��ȭ��ȣ ����

	FILE* fp = fopen(fileName, "r"); // �б� ����
	// ���н� 
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	// ������
	// ���� ���� ������ ������ �ݺ��ؼ� �̸��� ��ȭ��ȣ�� �о �迭�� �����Ѵ�
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}

	fclose(fp); // ������ ���� ������ �ݵ�� �ݾ��־�� �Ѵ�

}
void save (char *fileName) {

	FILE* fp = fopen(fileName, "w"); // ���� ������ ������ ������ ���
	// ���н� 
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

void init_directory() {
	names = (char**)malloc(CAPACITY * sizeof(char*));
	numbers = (char**)malloc(CAPACITY * sizeof(char*));
}

// line ������ �Է��� fgets,getline���� �Լ��� ������ ���� ���� ���� ��� ����.
// limit���� �� �� line�� ��쿡�� �޺κ��� ©����.
int read_line(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n') // �ٹٲ� ���ڰ� ���ö����� �д´�.
		if (i < limit - 1) // �ι��ڶ����� -1���� // �迭�� �ʰ����� ���� �������� ����.
			str[i++] = ch;
	str[i] = '\0'; // �������� �ι��� �߰�
	return  i; // ������ ���� ���ڼ� ��ȯ
}
void process_command() {
	// ��� ���� : add jamy 1234
	char command_line[BUFFER_SIZE]; // ���� ������ �о��.
	char* command, * argument1, * argument2;

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0)
			continue; // �ٽ� �������� ���ư��� $ �����
		// �׷��� ������(������ �Է��ϸ�)
		command = strtok(command_line, delim);
		if (command == NULL)continue;  // ù��° ��ū�� ��ɾ��̴�.
		
		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim); // read��ɿ��� �ι�° ��ū�� ���ϸ��̴�.
			if (argument1 == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argument1); // ���ϸ��� ���ڷ� �ָ鼭 load ȣ��
		}
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);  // �̸�
			argument2 = strtok(NULL, delim);  // ����

			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			add(argument1, argument2); // �������̸� �̸��� ������ ���ڷ� �ָ鼭 addȣ��
			printf("%s was added successfully.\n", argument1);
		}
		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			find(argument1);
		}
		else if (strcmp(command, "delete") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			delete_info(argument1);
		}
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);  // as
			argument2 = strtok(NULL, delim);  // ���ϸ�

			if (argument1 == NULL || strcmp("as", argument1) != 0 || argument2 == NULL) {
				printf("Invalid command format.\n");
				continue;
			}
			save(argument2);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

int main() {

	char command[BUFFER_SIZE];

	init_directory();  // �� �Լ����� �迭 names�� numbers�� �����Ѵ�
	process_command();  // ������� ����� �޾� ó���ϴ� �κ��� ������ �Լ��� �������

	return 0;
}
