#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    typedef struct { //구조체를 학년, 점수, 이름 순으로 만들었다
        int grade;
        double score;
        char name[10];
    }student;

    student s[5]; //구조체를 5개의 배열로 나타냄

    for (int i = 0; i < 5; i++) { //학생들의 학년, 점수, 이름을 입력할 수 있도록 만든 반복문
        printf("%d번째 학생의 학년 성적 이름 순으로 입력 : ", i + 1);
        scanf("%d %lf %s", &s[i].grade, &s[i].score, s[i].name);

        if (s[i].grade > 4 || s[i].grade < 1) { //학년이 4학년 초과이거나 1학년 미만이라면 프로그램을 종료하도록 하는 코드
            printf("잘못 입력하셨습니다. ");
            return 0;
        }
        else if (s[i].score < 0 || s[i].score>4.5) { // 학점이 0점보다 작고 4.5보다 크다면 프로그램이 종료되도록 만든 코드
            printf("잘못 입력하셨습니다. ");
            return 0;
        }
    }

    //학생의 학년을 먼저 정렬하고 만약 학년이 같거나 앞에 학년이 작다면 점수를 보고 점수가 같거나 앞에 온 것이 작다면 이름의 첫 문자를 아스키코드로 입력받아 대소비교를 하는 코드
    printf("\n학생의 학년 성적 이름 출력 : \n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) { // 학년을 오름차순으로 정렬하는 코드
            if (s[j].grade > s[j + 1].grade) {
                student swap = s[j];
                s[j] = s[j + 1];
                s[j + 1] = swap;
            }
            else if (s[j].grade == s[j + 1].grade) { // 학년이 같을 때 점수 비교하는 코드
                if (s[j].score > s[j + 1].score) {
                    student swap = s[j];
                    s[j] = s[j + 1];
                    s[j + 1] = swap;
                }
                else if (s[j].score == s[j + 1].score) { // 점수까지 같을 때 이름 첫 글자 아스키코드 비교하는 코드
                    if ((int)s[j].name[0] > (int)s[j + 1].name[0]) {
                        student swap = s[j];
                        s[j] = s[j + 1];
                        s[j + 1] = swap;
                    }
                }
            }
        }
    }
    //결괴 출력
    for (int i = 0; i < 5; i++) printf("%d번째 학생 : %d %lf %s\n", i + 1, s[i].grade, s[i].score, s[i].name);


    return 0;
}
