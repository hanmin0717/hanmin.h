#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void check(int arr[], int n, int b);

int main() {
	int N, B, arr[100], d = 0;

	while (1) {
		printf("N : ");
		scanf("%d", &N);
		if (N % 2 == 0) { //홀수 예외 처리
			printf("홀수만 입력해주세요. \n");
			continue;
		}
		else if (N <= 0) { //음수 예외처리
			printf("양수로만 입력해주세요. \n");
			continue;
		}
		break;
	}
	while (1) {
		printf("b : ");
		scanf("%d", &B);
		if (B > N || B < 1) { //B가 숫자 사이에 없을 경우 예외 처리
			printf("1부터 %d까지의 숫자 중 하나를 입력해주세요. \n", N);
			continue;
		}
		break;
	}

	while(1){
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}
		for (int i = 0; i < N;i++) {
			for (int j = i + 1; j < N; j++) {
				if (arr[i] == arr[j]) d++;
			}
		}
		if (d != 0) { //숫자 중복 예외 처리 및 다시 입력 기능
			printf("숫자가 중복되었거나 다른 문제가 생겼습니다\n");
			d = 0; // 중복 초기화
			continue;
		}
		else if (d == 0) break;
	}

	check(arr, N, B);

	return 0;
}

void check(int arr[], int n, int b) {
	int b1;

	for (int i = 0; i < n; i++) {
		if (arr[i] == b) {
			b1 = i;
			break;
		}
	}

	int total = 0;

	for (int i = 0; i <= b1; i++) {
		for (int j = b1; j < n; j++) {

			if ((j - i + 1) % 2 != 0) { //B가 포함된 구간의 길이를 구해서 구간의 길이가 짝수이면 건너뛰고 홀수가 될 때까지 계산한다
				int g = 0;
				int s = 0;

				for (int k = i; k <= j; k++) { //구간 안에서 B보다 크거나 작은 숫자를 판단하여 두 숫자가 같다면 부분 수열의 개수에 1을 더한다
					if (arr[k] > b) g++;
					if (arr[k] < b) s++;
				}

				if (g == s) {
					total++;
				}
			}
		}
	}

	printf("중앙값이 %d인 부분수열의 개수 : %d\n", b, total);
}
