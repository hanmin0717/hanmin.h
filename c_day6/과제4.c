#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int len(char* s) { //문자열의 길이를 반환하는 함수
	int n = 0;
	while (s[n] != '\0') n++; //널문자가 나올 때까지 n에 1을 더하는 코드
	return n; //반환값 n
}

int main() {
	char str[100]; //입력할 문자열 변수 생성

	char s[100]; //뒤에서 부터 문자열을 꺼내려고 만든 문자열 변수
	int top = 0; //stack을 사용하기 위해 선언한 변수

	char q[100]; //앞에서 부터 문자열을 꺼내려고 만든 문자열 변수
	int front = 0, rear = 0;

	printf("문자열을 입력하세요 : ");
	scanf("%[^\n]", str);

	for (int i = 0; i < len(str); i++) { //띄어쓰기를 제외하고 문자열에 각각 저장하기 위한 코드
		if (str[i] != ' ') {
			s[top++] = str[i];
			q[rear++] = str[i];
		}
	}

	int yueng = 1; //마지막에 회문인지 아닌지 판별을 위해 만들어 놓은 변수

	while (top >= 0) { //뒤에서부터 문자열을 출력하도록 top--를 하고 top이 0보다 작아진다면 s, q모두 문자열의 비교를 끝낸 것이기에 만든 반복문
		char a = s[top--];
		char b = q[front++];

		if (a != b) {//앞에서 꺼낸 것과 뒤에서 꺼낸 것을 비교하며 회문의 특징은 앞에서 꺼낸 것과 뒤에서 꺼낸 것이 같은 것이므로 만약 둘이 다르다면 아까 선언한 변수를 0으로 바꾸고 회문이 아닙니다 를 출력하는 코드
			yueng = 0;
			break;
		}
	}

	if (yueng == 1) { //최종 출력 코드
		printf("회문입니다.");
	}
	else {
		printf("회문이 아닙니다.");
	}

	return 0;
}