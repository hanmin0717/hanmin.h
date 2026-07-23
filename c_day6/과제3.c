#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node { //노드 안에 들어 있어야할 정보, 다음 노드의 주소를 담고 있는 구조체
	int data;
	struct _Node* Next;
} Node;

typedef struct Queue { //노드의 개수와 다음 노드의 연결을 도와주는 구조체
	Node* top[5];
	int size;
} queue;

queue q;

void f_call_f(int menu, int* size);// 함수를 호출하는 함수

void Enqueue(int* size);//매개변수로 사용자가 입력하고자 하는 값을 받아 출력해주는 함수들
void Dequeue(int* size);
void Size(int* size);
void front(int* size);
void rear(int* size);
void isEmpty(int* size);
void printQueue(int* size);

int main() {
	q.size = 0; //queue안에 있는 정보의 개수를 알려주는 변수

	for (int i = 0; i < 5; i++) { //top으로 데이터를 입력받을 준비를 하는 과정으로 아직 아무 데이터도 받은게 없기에 모두 0으로 초기화하고 있다
		q.top[i] = (Node*)malloc(sizeof(Node));
		q.top[i]->data = 0;
		q.top[i]->Next = NULL; 
	}

	while (1) {
		int menu;

		if (q.size > 1) { //stack에서와 마찬가지로 1보다 작다면 다음 노드에 연결할 수 없기에 조건을 걸었다
			for (int i = 0; i < q.size - 1; i++) {
				q.top[i]->Next = q.top[i + 1];
			}
		}
		if (q.size > 0) { //0보다 크다면 가장 큰 인덱스를 가지고 있는 노드의 주소를 NULL로 설정한다
			q.top[q.size - 1]->Next = NULL;
		}
		printf("0. exit\n1. Enqueue\n2. Dequeue\n3. size\n4. front\n5. rear\n6. isEmpty\n7. printQueue\nmenu : ");
		scanf("%d", &menu); //사용자가 입력하고자하는 조작을 보여주는 코드

		if (menu == 0) { //0 입력시 프로그램 종료
			printf("\n프로그램을 종료합니다.\n");
			break;
		}
		else if (menu < 0 || menu > 7) { //위에 나와있는 숫자와 다른 숫자 입력시 반복문으로 돌아가게 하는 코드
			printf("잘못 입력하셨습니다.\n");
			continue;
		}

		f_call_f(menu, &q.size); //메뉴와 사이즈를 매개변수로 함수를 호출하는 과정
	}

	for (int i = 0; i < 5; i++) { //할당한 메모리를 해제하는 코드
		free(q.top[i]);
	}

	return 0;
}

void f_call_f(int menu, int* size) { //함수 포인터와 메뉴의 숫자를 이용해서 다음 함수를 호출하는 코드

	void (*f_call[7])(int*) = { Enqueue, Dequeue, Size, front, rear, isEmpty, printQueue };

	f_call[menu - 1](size);
}

void Enqueue(int* size) { //1 입력시 데이터를 넣고 만약 한계에 도달했다면 가장 나중에 넣은 데이터를 밖으로 빼낸다 
	int num;

	if (*size <= 4 && *size >= 0) {
		printf("데이터를 입력하세요. : ");
		scanf("%d", &num);

		q.top[*size]->data = num;
		(*size)++;
	}
	else if (*size == 5) {
		printf("데이터를 입력하세요. : ");
		scanf("%d", &num);

		for (int i = 0; i < *size - 1; i++) {
			q.top[i]->data = q.top[i + 1]->data;
		}
		q.top[4]->data = num;
	}
	else {
		printf("문제가 발생했습니다.\n");
	}
}

void Dequeue(int* size) { //queue에 데이터를 삭제하는 코드이고 안에 아무 데이터도 없다면 함수를 끝내는 코드
	if (*size <= 0) {
		printf("\nqueue가 비어있습니다.\n");
		return;
	}

	int dequeue = q.top[0]->data;

	for (int i = 0; i < *size - 1; i++) {
		q.top[i]->data = q.top[i + 1]->data;
	}

	(*size)--;
	printf("Dequeue된 값 : %d\n", dequeue);
}

void Size(int* size) { //전체 queue의 크기를 출력하는 함수
	printf("queue의 크기는 %d입니다.\n", *size);
}

void front(int* size) { //queue에 있는 값 중 가장 앞에 있는 값을 출력하게 하는 코드 만약 저장된 값이 없다면 함수를 끝냄
	if (*size <= 0) {
		printf("queue에 저장된 값이 없습니다.\n");
		return;
	}
	printf("맨 앞의 수는 %d입니다.\n", q.top[0]->data);
}

void rear(int* size) {//queue에 있는 값 중 가장 뒤에 있는 값을 출력하게 하는 코드 만약 저장된 값이 없다면 함수를 끝냄
	if (*size <= 0) {
		printf("queue에 저장된 값이 없습니다.\n");
		return;
	}
	printf("맨 뒤의 수는 %d입니다.\n", q.top[*size - 1]->data);
}

void isEmpty(int* size) { //queue안에 아무 정보도 없다면 True를 하나라도 있다면 False를 출력하는 함수
	if (*size == 0) {
		printf("True\n");
	}
	else {
		printf("False\n");
	}
}

void printQueue(int* size) { //queue에 들어있는 전체 데이터를 출력하는 함수이고 만약 아무 데이터도 없다면 함수를 종료하는 코드
	if (*size <= 0) {
		printf("queue가 비어있습니다.\n");
		return;
	}

	printf("queue의 전체 데이터는 ");
	for (int i = 0; i < *size; i++) {
		printf("[%d] ", q.top[i]->data);
	}
	printf("입니다.\n");
}