#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;

    // 행과 열 크기 입력 받기
    printf("숫자를 입력하세요. : ");
    scanf("%d %d", &a, &b);

    // 2차원 배열 동적 할당
    int** p = (int**)malloc(a * sizeof(int*));
    for (int i = 0; i < a; i++) {
        p[i] = (int*)malloc(b * sizeof(int));
    }

    // 변수 초기화
    int total_cells = a *b;
    int count = 1;

    // 중앙 좌표 설정
    int cx = a / 2;
    int cy = b / 2;

    // 시작점 채우기
    p[cx][cy] = count++;

    // 반지름 r을 늘려가며 채우기
    int r = 1;
    while (count <= total_cells) {
        // 반지름을 기준으로 왼쪽 꼭짓점 구하기
        int curr_row = cx;
        int curr_col = cy - r;

        // 4개의 방향 
        int dr[4] = { 1, -1, -1, 1 };
        int dc[4] = { 1, 1, -1, -1 };

        // 4개 변을 순서대로 출력
        for (int dir = 0; dir < 4; dir++) {
            for (int step = 0; step < r; step++) {
                // 다음 칸으로 이동
                curr_row += dr[dir];
                curr_col += dc[dir];

                // 배열 범위 내에 있는지 확인
                if (curr_row >= 0 && curr_row < a && curr_col >= 0 && curr_col < b) {
                    p[curr_row][curr_col] = count++;
                }
            }
        }
        r++; // 반지름 증가
    }

    // 마지막 결과 출력
    printf("\n[출력 결과]\n");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%3d ", p[i][j]);
        }
        printf("\n");
    }

    // 동적 할당 해제
    for (int i = 0; i < a; i++) {
        free(p[i]);
    }
    free(p);

    return 0;
}
