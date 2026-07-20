#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int min, max;
	int arr[10000];

	while (1) {
		printf("min : ");
		scanf("%d", &min);

		if (min < 1) { //숫자 입력 오류 방지
			printf("1보다 큰 숫자를 입력해주세요 ");
			continue;
		}

		break;
	}

	while (1) {
		printf("max : ");
		scanf("%d", &max);

		if (max > 10000 || max < 1) { // 숫자 입력 오류 방지
			printf("1부터 10000까지의 숫자로만 입력해주세요 ");
			continue;
		}
		break;
	}
	//숫자 정리
	for (int i = 0; i <= max - min; i++) {//arr에 최솟값부터 최댓값 저장하기
		arr[i] = min + i;
	}

	//제곱수 판단
	int store[10000];
	for (int i = 0; i < max - min + 1; i++) store[i] = arr[i];


	for (int i = 2; i * i< max; i++) { //제곱수 판별
		for (int j = 0; j < max - min + 1; j++) {
			if(arr[j]%(i*i) == 0) store[j] = 0;
		}
	}

	//마지막 출력
	int num = 0;
	for (int i = 0; i < max - min + 1; i++) {
		if (store[i] != 0) {
			num++;
		}
	}
	printf("제곱 ㄴㄴ수는 %d 개 입니다\n", num);
	for (int i = 0; i < max - min + 1; i++) {
		if (store[i] != 0) printf("%d\t", store[i]);
	}
}
