#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct { //각각 번호, 이름, 주소4가지, 점수를 순서대로 등록해놓은 구조체
	int num;
	char* name;
	char* adr[4];
	double grade;
} students;

int len(char* str) {//문자열의 길이를 알기 위해 만든 함수
	int i = 0;
	while (str[i] != '\0') i++;
	return i;
}

void copy(char* str1, char* str2) {//문자열을 복사하는 함수
	int i = 0;
	while (str2[i] != '\0') {
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

int compare(char* s1, char* s2) {//문자열 두 개를 비교하는 함수, 나중에 정렬하거나 두 문자열이 같은지 다른지 비교하기 위해 사용됌
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] != s2[i]) return s1[i] - s2[i];
		i++;
	}
	return s1[i] - s2[i];
}


int main() {
	int n = 0;
	students* s = (students*)malloc(sizeof(students) * n); //s를 동적할당을 해서 나중에 학생을 추가하거나 삭제할 때 쓰일 변수

	while (1) {
		int menu; //사용자가 진행하고자하는 작업을 선택할 수 있게 하는 변수
		printf("현재 출석부 : \n");

		if (n > 1) { //번호 이름 주소 점수로 정렬을 한 것이다
			for (int i = 0; i < n - 1; i++) {
				for (int j = i + 1; j < n; j++) {
					int num1 = 0;

					if (s[i].num > s[j].num) {//두 번호의 비교
						num1 = 1;
					}
					else if (s[i].num == s[j].num) { //번호가 같다면 이름을 비교
						int num2 = compare(s[i].name, s[j].name); //char같은 문자열을 정수형 변수같이 바로 비교할 수 없으므로 아까 두 문자열을 아스키코드로 비교해주는 함수에 넣어 계산하는 과정
						if (num2 > 0) { //num2가 0보다 크다는 의미는 앞에 있는 값의 아스키코드가 크다는 의미고 상대적으로 나중에 나오는 문자라는 의미이다
							num1 = 1; // 상대적으로 나중에 나오는 문자이므로 나중에 바꿔주기 위해 num을 1로 바꿈
						}
						else if (num2 == 0) { // 만약 두 문자열의 아스키코드, 즉 두 문자열이 같다면 주소를 비교하는 코드
							int num3 = 0;

							for (int k = 0; k < 4; k++) {//주소를 비교하는 코드
								num3 = compare(s[i].adr[k], s[j].adr[k]);
								if (num3 != 0) {//만약 나라가 다르다면 그 뒤에 있는 도를 비교하지 않고 반복문을 탈출하는 코드
									break;
								}
							}

							if (num3 > 0) {//만약 앞에 온 값의 아스키코드가 크다면 큰 값은 뒤로 보내야함으로 순서를 바꿔주는 코드
								num1 = 1;
							}
							else if (num3 == 0) { //만약 주소도 같다면 점수로 나누는 코드
								if (s[i].grade < s[j].grade) { //만약 뒤에 온 점수가 크다면 점수가 높아야지 앞으로 와야함으로 순서를 바꿔야한다
									num1 = 1;
								}
							}
						}
					}

					if (num1 == 1) {//num1 == 1인 모든 경우에 해당하는 두 자료를 바꿔주는 코드
						students swap = s[i];
						s[i] = s[j];
						s[j] = swap;
					}
				}
			}
		}

		for (int i = 0; i < n; i++) {//정렬이 완료된 모든 자료를 출력하는 코드
			printf("%d %s %s %s %s %s %lf\n", s[i].num, s[i].name, s[i].adr[0], s[i].adr[1], s[i].adr[2], s[i].adr[3], s[i].grade);
		}

		//사용자가 원하는 작업을 물어보는 코드
		printf("\n0. exit\n1. 학생 찾기\n2. 학생 추가/삭제\n3. 출석부 저장 또는 불러오기\nmenu : ");
		scanf("%d", &menu);

		if (menu == 0) {//0 입력시 프로그램이 종료되는 코드
			printf("\n프로그램을 종료합니다. ");
			for (int i = 0; i < n; i++) {
				free(s[i].name);
				for (int k = 0; k < 4; k++) free(s[i].adr[k]);
			}
			free(s); //동적할당한 모든 변수를 해제
			break;
		}

		else if (menu == 1) {//1을 입력하면 학생을 찾는 기능을 수행할 코드
			students eqs;
			int fs;//학생을 찾는 변수
			if (n == 0) { //학생이 없다면 출력하는 결과값
				printf("학생을 먼저 등록해주세요. ");
				continue;
			}
			//학생의 정보를 확인하기 위한 코드 만약 밑에 세가지 중 하나를 안다면 해당하는 학생의 이름을 출력하는 코드
			printf("1. 번호 2. 주소 3. 성적\n한 가지를 선택해주세요. : ");
			scanf("%d", &fs);

			//번호를 입력하겠다 하면 입력한 번호와 적혀있는 번호를 비교하는 코드
			if (fs == 1) {
				scanf("%d", &eqs.num);
				for (int i = 0; i < n; i++) {
					if (s[i].num == eqs.num) printf("학생의 이름은 %s입니다. ", s[i].name);
				}
			}
			//주소를 입력한다 하면 입력한 주소와 기존에 주소를 함수를 통해 비교하는 코드
			else if (fs == 2) {
				char arr1[100], arr2[100], arr3[100], arr4[100];
				printf("주소를 입력하세요 (국가 도 시 구) : ");
				scanf("%s %s %s %s", arr1, arr2, arr3, arr4);

				for (int i = 0; i < n; i++) {
					if (compare(s[i].adr[0], arr1) == 0 && compare(s[i].adr[1], arr2) == 0 && compare(s[i].adr[2], arr3) == 0 && compare(s[i].adr[3], arr4) == 0) {
						printf("학생의 이름은 %s입니다. ", s[i].name);
					}
				}
			}
			//점수를 입력하겠다고 하면 입력한 점수와 기존의 점수를 비교하여 해당하는 학생의 이름을 출력하는 코드
			else if (fs == 3) {
				scanf("%lf", &eqs.grade);
				for (int i = 0; i < n; i++) {
					if (s[i].grade == eqs.grade) printf("학생의 이름은 %s입니다. ", s[i].name);
				}
			}
		}

		else if (menu == 2) {//학생을 출석부에 추가하거나 삭제하는 코드
			int num;
			char eqname[100], arr1[100], arr2[100], arr3[100], arr4[100];
			double grade;

			printf("등록 혹은 삭제할 학생의 번호 이름 주소 성적을 입력하세요. : "); //학생의 정보를 입력
			scanf("%d %s %s %s %s %s %lf", &num, eqname, arr1, arr2, arr3, arr4, &grade);

			int del = -1;//인덱스에 겹치는 부분을 없애기 위해 음수로 선언
			for (int i = 0; i < n; i++) { //만약 사용자가 입력한 학생의 번호, 이름, 주소, 점수가 모두 같다면 해당학생은 삭제하는 코드
				if (s[i].num == num && compare(s[i].name, eqname) == 0 && compare(s[i].adr[0], arr1) == 0 && compare(s[i].adr[1], arr2) == 0 && compare(s[i].adr[2], arr3) == 0 && compare(s[i].adr[3], arr4) == 0 && s[i].grade == grade) {
					del = i;//삭제할 인덱스를 del에 복사 후 아래의 조건문에 도달하면 삭제되는 코드
					break;
				}
			}

			if (del != -1) {
				free(s[del].name); //s자체를 반남하지 않는 이유는 name, adr은 포인터 값이므로 s를 해제하면 안에 있는 주소가 날아가버리기 때문에 먼저 해제하여 주소는 살리고 메모리만 반납하기 위함이다
				for (int k = 0; k < 4; k++) free(s[del].adr[k]);

				for (int j = del; j < n - 1; j++) {//아까 복사한 인덱스보다 큰 값만 앞으로 땅겨오는 코드
					s[j] = s[j + 1];
				}
				n--; //하나가 삭제되었으니 하나 줄여주고 동적할당을 다시 받음
				s = (students*)realloc(s, sizeof(students) * n);
				printf("해당 학생이 삭제되었습니다. ");
			}
			else {//만약 처음보는 학생이라면 실행되는 코드
				n++;//추가해야함으로 1을 더하고 재할당 받는 코드
				s = (students*)realloc(s, sizeof(students) * n);

				s[n - 1].num = num; //가장 큰 수보다 1작게 하여 인덱스를 만들고 안에 번호와 점수를 넣는다
				s[n - 1].grade = grade;

				s[n - 1].name = (char*)malloc(len(eqname) + 1);//name은 동적할당으로 할당받아 넣고 1을 더하는 이유는 널문자 때문이다
				copy(s[n - 1].name, eqname);//입력한 문자열을 복사하기 위해 아까 만들어둔 복사 함수 사용

				char* Arr[4] = { arr1, arr2, arr3, arr4 };//주소를 복사하는 코드
				for (int k = 0; k < 4; k++) {
					s[n - 1].adr[k] = (char*)malloc(len(Arr[k]) + 1);
					copy(s[n - 1].adr[k], Arr[k]);//name과 마찬가지로 문자열 복사를 위해 함수 사용
				}
				printf("학생이 추가되었습니다. ");
			}
		}

		else if (menu == 3) {//만약 메뉴에서 3을 입력한다면 현재 작성한 출석부를 저장하거나 불러오는 코드
			int sub;
			printf("1. 저장, 2. 불러오기 : "); //저장할지 불러올지 선택하는 코드
			scanf("%d", &sub);

			if (sub == 1) {//저장하는 작업을 하는 코드
				FILE* f = fopen("attendance sheet.txt", "w"); //파일을 열기 위해 w로 열어주고 t,b를 입력하지 않으면 알아서 텍스트 모드로 열린다
				if (f != NULL) { //파일이 존재한다면 실행되는 코드 w모드여서 실행되긴하지만 혹시 모를 예외적인 상황에 대비하기 위해 마련한 안전장치
					fprintf(f, "%d\n", n);//지금까지 입력한 학생들의 수를 기록하여 나중에 불러올 때 사용하기 위해서이다
					for (int i = 0; i < n; i++) {//지금까지 모든 학생들의 정보를 fprintf로 파일에 저장하는 코드
						fprintf(f, "%d %s %s %s %s %s %lf\n", s[i].num, s[i].name, s[i].adr[0], s[i].adr[1], s[i].adr[2], s[i].adr[3], s[i].grade);
					}
					fclose(f); //파일 닫기
					printf("출석부를 저장했습니다. ");
				}
			}
			else if (sub == 2) { // 만약 불러오기를 원한다면 진행되는 코드
				FILE* f = fopen("attendance sheet.txt", "r");
				if (f != NULL) { //파일이 존재한다면 진행되는 코드 r모드 즉 읽기 모드이기에 파일이 존재하지 않는다면 실행되지 않는 코드이다
					for (int i = 0; i < n; i++) {//포인터를 먼저 해제하여 안에 저장된 메모리를 잃지 않게한다
						free(s[i].name);
						for (int k = 0; k < 4; k++) free(s[i].adr[k]);
					}

					fscanf(f, "%d", &n); //아까 파일을 저장할 때 넣은 n을 읽어오는 코드
					s = (students*)realloc(s, sizeof(students) * n);//동적할당을 다시 받아 학생 수를 기록해놓고 나중에 모든 학생을 읽어올 때 쓰일 변수

					char eqname[100], arr1[100], arr2[100], arr3[100], arr4[100];
					for (int i = 0; i < n; i++) {//텍스트 파일에 쓰여진 모든 학생들의 정보를 읽어오는 반복문
						fscanf(f, "%d %s %s %s %s %s %lf", &s[i].num, eqname, arr1, arr2, arr3, arr4, &s[i].grade);

						s[i].name = (char*)malloc(len(eqname) + 1); //아까 설명한 name을 읽어오고 널문자 때문에 1을 더하는 코드
						copy(s[i].name, eqname); //문자열은 한 번에 복사할 수 없기에 호출한 문자열 복사 함수

						char* Arr[4] = { arr1, arr2, arr3, arr4 };//주소값을 이름과 같이 읽어오고 저장하는 과정

						for (int k = 0; k < 4; k++) {//이름과 같이 문자열이므로 1을 더해서 할당받고 문자열을 복사하는 함수를 호출하는 반복문
							s[i].adr[k] = (char*)malloc(len(Arr[k]) + 1);
							copy(s[i].adr[k], Arr[k]);
						}
					}
					fclose(f);//파일 닫기
					printf("출석부를 불러왔습니다. ");
				}
				else { //파일이 존재하지 않는다면 출력되는 결과값
					printf("저장된 파일이 없습니다. ");
				}
			}
		}
	}

	return 0;
}