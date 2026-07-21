#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int strlength(char* str); //문자열의 길이를 계산하는 함수

int main() {
    char str1[100];
    int a[100] = { 0 };

    printf("문자열을 입력하세요(띄어쓰기 금지): "); //scanf를 사용하면 띄어쓰기가 쓰이는 동시에 종료가 되기 때문에 띄어쓰기 금지를 넣었다
    scanf("%s", str1); 

    // 문자열 거꾸로 출력하는 반복문
    for (int i = strlength(str1) - 1; i >= 0; i--) {
        printf("%c", *(str1 + i));
    }
    printf("\n");

    // 각 문자 등장 횟수 계산하는 반복문
    for (int i = 0; i < strlength(str1); i++) {
        for (int j = i + 1; j < strlength(str1); j++) {
            if (*(str1 + i) == *(str1 + j)) a[i]++;
        }
    }

    // 가장 많이 나온 문자열을 찾기 위해 해당 문자열을 계산한 위의 반복문을 이용하여 a배열의 최댓값을 구하고 최댓값일 때에 인덱스가 무엇인지 알아오는 반복문
    int max = a[0];
    int store = 0;
    for (int i = 1; i < strlength(str1); i++) {
        if (max < a[i]) {
            max = a[i];
            store = i;
        }
    }

    //결과 출력
    printf("최다등장문자 : %c\n", *(str1 + store));

    return 0;
}

int strlength(char* str) {
    int i = 0;
    while (*(str + i) != '\0') { // 널문자가 나올 때까지 문자열의 길이를 측정
        i++;
    }
    return i; //문자열의 길이를 반환
}
