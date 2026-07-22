#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void arr_ij(int* sizeRow, int* sizeCol, int** pArr); //달팽이 모양을 만드는 함수
void print(int* row, int* col, int** pArr); //달팽이 모양을 출력하는 함수

int main() {
    int** arr = NULL; //2차원 포인터 변수를 만들어서 나중에 2차원 배열을 동적할당으로 받아줄 변수
    int row, col, sizeRow, sizeCol; //행과 열을 입력받는 변수 또는 입력받은 값을 복제하는 변수

    //행과 열 각각 입력받기
    printf("행의 수를 입력하세요 : "); 
    scanf("%d", &sizeRow);
    printf("열의 수를 입력하세요 : ");
    scanf("%d", &sizeCol);

    //행과 열을 복제해서 나중에 출력때 쓸 변수
    row = sizeRow; 
    col = sizeCol;

    //2차원 배열 선언, *arr 변수에 힙 영역의 메모리를 할당받아 행을 만들고 만들어진 arr[i]에 한 번 더 동적할당을 함으로써 2차원 배열을 만든 코드 
    arr = (int**)malloc(sizeof(int*) * sizeRow);
    for (int i = 0; i < sizeRow; i++) {
        arr[i] = (int*)malloc(sizeof(int) * sizeCol);
    }
    //달팽이 모양을 만드는 함수 호출
    arr_ij(&sizeRow, &sizeCol, arr);
    //달팽이 모양을 출력하는 함수 호출
    print(&row, &col, arr);

    //2차원 배열 동적할당 해제
    for (int i = 0; i < sizeRow; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

void arr_ij(int* sizeRow, int* sizeCol, int** pArr) {
    int r = *sizeRow; //*sizeRow와 *sizeCol은 각각 주소값이 가리키는 값으로 메모리를 건드리기 때문에 모든 함수에 영향을 줄 수 있기 때문에 값을 복제하여 사용해서 나중에 출력을 할 때 문제가 생기지 않게 한 코드 
    int c = *sizeCol;

    int d = 1; //행과 열의 이동을 하게 하는 변수 맨 밑에는 -1을 곱하여 방향도 바꾸는 역할을 한다
    int num = 1; //출력할 숫자
    int row = 0, col = -1; //행과 열의 시작점을 결정짓는 변수

    while (r > 0 && c > 0) { //행과 열의 크기가 0보다 작다면 반복을 끝내는 코드
        for (int i = 0; i < c; i++) {//가로값 결정하는 코드
            col += d; //가로값의 시작점을 정하고 점점 키우면서 가로를 채우는 코드
            pArr[row][col] = num++; //행의 값은 고정해야함으로 row의 값은 건들이지 않는다
        }
        r--; //열에 값이 하나 끝날 때마다 행의 값은 하나 줄어들기 때문에 행의 값을 하나 줄인다
        if (r <= 0) break; //행의 값이 0보다 작거나 같다면 끝내는 코드

        for (int i = 0; i < r; i++) { //세로의 값을 결정하는 코드
            row += d; //세로는 행에 영향을 받기에 행에 d를 더해서 행의 값에 변화를 주는 코드
            pArr[row][col] = num++; //col은 고정해두고 행의 값만 바꾸면서 숫자를 1씩 커지게 하면 세로의 행이 만들어지게 하는 코드
        }
        c--; //이 코드를 실행하기 전에는 열의 크기가 행의 크기보다 한개가 크기때문에 1을 줄여서 행의 크기와 열의 크기를 같도록 맞춰준다

        d *= -1; //행과 열이 커지는 방향으로 갔다면 이번에는 행과 열을 작아지게 만들어야한다 달팽이 모양을 보면 행은 열을 따라서 커질 때는 커지지만 작아질 때는 작아지기에 두 방향을 동시에 바꿔주어야한다
    }
}

void print(int* row, int* col, int** pArr) { //2차원 배열을 출력하는 코드
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            printf("%d\t", pArr[i][j]);
        }
        printf("\n");
    }
}
