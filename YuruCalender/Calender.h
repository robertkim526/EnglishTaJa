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

void gotoxy(int, int); //Ŀ�� �ű�� �Լ���
void textcolor(int foreground, int background);
void wait(clock_t);

int YunNyun(int); //���� ��� �Լ�, 29��, 28�Ϸ� ������.
int YNday(int, int);
int JeraWeek(int, int, int);



//
void gotoxy(int x, int y) //ù��° ���ڴ� ����, �ι�° ���ڴ� ���� 
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int foreground, int background) //foreground : ���ڻ�, backgroung : ����
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
//�޷°��
int YunNyun(int YNyear)
{
	//������ ���ߵ��� ���� �����
	
	if (YNyear % 4 == 0 && (YNyear % 100 != 0 || YNyear % 400 == 0))
		return 29;
	else
		return 28;
}

int YNday(int year, int month)
{
	int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//�� ���� ������ �ϼ�

	if (month == 2 && YunNyun(year))
	{
		return 29;
	}
	else
		return month_day[month];
}

bool Holiday()//�����̸� �� �ƴϸ� ������ ����
{
	int i;
	int Holidays[][] = {
		{ 1, 1 }, { 3, 1 }, { 5, 5 }, { 6, 6 }, { 8, 15 }, { 10, 3 }, { 10, 9 }, { 12, 25 }, { 1, 6 }, { 5, 26 }, {}
	}
}

int JeraWeek(int year, int month, int day) //������ ����
{
	// ������ ���� ((21 * ye / 4) + (5 * ar / 4) + (26 * (month + 1) / 10) + day - 1) % 7
	// 2012�� 12���� �������� �ϸ� 2013��1���� 2012��13���� �������־�� �Ѵ�.
	if (month < 3) // 1��, 2���̸�
	{
		month += 12;
		year--;
	}
	int ye = year / 100; // ���� 100���� ���� ���� �� 2�ڸ�
	int ar = year % 100; // ���� 100���� ���� �������� �� 2�ڸ�
	return ((21 * ye / 4) + (5 * ar / 4) + (26 * (month + 1) / 10) + day - 1) % 7;
}

/*

	�����ϸ����� ������ ����ϴ� ����(Zeller)�� ������ �ִ�.

	���� a (õ)�� b (��)�� c�� d���� ������ �˾ƺ���.
	(��, 1���� 2���� ������ 13���� 14���� �����Ѵ�.)

	1. ����, 

	w=[21a/4]+[5b/4]+[26(c+1)/10]+d-1 

	�� ����Ѵ�.
	 (���⼭ [x]�� ���콺�� ��ȣ�ν� x ������ ���� ��� �ִ��� ������ ���Ѵ�.)

	2. ������ w�� 7�� ���� �������� ���ϰ�, �� �������� 0, 1, 2, 3, 4, 5,6�� ����
	������ ��, ��, ȭ, ��, ��, ��, �� �� �Ѵ�. 
	������ ������ 1887�� ���� ó�� �������.
	������ ���콺�� ������ �������� ��������� �ϳ��� �������ν� ǥ���� ���� �ƴϰ�, ǥ�� �̿��ϴ� ���̾���.
	������ ����� 1582�� 10�� 15�� ���� ���ǰ� �ִ� �׷��������ν� �� ���ĵ� �� ���Ŀ��� ����ȴ�. �׷����¿� ���ϸ� '���� ������ 4�� ����������� �ظ� �������� �ϰ�, 100���� ������ �������� 400���δ� ������ �������� �ʴ� �ش� �������� ���� �ʴ´�.'�� �Ǿ� �ִ�. 

	�׷��� 2000�� 1�� 1���� ���� �����ϱ�? 

	������ ������ �̿��Ϸ��� 2000�� 1�� 1���� 1999�� 13�� 1�Ϸ� �����ؾ� �Ѵ�. 

	a=19, b=99, c=13, d=1 �̹Ƿ� 

	w=[21x19 / 4]+[5x99 / 4]+[26(13+1) / 10]+1-1 

	=[399/4]+[495/4]+[364/10] 

	=[99.75]+[123.75]+[36.4] 

	=99+123+36 

	=258 

	����, 258�� 7�� ������ �������� 6 �̹Ƿ� ������̴�. 
*/