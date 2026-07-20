#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int a[4][3], b[3][4];
    int n = 1; 
    for (int i = 0; i < 4; i++) {// 2차원 배열에 숫자를 대입하는 방법
        for (int j = 0; j < 3;j++) {
            a[i][j] = n++;
        }
    }

    printf("바꾸기 전 : \n");
    for (int i = 0; i < 4; i++) { //바꾸기 전의 숫자들의 나열
        for (int j = 0; j < 3;j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 3; i++) { // 입력한 2차원 배열의 행과 열을 바꾼 다른 2차원 배열에 대입
        for (int j = 0; j < 4;j++) {
            b[i][j] = a[j][i];
        }
    }
    
    printf("바꾼 후 : \n");
    for (int i = 0; i < 3; i++) { //입력한 2차원 배열의 행과 열을 바꾼 다른 2차원 배열에 대입한 배열을 출력
        for (int j = 0; j < 4;j++) {
            printf("%d\t", b[i][j]);
        }
        printf("\n");
    }

    return 0;
}
