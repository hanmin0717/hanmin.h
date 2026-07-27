#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS 300000
#define WORDLEN 50

typedef struct Node { //단어 중복 사용을 방지하기 위해 구조체 동적할당으로 리스트를 만들 때 사용될 구조체
    char data[WORDLEN];
} Node;

Node* node; //모든 함수애서 사용할 수 있게 전역 변수로 구조체 포인터 정의
int n = 0; //노드의 개수를 파악하기 위해 만든 전역변수 개수는 한 개 작음

void node_add(char* str); //입력한 단어를 노드로써 추가하는 함수
int comfirm_wordlen(char* str);//단어의 길이가 2음절인지 판단하는 함수
int confirm_sameword(char* str); // 같은 단어인지 판단하는 함수
int confirm_connect(char* str); // 최근에 노드에 저장된 단어와 방금 입력한 단어 사이의 연결을 확인하는 함수

int check_dictionary(char* str); // 텍스트 파일을 열어 존재하는 파일인지 아닌지 파일에 어디 부분을 읽어올 것인지 판단하는 함수

int main() {
    char enter_str[WORDLEN]; //입력할 단어를 잠시 저장해 놓는 변수
    char enter; // 시작 버튼

    node = (Node*)malloc(sizeof(Node));

    printf("시작하시려면 Enter를 누르시오. "); // 게임 시작 버튼 구현
    scanf("%c", &enter);
    printf("끝말잇기를 시작합니다.\n\n");

    while (1) { 
        printf("처음 단어 입력 : "); //입력한 단어르 저장하는 코드
        scanf("%s", enter_str);

        if (comfirm_wordlen(enter_str) == 0) { //단어의 길이를 판단하는 조건문
            printf("2글자 이상 입력해주세요. \n\n");
            continue;
        }
        if (check_dictionary(enter_str) == 0) { // 단어가 사전에 있는지 없는 지 판단하는 조건문
            printf("사전에 없는 단어이거나 외래어 혹은 혼종어는 입력할 수 없습니다. \n");
            continue;
        }
        if (comfirm_wordlen(enter_str) != 0) { //단어를 노드 인덱스 0에 저장하고 처음 단어 입력은 처음에만 나와야함으로 반복문을 탈출하게 하는 코드
            node_add(enter_str);
            break;
        }
    }

    while (1) {// 처음 단어 이후부터 계속 출력되게 하는 코드
        printf("현재 단어 : %s\n", node[n - 1].data); // 현재 단어를 알려줘서 뭘 입력해야할지 편하게 보여주는 코드
        printf("\n다음 단어 입력 : "); // 다음 단어 입력 코드
        scanf("%s", enter_str);

        if (comfirm_wordlen(enter_str) == 0) {//단어의 길이를 판단하는 조건문
            printf("2글자 이상 입력해주세요. \n\n");
            continue;
        }

        if (confirm_sameword(enter_str) == 0) { //이미 사용한 단어인지 판단하는 조건문
            printf("이미 한 번 사용한 단어입니다. \n\n");
            continue;
        }
        if (confirm_connect(enter_str) == 0) { //단어의 끝 글자와 단어의 앞 글자의 연결을 확인하는 조건문
            printf("단어가 연결되지 않습니다. \n\n");
            continue;
        }
        if (check_dictionary(enter_str) == 0) { //사전에 있는 단어인지 없는 단어인지 확인하는 조건문
            printf("사전에 없는 단어이거나 외래어 혹은 혼종어는 입력할 수 없습니다. \n");
            continue;
        }

        if (comfirm_wordlen(enter_str) != 0 && confirm_sameword(enter_str) != 0) {//단어를 만들어둔 구조체 동적할당에 인덱스 n으로 저장해두는 코드
            node_add(enter_str);
        }

    }
    free(node); // 구조체 동적할당 해제

    return 0;
}

void node_add(char* str) { //단어 노드를 추가하는 코드
    Node* new_node = (Node*)realloc(node, sizeof(Node) * (n + 1)); // 새로운 구조체 포인터를 설정해서 realloc으로 재할당 받고 
    strcpy(new_node[n].data, str); // 멤버 변수에 입력한 단어를 넣어서 node에 다시 저장하는 코드 
    node = new_node;

    n++; // 노드 개수 증가
}

int comfirm_wordlen(char* str) { // 단어 개수 판단 함수
    if (strlen(str) < 4) return 0; // 인코딩 949 기준으로 한글을 한글자당 2바이트 이기에 4보다 작거나 크거나 같다면이라는 조건문을 세워둠
    else if (strlen(str) >= 4) return 1;
}

int confirm_sameword(char* str) {
    for (int i = 0;i < n; i++) { // 같은 단어인지 판단하기 위해 저장해둔 멤버 변수들과 입력한 단어 사이의 비교를 해준 코드
        if (strcmp(str, node[i].data) == 0) return 0;
    }

    return 1;
}

int confirm_connect(char* str) { // 단어 연결 확인 함수
    int flen = (int)strlen(node[n - 1].data); //노드에 저장된 가장 최근 문자열의 길이로 문자열의 마지막 부분을 알아내는 코드

    char last[3] = { node[n - 1].data[flen - 2], node[n - 1].data[flen - 1], '\0' }; // 문자열들을 배열에 저장해서 나중에 같은지 아니면 두음법칙 적용 대상인지 판단하기 위한 코드

    char first[3] = { str[0], str[1], '\0' };

    if (strcmp(last, first) == 0) { //같은 글자이면 1 반환
        return 1;
    }
    //다른 글자이지만 다음 조건을 만족시키는 즉 두음법칙이라면 1을 반환
    if (strcmp(last, "리") == 0 && strcmp(first, "이") == 0) return 1;
    if (strcmp(last, "라") == 0 && strcmp(first, "나") == 0) return 1;
    if (strcmp(last, "락") == 0 && strcmp(first, "낙") == 0) return 1;
    if (strcmp(last, "란") == 0 && strcmp(first, "난") == 0) return 1;
    if (strcmp(last, "란") == 0 && strcmp(first, "안") == 0) return 1;
    if (strcmp(last, "람") == 0 && strcmp(first, "남") == 0) return 1;
    if (strcmp(last, "랑") == 0 && strcmp(first, "낭") == 0) return 1;
    if (strcmp(last, "래") == 0 && strcmp(first, "내") == 0) return 1;
    if (strcmp(last, "로") == 0 && strcmp(first, "노") == 0) return 1;
    if (strcmp(last, "록") == 0 && strcmp(first, "녹") == 0) return 1;
    if (strcmp(last, "론") == 0 && strcmp(first, "논") == 0) return 1;
    if (strcmp(last, "루") == 0 && strcmp(first, "누") == 0) return 1;
    if (strcmp(last, "력") == 0 && strcmp(first, "역") == 0) return 1;
    if (strcmp(last, "련") == 0 && strcmp(first, "연") == 0) return 1;
    if (strcmp(last, "렬") == 0 && strcmp(first, "열") == 0) return 1;
    if (strcmp(last, "령") == 0 && strcmp(first, "영") == 0) return 1;
    if (strcmp(last, "료") == 0 && strcmp(first, "요") == 0) return 1;
    if (strcmp(last, "류") == 0 && strcmp(first, "유") == 0) return 1;
    if (strcmp(last, "륙") == 0 && strcmp(first, "육") == 0) return 1;
    if (strcmp(last, "륜") == 0 && strcmp(first, "윤") == 0) return 1;
    if (strcmp(last, "률") == 0 && strcmp(first, "율") == 0) return 1;
    if (strcmp(last, "녀") == 0 && strcmp(first, "여") == 0) return 1;
    if (strcmp(last, "뇨") == 0 && strcmp(first, "요") == 0) return 1;
    if (strcmp(last, "뉴") == 0 && strcmp(first, "유") == 0) return 1;
    if (strcmp(last, "니") == 0 && strcmp(first, "이") == 0) return 1;

    return 0; // 나머지는 0으로 반환
}

int check_dictionary(char* str) {
    char* f[] = { "1579015_5000.txt", "1579015_10000.txt", "1579015_15000.txt", "1579015_20000.txt", "1579015_25000.txt", "1579015_30000.txt", "1579015_35000.txt",
    "1579015_40000.txt", "1579015_45000.txt", "1579015_50000.txt", "1579015_55000.txt", "1579015_60000.txt", "1579015_65000.txt", "1579015_70000.txt", "1579015_75000.txt"
    ,"1579015_80000.txt", "1579015_85000.txt", "1579015_90000.txt", "1579015_95000.txt", "1579015_100000.txt", "1579015_105000.txt", "1579015_110000.txt", "1579015_115000.txt"
    ,"1579015_120000.txt", "1579015_125000.txt", "1579015_130000.txt", "1579015_135000.txt", "1579015_140000.txt", "1579015_145000.txt", "1579015_150000.txt",
    "1579015_155000.txt", "1579015_160000.txt", "1579015_165000.txt", "1579015_170000.txt", "1579015_175000.txt", "1579015_180000.txt", "1579015_185000.txt",
    "1579015_190000.txt", "1579015_195000.txt", "1579015_200000.txt", "1579015_205000.txt", "1579015_210000.txt", "1579015_215000.txt", "1579015_217892.txt" };
    //텍스트 파일을 열기 위해 만든 배열에 파일의 이름을 넣어줌

    for (int i = 0; i < 44; i++) {// 반복문으로 파일을 다 열어주는 코드
        FILE* fp = fopen(f[i], "r");

        if (fp == NULL) { //파일이 존재하지 않으면 건너뛰는 코드
            continue;
        }

        char strp[WORDLEN];

        while (fgets(strp, sizeof(strp), fp) != NULL) { //파일이 끝날 때까지 읽으라는 반복문
            for (int j = 0; strp[j] != '\0'; j++) { //찾을 문자열이 널문자가 될때까지 반복
                if (strp[j] == '\n' || strp[j] == '\r') {//줄바꿈이 있으면 반복을 끝냄
                    strp[j] = '\0';
                    break;
                }
            }

            if (strlen(strp) == 0 || strncmp(strp, "#00", 3) == 0) {//#00이라는 문자열 혹은 빈 줄아라면 위에서 그 줄은 건너뛰는 코드
                continue;
            }

            int w = 0; //하이픈을 뺀 글자를 읽어오기 위해 사용할 변수
            for (int r = 0; strp[r] != '\0'; r++) {//널 문자를 발견하면 종료하는 반복문
                if (strp[r] != '-') {//하이픈같은 문자는 단어를 읽어올때 방해가 됨으로 읽어오지 않으려는 조건문
                    strp[w++] = strp[r]; //하이픈 제외하고 읽어오는 과정
                }
            }
            strp[w] = '\0';//위에 반복문이 끝나면 w의 맨마지막 글자를 널문자로 초기화하여 나중에 쓰레기값을 방지

            //입력한 문자열과 같은 문자열이 사전에 있다면 반복문 안에서 파일을 모드 닫는 코드
            if (strcmp(str, strp) == 0) {
                fclose(fp);
                return 1;
            }
        }

        fclose(fp);//파일이 모드 끝난다면 파일을 닫는 코드
    }
    return 0;
}
