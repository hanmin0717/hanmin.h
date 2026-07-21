#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int a, add = 0;
	double avg;

	printf("몇 개의 원소를 할당하겠습니까? : ");
	scanf("%d", &a);

	if (a < 0) { // 0이하의 숫자를 입력하면 프로그램 종료 
		printf("잘못입력하셨습니다");
	}
	else {
		int* p = (int*)malloc(sizeof(int) * a); //입력받은 원소의 개수를 이용하여 동적할당으로 사용  

		int max; //최댓값과 최솟값을 입력받기 위한 변수들
		int min;

		for (int i = 0; i < a; i++) {
			printf("정수형 데이터 입력 : ");
			scanf("%d", &p[i]); //동적할당 받은 변수를 저장

			if (i == 0) { //최댓값과 최솟값을 구하기 위한 코드
				max = p[0];
				min = p[0];
			}

			if (min > p[i]) min = p[i];
			if (max < p[i]) max = p[i];


			add += p[i]; // 입력받은 모든 값들을 더해주는 코드

			avg = (double)add / (double)a; //add 변수를 이용하여 평균값을 구하는 코드 + int 형을 double 형으로 바꿔서 avg라는 double 형 변수를 계산하기 위한 코드
		}

		//마지막 결과값 출력
		printf("최솟값 : %d\n", min);
		printf("최댓값 : %d\n", max);
		printf("전처합 : %d\n", add);
		printf("평 균 : %lf\n", avg);
	}
}
