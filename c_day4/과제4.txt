#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct { //년, 월, 일을 담고있는 구조체
    int year;
    int month;
    int day;
} date;

typedef struct { //시간, 분, 초를 담고있는 구조체
    int hour;
    int minute;
    int second;
} time;

typedef struct {//위에 두 구조체를 담고 있는 중첩 구조체
    date date;
    time time;
} datetime;

int yoonyeun(int year); //윤년을 판단하는 함수
int daymonth(int year, int month); //년을 가지고 월을 판단하는 함수

int main() {
    datetime dt[2]; // 두개의 시간을 입력해야하기 때문에 dt라는 이름을 2개 만들었다 

    //두개의 시간을 받는 코드
    printf("1. 연 월 일 시 분 초 순서대로 입력해주세요: ");
    scanf("%d %d %d %d %d %d", &dt[0].date.year, &dt[0].date.month, &dt[0].date.day, &dt[0].time.hour, &dt[0].time.minute, &dt[0].time.second);

    printf("2. 연 월 일 시 분 초 순서대로 입력해주세요: ");
    scanf("%d %d %d %d %d %d", &dt[1].date.year, &dt[1].date.month, &dt[1].date.day, &dt[1].time.hour, &dt[1].time.minute, &dt[1].time.second);

    //전체 초를 구하는 코드들
    int totsec[2]; //전체 초를 알기 위해 만든 변수

    for (int i = 0; i < 2; i++) {
        int days = (dt[i].date.year - 1) * 365 + yoonyeun(dt[i].date.year); // 현재의 년은 2월이 지났는지 또는 윤년인지 아닌지 모르기에 일단을 1을 빼주고 나머지는 365를 곱해서 월을 찾아준다 그 후 입력한 년이 얼마만큼의 윤년을 지나왔는지 알 수 있는 yoonyeun 함수를 호출하여 지나온 윤년을 더해주었다. 이유는 윤년은 2월에 하루 더 추가되는 것이기에 윤년을 지나온 횟수를 더한 것이나 다름없는 계산이기 때문이다

        for (int j = 1; j < dt[i].date.month; j++) { //daymonth 함수를 호출하여 이번 년도를 기준으로 지금까지의 월을 일로바꿔주는 코드
            days += daymonth(dt[i].date.year, j);
        }

        days += (dt[i].date.day - 1); //1월 1일을 기준으로 1월 1일이 한 번 더 중복으로 들어가는 것을 방지하기 위해 1을 빼주었다

        totsec[i] = days * 86400 + dt[i].time.hour * 3600 + dt[i].time.minute * 60 + dt[i].time.second; //하루를 초단위로 나타내면 86400이고 시간을 초단위로 나타내면 3600이고 분을 초단위로 나타내면 60 초는 초니까 1을 곱해주는 것이지만 안곱한 것과 같기에 생략한 입력한 전체 초를 알게 해주는 코드
    }

    int minsec;
    //두 시간의 초의 차이를 계산하기 위한 변수로 difsec를 사용하고 음수가 나오면 안되기에 경우의 수를 나우어 계산하는 코드
    if (totsec[1] > totsec[0]) {
        minsec = totsec[1] - totsec[0];
    }
    else {
        minsec = totsec[0] - totsec[1];
    }

    //1시간은 3600초로 나타낼 수 있으므로 나누어서 몫만 가져가게 하는 코드 
    int hours = minsec / 3600;
    //분은 위에 있는시간에 나머지에 60을 나누어 몫을 가져가는 코드
    int minutes = (minsec % 3600) / 60;
    //초는 60초가 넘어갈 수 없고 초는 여기있는 시간 단위 중 가장 작은 단위이므로 나눠서 나머지가 나온다면 무조건 초이기 때문에 사용한 코드
    int seconds = minsec % 60;

    //결과 출력
    printf("\n출력 : %d시 %d분 %d초\n", hours, minutes, seconds);

    return 0;
}

int yoonyeun(int year) {
    int a = 0; //윤년을 지나온 횟수를 세는 역할의 변수
    for (int i = 1; i < year; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0)) {//윤년이라면 a에 1을 더함으로써 횟수를 알 수 있다
            a++;
        }
    }
    return a;
}

int daymonth(int year, int month) {
    int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //0을 채워준 이유는 인덱스 1을 1월에 오게함으로써 코드의 편리함을 높이기 위해서이다

    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) { //윤년을 판단하는 코드
        return 29;
    }
    return days[month]; //해당하는 월을 반환하는 코드
}
