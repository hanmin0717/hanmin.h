#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 문자열 길이 구하는 함수
int len(char* s) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

int main() {
    // 입력 문자열 저장 배열
    char* a = (char*)malloc(sizeof(char) * 10001);
    if (a == NULL) return 1;

    printf("HTML을 입력하세요:\n");

    // 줄바꿈가 입력될 때까지 한 글자씩 직접 배열에 저장
    int count = 0;
    char ch;
    while (count < 10000) {
        scanf("%c", &ch);
        if (ch == '\n') break;
        a[count] = ch;
        count++;
    }
    a[count] = '\0';

    // 태그 이름을 저장할 스택 배열
    char* b = (char*)malloc(sizeof(char) * 5000);
    if (b == NULL) {
        free(a);
        return 1;
    }
    b[0] = '\0';

    int depth = 0;
    int n = len(a);
    int i = 0;
    int err = 0;

    while (i < n && !err) {
        // 공백 문자 건너뛰기
        if (a[i] == ' ' || a[i] == '\t' || a[i] == '\n' || a[i] == '\r') {
            i++;
            continue;
        }

        //태그 처리
        if (a[i] == '<') {
            int j = i + 1;
            while (j < n && a[j] != '>') j++;

            if (j >= n) {
                err = 1;
                break;
            }

            // 태그명 추출
            int tag_len = j - (i + 1);
            char* c = (char*)malloc(sizeof(char) * (tag_len + 1));
            for (int k = 0; k < tag_len; k++) {
                c[k] = a[i + 1 + k];
            }
            c[tag_len] = '\0';

            // 닫는 태그 처리
            if (c[0] == '/') {
                char* name = c + 1;

                if (depth == 0) {
                    err = 1;
                    free(c);
                    break;
                }

                // 스택(의 맨 뒤에서부터 마지막 태그의 시작 위치 탐색
                int b_len = len(b);
                int last = b_len - 1;
                if (last > 0) {
                    last--;
                    while (last >= 0 && b[last] != ' ') last--;
                }
                char* last_tag = b + (last + 1);

                // 스택의 태그와 현재 닫는 태그 이름 직접 비교
                int match = 1;
                int idx = 0;
                while (name[idx] != '\0' && last_tag[idx] != ' ') {
                    if (name[idx] != last_tag[idx]) {
                        match = 0;
                        break;
                    }
                    idx++;
                }
                if (name[idx] != '\0' || last_tag[idx] != ' ') {
                    match = 0;
                }

                if (!match) {
                    err = 1;
                    free(c);
                    break;
                }

                // pop 연산
                b[last + 1] = '\0';
                depth--;

                printf("%*s</%s>\n", depth * 4, "", name);
                free(c);
            }
            // 여는 태그 처리
            else {
                printf("%*s<%s>\n", depth * 4, "", c);

                // push 연산
                int b_len = len(b);
                int idx = 0;
                while (c[idx] != '\0') {
                    b[b_len++] = c[idx++];
                }
                b[b_len++] = ' ';
                b[b_len] = '\0';

                depth++;
                free(c);
            }
            i = j + 1;
        }
        // 텍스트 처리
        else {
            int j = i;
            while (j < n && a[j] != '<') j++;

            // 의미 없는 뒤쪽 공백 제거
            int txt_len = j - i;
            while (txt_len > 0 && (a[i + txt_len - 1] == ' ' || a[i + txt_len - 1] == '\t' || a[i + txt_len - 1] == '\r' || a[i + txt_len - 1] == '\n')) {
                txt_len--;
            }

            if (txt_len > 0) {
                printf("%*s%.*s\n", depth * 4, "", txt_len, a + i);
            }
            i = j;
        }
    }

    if (depth != 0) err = 1;

    if (err) {
        printf("오류: 잘못된 태그 구조입니다.\n");
    }

    // 메모리 해제
    free(b);
    free(a);

    return 0;
}
