#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    // 1부터 20까지의 숫자의 존재 여부를 저장할 배열
    int arr[21] = { 0 };

    char ch[10];
    int x;

    printf("연산을 선택하세요. (1 <= x <= 20, 종료하려면 exit 입력)\n");
    printf("add X\nremove X\ncheck X\ntoggle X\nall 0\nempty 0\nexit\n\n");

    while (1) {
        // 입력을 받음
        printf("input : ");
        scanf("%s", ch);

        // 프로그램 종료
        if (ch[0] == 'e' && ch[1] == 'x' && ch[2] == 'i' && ch[3] == 't' && ch[4] == '\0') {
            printf("프로그램을 종료합니다.\n");
            return 0; //프로그램 빠져나감
        }
        // add 명령어 처리
        else if (ch[0] == 'a' && ch[1] == 'd' && ch[2] == 'd' && ch[3] == '\0') {
            scanf("%d", &x);
            if (x >= 1 && x <= 20) {
                arr[x] = 1;
            }
        }
        // remove 명령어 처리
        else if (ch[0] == 'r' && ch[1] == 'e' && ch[2] == 'm' && ch[3] == 'o' && ch[4] == 'v' && ch[5] == 'e' && ch[6] == '\0') {
            scanf("%d", &x);
            if (x >= 1 && x <= 20) {
                arr[x] = 0;
            }
        }
        // check 명령어 처리
        else if (ch[0] == 'c' && ch[1] == 'h' && ch[2] == 'e' && ch[3] == 'c' && ch[4] == 'k' && ch[5] == '\0') {
            scanf("%d", &x);
            if (x >= 1 && x <= 20) {
                if (arr[x] == 1) printf("1\n");
                else printf("0\n");
            }
        }
        // toggle 명령어 처리
        else if (ch[0] == 't' && ch[1] == 'o' && ch[2] == 'g' && ch[3] == 'g' && ch[4] == 'l' && ch[5] == 'e' && ch[6] == '\0') {
            scanf("%d", &x);
            if (x >= 1 && x <= 20) {
                if (arr[x] == 1) arr[x] = 0;
                else arr[x] = 1;
            }
        }
        // all 명령어 처리
        else if (ch[0] == 'a' && ch[1] == 'l' && ch[2] == 'l' && ch[3] == '\0') {
            scanf("%d", &x);
            for (int i = 1; i <= 20; i++) {
                arr[i] = 1;
            }
        }
        // empty 명령어 처리
        else if (ch[0] == 'e' && ch[1] == 'm' && ch[2] == 'p' && ch[3] == 't' && ch[4] == 'y' && ch[5] == '\0') {
            scanf("%d", &x);
            for (int i = 1; i <= 20; i++) {
                arr[i] = 0;
            }
        }
        // 오타 예외 처리
        else {
            scanf("%d", &x); // 오타 뒤에 오는 숫자를 읽어서 버림
            printf("잘못된 명령어입니다. 다시 입력해주세요.\n\n");
            continue;
        }

        // 현재 집합 상태 출력
        printf("집합 : { ");
        for (int i = 1; i <= 20; i++) {
            if (arr[i] == 1) {
                printf("%d, ", i);
            }
        }
        printf("}\n\n");
    }

    return 0;
}
