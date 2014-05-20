#include<stdio.h>
#include<windows.h>
#include<time.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENT13
#define YELLOW 14
#define WHITE 15

#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

void gotoxy(int, int); //커서 옮기는 함수다
void textcolor(int foreground, int background);
void wait(clock_t);

int YunNyun(int); //윤년 계산 함수, 29일, 28일로 나눈다.
int YNday(int, int);
int JeraWeek(int, int, int);



//
void gotoxy(int x, int y) //첫번째 인자는 가로, 두번째 인자는 세로 
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int foreground, int background) //foreground : 글자색, backgroung : 배경색
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void wait(clock_t time)
{
	clock_t start = clock();
	while (clock() - start < time);
}


///////////////////////////////////////////////////////
//달력계산
int YunNyun(int YNyear)
{
	//위에서 말했듯이 윤년 계산잼
	
	if (YNyear % 4 == 0 && (YNyear % 100 != 0 || YNyear % 400 == 0))
		return 29;
	else
		return 28;
}

int YNday(int year, int month)
{
	int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//각 월의 마지막 일수

	if (month == 2 && YunNyun(year))
	{
		return 29;
	}
	else
		return month_day[month];
}

bool Holiday()//휴일이면 참 아니면 거짓을 리턴
{
	int i;
	int Holidays[][] = {
		{ 1, 1 }, { 3, 1 }, { 5, 5 }, { 6, 6 }, { 8, 15 }, { 10, 3 }, { 10, 9 }, { 12, 25 }, { 1, 6 }, { 5, 26 }, {}
	}
}

int JeraWeek(int year, int month, int day) //제라의 공식
{
	// 제라의 공식 ((21 * ye / 4) + (5 * ar / 4) + (26 * (month + 1) / 10) + day - 1) % 7
	// 2012년 12월을 기준으로 하면 2013년1월은 2012년13월로 생각해주어야 한다.
	if (month < 3) // 1월, 2월이면
	{
		month += 12;
		year--;
	}
	int ye = year / 100; // 년을 100으로 나눈 값이 앞 2자리
	int ar = year % 100; // 년을 100으로 나눈 나머지가 끝 2자리
	return ((21 * ye / 4) + (5 * ar / 4) + (26 * (month + 1) / 10) + day - 1) % 7;
}

/*

	연월일만으로 요일을 계산하는 제라(Zeller)의 공식이 있다.

	서기 a (천)백 b (십)년 c월 d일의 요일을 알아보자.
	(단, 1월과 2월은 전년의 13월과 14월로 생각한다.)

	1. 먼저, 

	w=[21a/4]+[5b/4]+[26(c+1)/10]+d-1 

	을 계산한다.
	 (여기서 [x]는 가우스의 기호로써 x 이하의 정수 가운데 최대인 정수를 말한다.)

	2. 다음에 w를 7로 나눈 나머지를 구하고, 그 나머지가 0, 1, 2, 3, 4, 5,6에 따라서
	요일을 일, 월, 화, 수, 목, 금, 토 로 한다. 
	제라의 공식은 1887년 제라가 처음 만들었다.
	이전에 가우스도 요일의 계산공식을 만들었으나 하나의 공식으로써 표현한 것은 아니고, 표를 이용하는 것이었다.
	현재의 서기는 1582년 10월 15일 이후 사용되고 있는 그레고리력으로써 이 공식도 그 이후에만 적용된다. 그레고리력에 의하면 '서기 연수가 4로 나누어떨어지는 해를 윤년으로 하고, 100으로 나누어 떨어지나 400으로는 나누어 떨어지지 않는 해는 윤년으로 하지 않는다.'로 되어 있다. 

	그러면 2000년 1월 1일은 무슨 요일일까? 

	제라의 공식을 이용하려면 2000년 1월 1일은 1999년 13월 1일로 생각해야 한다. 

	a=19, b=99, c=13, d=1 이므로 

	w=[21x19 / 4]+[5x99 / 4]+[26(13+1) / 10]+1-1 

	=[399/4]+[495/4]+[364/10] 

	=[99.75]+[123.75]+[36.4] 

	=99+123+36 

	=258 

	따라서, 258을 7로 나누면 나머지가 6 이므로 토요일이다. 
*/