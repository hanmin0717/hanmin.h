#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int a[5][5] = { 0 };
    int num = 1; // 모래시계 모양에 숫자를 집어 넣기 위해 사용
    int s = 0, e = 4; //배열의 시작과 끝을 나타냄

    for (int i = 0; i < 5; i++) {
        for (int j = s; j <= e;j++) {
            a[i][j] = num++; // 행과 열에 num이 점점 커지는 코드
        }

        if (i < 2) { // i가 2보다 작다면 즉, i가 0과 1 일 때는 다음이 좁아져야하기 때문에 시작을 크게 하고 끝을 작게 하는 코드
            s++;
            e--;
        }
        else { // i가 2보다 크다면 다음을 넓혀줘야하므로 시작을 작게하고 끝을 크게 하는 코드
            s--;
            e++;
        }
    }

    for (int i = 0; i < 5;i++) { // 2차원 배열 출력
        for (int j = 0; j < 5; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
