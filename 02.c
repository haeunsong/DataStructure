#include <stdio.h>
#include <string.h>
#define CAPACITY 100
#define BUFFER_SIZE 20

char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0; // 사람 수

void add() {
	// 정렬 필요
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1); // 이름 저장
	scanf("%s", buf2); // 전번 저장

	int i = n - 1; // 마지막 사람
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
	char buf[BUFFER_SIZE]; // 삭제할 사람 이름
	scanf("%s", buf);
	/*
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
	*/ // 이 방법은 이제 사용 뷸가(정렬했으니까) 

	int index = search(buf); // 사람이름이 존재하지 않으면 return -1
	if (index == -1) {
		printf("No person named '%s' exists.\n",buf);
		return;
	}
	// 존재하면
	int j = index; // 삭제할 사람 인덱스 번호
	// 삭제후 그 빈자리를 채우기 위해서 앞으로 한칸씩 당긴다
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--; // 삭제했으니까 사람 수 줄어들음
	printf("'%s' was deleted successfully.\n",buf);
}

void load() {
	// 파일에 이미 정렬되어 있는 상태
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE]; // 이름 저장
	char buf2[BUFFER_SIZE]; // 전화번호 저장

	// 파일 이름을 입력 받는다.
	scanf("%s", fileName);

	FILE* fp = fopen(fileName, "r"); // 읽기 전용
	// 실패시 
	if (fp == NULL) {
		printf("Opne failed.\n");
		return;
	}
	// 성공시
	// 파일 끝에 도달할 때까지 반복해서 이름과 전화번호를 읽어서 배열에 저장한다
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = _strdup(buf1);
		numbers[n] = _strdup(buf2);
		n++; // 한 사람이 추가되었으므로 
	}

	fclose(fp); // 볼일이 끝난 파일은 반드시 닫아주어야 한다

}

void save() {
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp); // 'as' 문자 받음 
	scanf("%s", fileName);


	FILE* fp = fopen(fileName, "w"); // 원래 기존에 내용이 있으면 덮어씀
	// 실패시 
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
		else if (strcmp(command, "read") == 0)
			load();
		else if (strcmp(command, "save") == 0)
			save();
	}

}