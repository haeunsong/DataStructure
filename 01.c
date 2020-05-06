#include <stdio.h>
#include <string.h>
#define CAPACITY 100
#define BUFFER_SIZE 20

char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0; // 사람 수

void add() {
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	names[n] = _strdup(buf1);
	numbers[n] = _strdup(buf2);


	printf("%s was added successfully.\n", buf1);
	printf("%p was added successfully.\n", names[n]);
	n++;
}

void find() {

	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	for (int i = 0; i < n; i++) {
		if (strcmp(buf, names[i]) == 0) {
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("No person named '%s' exists.\n", buf);
}


void status() {

	for (int i = 0; i < n; i++) {
		printf("%s  %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);

}

void remove() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	for (int i = 0; i < n; i++) {
		if (strcmp(buf, names[i]) == 0) {  // 문자열을 비교하여 일치하면(삭제할 사람을 찾음) 0을 반환한다.
			// 맨 마지막 사람을 삭제된 자리로 옮긴다.
			names[i] = names[n - 1];
			numbers[i] = numbers[n - 1];
			n--;
			printf("'%s' was deleted successfully.\n", buf);
			return;
		}
	}
	printf("No person named '%s' exists.\n", buf);

}


void main() {

	char command[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0) // 일치하면 0반환
			add();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0)
			remove();
		else if (strcmp(command, "exit") == 0)
			break;
	}

}