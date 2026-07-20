#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int arr[8];
    int s;

    // 사용자로부터 8개의 정수 입력 받기
    for (int i = 0; i < 8; i++) {
        printf("%d : ", i + 1); // i가 0이기 때문에 i에 1을 더했음
        scanf("%d", &arr[i]);
    }
    printf("\n");

    // 정렬 전 초기 상태 출력
    for (int i = 0; i < 8; i++) {
        printf("%d   ", arr[i]);
    }
    printf("\n\n"); // 가독성을 위해 줄바꿈 추가

    for (int i = 7; i > 0; i--) {
        int max = 0; // 매 턴마다 0번 인덱스를 최댓값으로 가정

        // 0번부터 i번 범위 안에서 최댓값의 찾기
        for (int j = 1; j <= i; j++) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }

        // 최댓값이 맨 뒤에 있는 게 아닐 때만 교환
        if (max != i) {
            s = arr[i];
            arr[i] = arr[max];
            arr[max] = s;
        }

        // 중간 과정 출력
        for (int j = 0; j < 8; j++) {
            printf("%d   ", arr[j]);
        }
        printf("\n");
    }

    printf("\n");

    //  정렬 결과 출력
    for (int i = 0; i < 8; i++) {
        printf("%d : %d\n", i, arr[i]);
    }

    return 0;
}
