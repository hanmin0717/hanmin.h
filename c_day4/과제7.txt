#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node { //노드들이 가지고 있는 데이터와 다음 노드를 연결하는 주소를 저장하는 변수를 담고 있는 구조체
    int data; // 노드의 데이터 자료형은 정수형
    struct _node* next; // 노드의 다음 연결 노드의 주소
} node;

typedef struct { //노드들로 묶인 리스트의 구조를 head, cur, tail로 나눈 구조체이고 cur은 head와 tail을 포함하는 밑에 코드로 쓰인다
    node* head; //리스트의 처음부분
    node* cur[10]; //리스트의 전체부분
    node* tail; //리스트의 마지막 부분
    int size; // 현재 노드들의 개수를 나타내는 변수
} linked_list;

int main() {
    linked_list list;
    list.size = 3; //초기 설정은 head, tail, 중간에 하나로 설정하려는 코드

    node* num = (node*)malloc(list.size * sizeof(node)); //동적할당으로 일단은 3을 받아놓는다

    for (int i = 0; i < list.size; i++) { //3개의 노드의 데이터를 입력하는 코드
        printf("%d번째 노드의 데이터를 입력하세요 : ", i + 1);
        scanf("%d", &num[i].data);
    }

    while (1) { //리스트에 노드를 조작할 수 있도록 만들어놓은 무한 루프 만약 메뉴에서 0을 입력한다면 빠져나올 수 있다
        for (int i = 0; i < list.size - 1; i++) { //반복문 시작할 때마다 노드들의 다음 연결을 해놓은 코드
            num[i].next = &num[i + 1];
        }
        num[list.size - 1].next = NULL; //마지막 노트, 즉 head는 다음을 연결할 수 있는 노드가 없기 떄문에 NULL로 저장한다

        list.head = &num[0]; //head는 항상 처음의 노드이기에 num[0]을 저장한다
        list.tail = &num[list.size - 1]; //tail은 항상 리스트에서 마지막에 있기에 전체 노드의 숫자에서 1을 뺀 값의 인덱스와 같다

        for (int i = 0; i < list.size; i++) { //cur은 모든 입력한 숫자들의 주소를 담게하는 코드, 나중에 전체 노드 출력에 도움이 되는 코드
            list.cur[i] = &num[i];
        }

        int menu;
        printf("\n0. exit\n1. insert\n2. delete\n3. get_entry\n4. get_length\n5. print_list\n6. reverse\n메뉴를 선택하세요 : "); //작업하려는 것을 입력할 수 있게 도움을 주는 코드
        scanf("%d", &menu);

        if (menu == 0) { //0을 입력하면 프로그램이 종료되게 하는 코드
            printf("\n프로그램을 종료합니다.\n");
            break;
        }
        else if (menu == 1) { //노드를 추가할 수 있는 코드
            if (list.size >= 10) { //노드의 제한이 10이기에 10보다 크거나 같으면 추가할 수 없다고 띄우는 메세지
                printf("추가할 수 없습니다!\n");
                continue;
            }

            int n, id; //n은 인덱스 id는 노드에 저장할 데이터이다
            printf("인덱스 입력 : ");
            scanf("%d", &n);

            if (n < 0 || n > list.size) { //인덱스가 정해진 값의 범위에 벗어난다면 즉시 추가 작업을 중단하는 코드
                printf("잘못 입력했습니다.\n");
                continue;
            }

            printf("데이터 입력 : ");
            scanf("%d", &id);

            list.size++;
            num = (node*)realloc(num, list.size * sizeof(node)); //노드를 추가해야하기에 realloc으로 다시 할당해준다

            for (int i = list.size - 1; i > n; i--) { //넣으려는 인덱스보다 크다면 뒤로 한 칸씩 후퇴하게 만든 코드이고 이미 동적할당으로 입력할 수 있는 공간을 한 개 더 늘렸기 때문에 인덱스의 값을 벗어나지 않는다
                num[i].data = num[i - 1].data;
            }
            num[n].data = id; //아까 입력한 인덱스에 데이터를 저장한다
        }
        else if (menu == 2) { //노드를 제거하는 코드
            if (list.size <= 1) { // 노드가 1보다 작거나 같다면 노드를 제거할 수 없음으로 메세지를 띄우고 삭제하는 작업을 중단한다
                printf("삭제할 노드가 없습니다!\n");
                continue;
            }

            int n; //인덱스 변수
            printf("인덱스 입력 : ");
            scanf("%d", &n);

            if (n < 0 || n >= list.size) { // 인덱스가 값을 벗어나면 프로그램이 종료되게하는 코드
                printf("잘못 입력했습니다.\n");
                continue;
            }

            for (int i = n; i < list.size - 1; i++) { //insert와는 반대로 지우려는 인덱스보다 큰 값은 앞으로 한칸씩 당겨온다
                num[i].data = num[i + 1].data;
            }

            list.size--; // 아까 insert는 추가하고 앞으로 한 칸 당겨야했지만 삭제는 한칸 앞으로 당기고 realloc으로 노드의 수를 줄였다. 이유는 insert는 크기를 키워야 반복문에서 제대로 작동할 수 있지만 delete같은 경우에는 이미 삭제한 곳이 비어있으니 그곳을 빨리 채우는 것이 중요하지 한 칸을 줄이는 것은 맨 마지막 정보가 한 칸 당겨지지도 못한채 삭제되고 말기 때문이다
            num = (node*)realloc(num, list.size * sizeof(node));
        }
        else if (menu == 3) {//데이터로 인덱스를 찾거나 인덱스로 데이터를 찾게 해주는 코드
            int cho, fi,fd, a = 0; // 각각 인덱스, 데이터를 찾을 것인지, 전자라면 데이터를 입력하고, 후자라면 인덱스를 입력하게 하는 변수, a는 찾는 숫자가 있는지 없지는 알게 해주는 변수
            printf("데이터로 인덱스를 찾는다면 0, 인덱스로 데이터를 찾는다면 1을 입력해주세요. :");
            scanf("%d", &cho); //인덱스를 찾을 것인지 데이터를 찾을 것인지 묻는 코드
            if (cho == 0) { //인덱스를 찾는 코드
                printf("데이터를 입력해주세요. : ");
                scanf("%d", &fi);
                printf("인덱스는 ");
                for (int i = 0; i < list.size; i++) { //입력한 데이터와 같은 값이 있다면 a는 0에서 탈출한다
                    if (num[i].data == fi) {
                        printf("(%d) ", i);
                        a++;
                    }
                }
                if (a == 0) printf("없습니다. "); //a에 따라 달라지는 출력값
                else printf("입니다. ");
            }

            else if (cho == 1) {//데이터를 찾는 코드
                printf("인덱스를 입력해주세요. : ");
                scanf("%d", &fd);
                if (fd <= 0 && fd >= list.size) {//범위에 벗어나는 인덱스 예외 처리
                    printf("잘못 입력하셨습니다. ");
                    continue;
                }
                printf("데이터 : %d", num[fd].data); //인덱스를 가지고 데이터를 출력하는 코드
            }
            else {//예외 처리
                printf("잘못 입력하셨습니다. ");
                continue;
            }
        }
        else if (menu == 4) { //노드의 전체 개수를 출력하는 코드
            printf("\n노드 개수 : %d\n", list.size); //list.size가 노드의 개수이므로 그대로 출력한다
        }
        else if (menu == 5) { // 전체 노드를 출력하는 코드
            for (int i = 0; i < list.size; i++) {//반복문으로 전체 노드를 출력하는 코드
                printf("%d번 노드: %d\n", i + 1, list.cur[i]->data); //1을 더해서 몇번째인지 알게 하기 위해 더한 1
            }
        }
        else if (menu == 6) { //노드를 뒤집는 코드
            for (int i = 0; i < list.size / 2; i++) { //반복문과 구조체 포인터를 사용하여 맨위와 맨앞 맨뒤에 1칸 앞 맨 앞의 1칸 뒤를 바꿔주는 코드
                int swap = list.cur[i]->data; // 두 숫자를 바꿔주는 코드
                list.cur[i]->data = list.cur[list.size - i - 1]->data;
                list.cur[list.size - i - 1]->data = swap;
            }
        }
        else {//예외 처리
            printf("잘못된 입력입니다.\n");
        }
    }

    free(num); // 동적할당 해제
    return 0;
}
