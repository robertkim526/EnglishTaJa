/*
	달력만들기
	1. 커서의 위치를 알려주는 함수
	2. 색상을 바꿔주는 함수(아마 16단계)
	3. 연 월 일이 출력이 되고 위치도 바꿀 수 있는 컬러 달력
		단, 토요일은 파랑색, 일요일은 빨간색, 자기 생일은 금색으로 하되, 어두운 금색과 밝은 금색을 번갈아 사용해서 반짝이도록 한다.
		기타 기능은 자유
	4. time.h 헤더와 clock함수를 사용할 것. sleep() 금지.
	
	clock함수
	-VS기준 1클락 1밀리세컨드
	sclock = clock()
	if(clock() - sclock)


	배열 사용법
	int a[10];

	**글자색과 배경색을 바꿔주는 함수
	//color 상수 지정
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

	#include<stdio.h>

	void textcolor(int foreground, int background) //foreground : 글자색, backgroung : 배경색
	{
		int color = foreground + background * 16;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	**커서의 위치를 바꿔주는 함수
	#include<windows.h>

	void gotoxy(int x, int y)
	{
		void gotoxy(int x, int y)
		{
			COORD Pos = {x-1, y-1};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		}
	}
*/

/*
	구상을 해보자.

	어떻게 구현할 것인가?
	- 우선적으로 명세서에 나온 것처럼 토요일은 파랑색 기타 휴일과 일요일은 빨강색으로 한다.
	- 생일또한 금색으로 하며, 기타 다른 생일 추가가 가능함.
		그렇다면 어떤 생일을 넣을 것인가?
			1. 지수형 생일 및 차기회장 생일을 넣는다.
			2. 그외 여러가지 추가
	- WASD입력을 kbhit() 으로 입력받아서 연 월단위로 넘어가게 한다.
	- 달력을 키면 현재날짜 기준으로 달력 출력, 현재날짜를 초록색으로 표현해보자.
	- 기타 부가적인 것은 일단 구현부터 하고나서 생각하자.

	- 윤년 구현
	- 달력만들기 알고리즘 착용
	- 제라의 공식!


	kbhit()

	windwos.h 인클루드 해야함

	키 버튼의 입력을 감지하는 함수

	if(kbhit())
	{
	key = getch();
	}

	의 형식으로 쓰면 된다.


*/
#include "Calender.h"

int main()
{
	/*
		연 월 일 우선구현
	*/

	sndPlaySound("../op.wav", SND_ASYNC);//에길의 유루유리잼

	int year = 0, month = 0;
	int num1 = 0, num2 = 0;//반짝거릴때 쓸거당
	int n = 1;

	struct tm *nowtime;
	time_t nowtimer;

	nowtimer = time(NULL);    // 현재 시각을 초 단위로 얻기
	nowtime = localtime(&nowtimer); // 초 단위의 시간을 분리하여 구조체에 넣기

	year = 1900 + nowtime->tm_year; // tm_year은 1900년 기준
	month = nowtime->tm_mon + 1; // tm_mon은 0부터 시작

	COORD ATL;//아틀리에 좌표!
	ATL.X = 0;
	ATL.Y = 0;

	Calender(year, month, nowtime, &ATL);

	//요일 색상 표시를 해봅시다.

	while (true)
	{

		if (month==5) //아틀리에 생일. 5월이니까 month == 5
		{
			int colors[] = {BROWN, YELLOW};//반짝 반짝잼
			if (ATL.X != 0 || ATL.Y!= 0)//ATL.X가 0이 아니거나 혹은 ATL.Y가 0이 아니거나 혹은 둘다 0이 아니거나
			{
				if (num1 % 10 == 0)//빨리 반짝반짝잼
				{
					gotoxy(ATL.X, ATL.Y);
					textcolor(BLACK, colors[num2 % 2]);
					printf("%d", 26);//내 생일
					num2++;

					if (num2 == 2)
					{
						num2 = 0;
						num1 = 0;
					}
				}
				wait(10);//10밀리세컨드 동안 기다리쇼
				num1++;

			}
		}

		else if (month == 1) //짓수형 생일, 지수2가 만든것처럼 사라지게 해드리겠습니다 껄껄
		{
			int colors[] = { WHITE, LIGHTGRAY, DARKGRAY, BLACK};//저엄저엄 사라진다아아낄낄 
			char str[7] = {"앗카링"};

			if (ATL.X != 0 || ATL.Y!= 0)
			{
				if (num1 % 50 == 0)//앗카링~
				{
					gotoxy(ATL.X, ATL.Y);
					textcolor(BLACK, colors[num2 % 4]);
					printf("%3c%c", str[2*n-2], str[2*n-1]);	

					sndPlaySound("../Akkaring.wav", SND_ASYNC);//앗카링 브금 재생
					num2++;
					n++;

					if (num2 == 4)
					{
						num1 = 0;
						num2 = 0;
						ATL.X = 0;
						ATL.Y = 0;
						n = 1;
					}
				}

				wait(10);
				num1++;
			}

		}

		//키입력 받자

		/*
			키 버튼의 입력을 감지하는 함수

			if(kbhit())
			{
			key = getch();
			}

			의 형식으로 쓰면 된다.
		*/

		if (kbhit())
		{
			int key = getch();//헤더 W A S D를 숫자로 선언했으니까

			switch (key)
			{
			case 'A':
			case 'a':
				if (month != 1)//1월이 아니면 걍 월을 감소시키면 되긋네.
					month--;
				else
				if (year > 0)//0년까지 갈일이 있을진 모르겠지만 일단..0이상의 연도면 하나씩 감소한다.
				{
					year--;
					month = 12;
				}
				break;
			case 'D':
			case 'd':
				if (month != 12)//12월이 아니면 증가만 시키면 됨
					month++;
				else
				{
					year++;//12월이면 연도를 증가시키고 월을 1월로 바꿔주면되지
					month = 1;
				}
				break;
			case 'W':
			case 'w':
				year++;//얜 걍 연도만 증가해주면 된다
				break;
			case 'S':
			case 's':
				if (year > 0) 
					year--;//0년 이상이면 그냥 연도를 내리면 된다. 0년이하까지 갈일이 있을까 싶다만
				break;
			}

			Calender(year, month, nowtime, &ATL);
		}
		
	}

	getchar();

	return 0;
}

//이제 달력에 날짜를 출력해보으리자
void Calender(int year, int month, struct tm *nowtime, COORD *ATL)//연 월 현재시간 아틀리에좌표계
{

	/*
		달력 연 월이 바뀔때마다 콘솔창을 모두 지워줘야 하므로
		system("cls");를 사용해야된다. 하지만 이걸 사용하면 위에 printf()로 표현한
		연 월 달력 제목등이 같이 사라지므로 여기로 옮겨서 사용하겠다.
	*/

	//기본틀
	

	char Week_Name[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };//날짜
	int a = 0, b = 0;//달력을 행렬로 표시했을때.. 행과 열이 되어줄 친구들
	int day = 0, now_year = 0, now_month = 0, now_day = 0, cnt = 0;
	int startofworld = JeraWeek(year, month, 1);
	int endofworld = YNday(year, month) - 1;

	now_year = 1900 + nowtime->tm_year;//1900년 기준으로 하라는데 왜그런건진 모르겠다
	now_month = nowtime->tm_mon + 1;//0에서 시작
	now_day = nowtime->tm_mday;

	textcolor(LIGHTGRAY, BLACK); // 화면 비울때 색상
	system("cls"); // 화면을 날려버려어엇

	printf("     << %4d년%2d월 >>\n", year, month);

	//요일 표시 및 색상 결정
	textcolor(LIGHTRED, DEF_BACKCOLOR);//foreground : 글자색, backgroung : 배경색
	printf(" %s", Week_Name[0]);

	textcolor(DEF_FORECOLOR, DEF_BACKCOLOR);
	printf(" %s %s %s %s %s", Week_Name[1], Week_Name[2], Week_Name[3], Week_Name[4], Week_Name[5]);

	textcolor(LIGHTBLUE, DEF_BACKCOLOR);
	printf(" %s\n", Week_Name[6]);

	//요일 배치하자


	for (a = 0; a<6; a++) // 행행행행행
	{
		for (b = 0; b<7; b++) // 여여여여여여열
		{
			cnt = (a * 7) + b + 1;
			if (b == SUNDAY) // 일
				textcolor(RED, DEF_BACKCOLOR); // 딮다크레드
			else if (b == SATURDAY) // 토요일
				textcolor(BLUE, DEF_BACKCOLOR); // 딮다크블루
			else
				textcolor(DARKGRAY, DEF_BACKCOLOR); // 딮다크함
			//구분선
			if (a == SUNDAY && b < startofworld) // 첫주에서 b가 1보다 작을때는 지난달을 출력해보자.
				day = YNday(year, month != 1 ? month - 1 : 12) - (startofworld - b - 1);
			else if (a >= 4 && (cnt - startofworld - 1) > endofworld) // 마지막주에서 b가 마지막날보다 크면 다음달 첫째주를 출력
				day = (cnt - startofworld - 1) - endofworld;

			else
			{
				if (b == SUNDAY) // 일
					textcolor(LIGHTRED, DEF_BACKCOLOR); // 밝은빨간색으로
				else if (b == SATURDAY) // 토
					textcolor(LIGHTBLUE, DEF_BACKCOLOR); // 밝은파란색으로
				else
					textcolor(LIGHTGRAY, DEF_BACKCOLOR); // 밝은색으로
				day = cnt - startofworld;
				if (now_year == year && now_month == month && now_day == day)
					textcolor(BLACK, WHITE); // 오늘날짜는 따로 표시를 해줘야하니까 하얀색으로 해보자
				if (Holiday(month, day))
				{
\
					if (month == 5 && day == 26)
					{
						COORD tmp;
						tmp.Y = a + 3;
						tmp.X = b * 4 + 3;
						(*ATL) = tmp;
					}

					else if (month == 1 && day == 6)
					{
						COORD tmp;
						tmp.Y = a + 3;
						tmp.X = b * 4 + 1;
						(*ATL) = tmp;
					}
					else
						textcolor(LIGHTRED, DEF_BACKCOLOR); // 휴일을 빨강빨강으로
				}

			}
			printf("%4d", day);
		}
		printf("\n");

	}
	// 다썻으니까 색상도 바꿔줘야제 안그럼?
	textcolor(DEF_FORECOLOR, DEF_BACKCOLOR);
	printf("달력이동 설명\nW,S 연도이동\nA,D 월이동");

}





