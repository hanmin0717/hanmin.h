#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int length1(char str[]); //문자열의 길이를 탐색하는 두개의 함수
int length2(char str[]);

int main() {
    char str1[99], str2[99]; //입력하는 문자열, 내가 찾을 문자열 선언 
    int len1, len2; // 함수를 호출해서 문자열의 길이를 반환받는 변수
    int p1, p2;

    printf("최대 99까지 문자 입력 <inputStr> : ");
    scanf("%s", str1);

    printf("찾는 문자열 <subStr> : ");
    scanf("%s", str2);

    len1 = length1(str1); //함수 호출해서 문자열의 길이를 반환받는 것
    len2 = length2(str2);

    printf("%s의 위치 : ", str2);

    for (p1 = 0; p1 <= len1 - len2; p1++) { //반목분으로 입력한 문자열과 찾으려는 문자열을 비교하는 것
        for (p2 = 0; p2 < len2; p2++) {
            if (str1[p1 + p2] != str2[p2])
                break;
        }

        if (p2 == len2)
            printf("%d ", p1 +1);
    }

    return 0;
}

int length1(char str[]) {
    int i = 0;
    while (1) {
        if (str[i] == '\0') //널문자를 활용하여 문자열의 길이를 탐색하는 코드
            break;
        i++;
    }
    return i; // 문자열 길이 반환 
}

int length2(char str[]) {
    int i = 0;
    while (1) {
        if (str[i] == '\0') //널문자를 활용하여 문자열의 길이를 탐색하는 코드
            break;
        i++;
    }
    return i;// 문자열 길이 반환
}
