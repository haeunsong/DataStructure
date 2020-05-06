#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 30 
#define BUFFER_SIZE 50

// void remove(char* name);
// 동적 메모리 할당을 위해 이차원 포인터 사용
char** names;
char** numbers;

int n = 0; // 사람 수
int capacity = CAPACITY; // 현재 배열의 사이즈 
char delim[] = " "; // strtok 구분문자

void delete_info(char* name) {
	int index = search(name); // 사람이름이 존재하지 않으면 return -1
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
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
	// 크기가 2배인 배열 할당
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	// 원본 배열 names와 numbers의 값을 새로운 배열에 모두 복사
	for (int i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}
	//strcpy(tmp1, names);
	//strcpy(tmp2, names);

	free(names);
	free(numbers);

	// names와 numbers가 새로운 배열을 가리키도록
	// (배열의 이름은 포인터 변수이다)

	names = tmp1;
    numbers = tmp2;


}

void add(char *name,char *number) {
	// 배열이 꽉찬 경우 재할당한다.
	if (n >= capacity)
		reallocate();

	// 정렬 필요
	int i = n - 1; // 마지막 사람
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
	// 파일에 이미 정렬되어 있는 상태
	char buf1[BUFFER_SIZE]; // 이름 저장
	char buf2[BUFFER_SIZE]; // 전화번호 저장

	FILE* fp = fopen(fileName, "r"); // 읽기 전용
	// 실패시 
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	// 성공시
	// 파일 끝에 도달할 때까지 반복해서 이름과 전화번호를 읽어서 배열에 저장한다
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}

	fclose(fp); // 볼일이 끝난 파일은 반드시 닫아주어야 한다

}
void save (char *fileName) {

	FILE* fp = fopen(fileName, "w"); // 원래 기존에 내용이 있으면 덮어씀
	// 실패시 
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

// line 단위의 입력은 fgets,getline등의 함수도 있지만 직접 만들어서 쓰는 경우 많음.
// limit보다 더 긴 line의 경우에는 뒷부분이 짤린다.
int read_line(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n') // 줄바꿈 문자가 나올때까지 읽는다.
		if (i < limit - 1) // 널문자때문에 -1해줌 // 배열을 초과하지 않을 때까지만 읽음.
			str[i++] = ch;
	str[i] = '\0'; // 마지막에 널문자 추가
	return  i; // 실제로 읽은 문자수 반환
}
void process_command() {
	// 명령 예시 : add jamy 1234
	char command_line[BUFFER_SIZE]; // 라인 단위로 읽어옴.
	char* command, * argument1, * argument2;

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0)
			continue; // 다시 조건으로 돌아가서 $ 출력함
		// 그렇지 않으면(뭔가를 입력하면)
		command = strtok(command_line, delim);
		if (command == NULL)continue;  // 첫번째 토큰은 명령어이다.
		
		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim); // read명령에서 두번째 토큰은 파일명이다.
			if (argument1 == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argument1); // 파일명을 인자로 주면서 load 호출
		}
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);  // 이름
			argument2 = strtok(NULL, delim);  // 전번

			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			add(argument1, argument2); // 정상적이면 이름과 전번을 인자로 주면서 add호출
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
			argument2 = strtok(NULL, delim);  // 파일명

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

	init_directory();  // 이 함수에서 배열 names와 numbers를 생성한다
	process_command();  // 사용자의 명령을 받아 처리하는 부분을 별개의 함수로 만들었다

	return 0;
}
