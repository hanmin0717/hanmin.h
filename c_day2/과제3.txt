#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int check(char s[]);

int main() {
    char arr[20]; 

    printf("음 입력\n");
    scanf("%s", arr);
    printf("\n"); //가독성을 위해 줄바꿈

    int result = check(arr); //함수 호출해서 값을 반환받음

    switch (result) { // 스위치 케이스 문을 사용해서 
    case 1:
        printf("결과 : ascending\n");
        break;
    case 2:
        printf("결과 : descending\n");
        break;
    case 3:
        printf("결과 : mixed\n");
        break;
    default:
        printf("잘못된 입력입니다.\n"); //예외처리
        break;
    }

    return 0;
}

int check(char s[]) { // 입력받은 문자열을 판단하는 함수
    char asc[] = "cdefgabC";
    char desc[] = "Cbagfedc";

    int as = 1;
    int des = 1;

    for (int i = 0; i < 8; i++) { // 문자열 비교하는 반본문
        if (s[i] != asc[i]) {
            as = 0;
        }
        if (s[i] != desc[i]) {
            des = 0;
        }
    }

    if (as == 1) { //값이 정확한지 반환하는 반환값 아니면 무엇인지 반환하는 반환값
        return 1;
    }
    else if (des == 1) {
        return 2;
    }
    else {
        return 3;
    }
}
