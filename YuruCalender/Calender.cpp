/*
	�޷¸����
	1. Ŀ���� ��ġ�� �˷��ִ� �Լ�
	2. ������ �ٲ��ִ� �Լ�(�Ƹ� 16�ܰ�)
	3. �� �� ���� ����� �ǰ� ��ġ�� �ٲ� �� �ִ� �÷� �޷�
		��, ������� �Ķ���, �Ͽ����� ������, �ڱ� ������ �ݻ����� �ϵ�, ��ο� �ݻ��� ���� �ݻ��� ������ ����ؼ� ��¦�̵��� �Ѵ�.
		��Ÿ ����� ����
	4. time.h ����� clock�Լ��� ����� ��. sleep() ����.
	
	clock�Լ�
	-VS���� 1Ŭ�� 1�и�������
	sclock = clock()
	if(clock() - sclock)


	�迭 ����
	int a[10];

	**���ڻ��� ������ �ٲ��ִ� �Լ�
	//color ��� ����
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

	void textcolor(int foreground, int background) //foreground : ���ڻ�, backgroung : ����
	{
		int color = foreground + background * 16;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	**Ŀ���� ��ġ�� �ٲ��ִ� �Լ�
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
	������ �غ���.

	��� ������ ���ΰ�?
	- �켱������ ������ ���� ��ó�� ������� �Ķ��� ��Ÿ ���ϰ� �Ͽ����� ���������� �Ѵ�.
	- ���϶��� �ݻ����� �ϸ�, ��Ÿ �ٸ� ���� �߰��� ������.
		�׷��ٸ� � ������ ���� ���ΰ�?
			1. ������ ���� �� ����ȸ�� ������ �ִ´�.
			2. �׿� �������� �߰�
	- WASD�Է��� kbhit() ���� �Է¹޾Ƽ� �� �������� �Ѿ�� �Ѵ�.
	- �޷��� Ű�� ���糯¥ �������� �޷� ���, ���糯¥�� �ʷϻ����� ǥ���غ���.
	- ��Ÿ �ΰ����� ���� �ϴ� �������� �ϰ��� ��������.

	- ���� ����
	- �޷¸���� �˰��� ����
	- ������ ����!


	kbhit()

	windwos.h ��Ŭ��� �ؾ���

	Ű ��ư�� �Է��� �����ϴ� �Լ�

	if(kbhit())
	{
	key = getch();
	}

	�� �������� ���� �ȴ�.


*/
#include "Calender.h"

int main()
{
	/*
		�� �� �� �켱����
	*/

	sndPlaySound("../op.wav", SND_ASYNC);//������ ����������

	int year = 0, month = 0;
	int num1 = 0, num2 = 0;//��¦�Ÿ��� ���Ŵ�
	int n = 1;

	struct tm *nowtime;
	time_t nowtimer;

	nowtimer = time(NULL);    // ���� �ð��� �� ������ ���
	nowtime = localtime(&nowtimer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	year = 1900 + nowtime->tm_year; // tm_year�� 1900�� ����
	month = nowtime->tm_mon + 1; // tm_mon�� 0���� ����

	COORD ATL;//��Ʋ���� ��ǥ!
	ATL.X = 0;
	ATL.Y = 0;

	Calender(year, month, nowtime, &ATL);

	//���� ���� ǥ�ø� �غ��ô�.

	while (true)
	{

		if (month==5) //��Ʋ���� ����. 5���̴ϱ� month == 5
		{
			int colors[] = {BROWN, YELLOW};//��¦ ��¦��
			if (ATL.X != 0 || ATL.Y!= 0)//ATL.X�� 0�� �ƴϰų� Ȥ�� ATL.Y�� 0�� �ƴϰų� Ȥ�� �Ѵ� 0�� �ƴϰų�
			{
				if (num1 % 10 == 0)//���� ��¦��¦��
				{
					gotoxy(ATL.X, ATL.Y);
					textcolor(BLACK, colors[num2 % 2]);
					printf("%d", 26);//�� ����
					num2++;

					if (num2 == 2)
					{
						num2 = 0;
						num1 = 0;
					}
				}
				wait(10);//10�и������� ���� ��ٸ���
				num1++;

			}
		}

		else if (month == 1) //������ ����, ����2�� �����ó�� ������� �ص帮�ڽ��ϴ� ����
		{
			int colors[] = { WHITE, LIGHTGRAY, DARKGRAY, BLACK};//�������� ������پƾƳ��� 
			char str[7] = {"��ī��"};

			if (ATL.X != 0 || ATL.Y!= 0)
			{
				if (num1 % 50 == 0)//��ī��~
				{
					gotoxy(ATL.X, ATL.Y);
					textcolor(BLACK, colors[num2 % 4]);
					printf("%3c%c", str[2*n-2], str[2*n-1]);	

					sndPlaySound("../Akkaring.wav", SND_ASYNC);//��ī�� ��� ���
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

		//Ű�Է� ����

		/*
			Ű ��ư�� �Է��� �����ϴ� �Լ�

			if(kbhit())
			{
			key = getch();
			}

			�� �������� ���� �ȴ�.
		*/

		if (kbhit())
		{
			int key = getch();//��� W A S D�� ���ڷ� ���������ϱ�

			switch (key)
			{
			case 'A':
			case 'a':
				if (month != 1)//1���� �ƴϸ� �� ���� ���ҽ�Ű�� �Ǳ߳�.
					month--;
				else
				if (year > 0)//0����� ������ ������ �𸣰����� �ϴ�..0�̻��� ������ �ϳ��� �����Ѵ�.
				{
					year--;
					month = 12;
				}
				break;
			case 'D':
			case 'd':
				if (month != 12)//12���� �ƴϸ� ������ ��Ű�� ��
					month++;
				else
				{
					year++;//12���̸� ������ ������Ű�� ���� 1���� �ٲ��ָ����
					month = 1;
				}
				break;
			case 'W':
			case 'w':
				year++;//�� �� ������ �������ָ� �ȴ�
				break;
			case 'S':
			case 's':
				if (year > 0) 
					year--;//0�� �̻��̸� �׳� ������ ������ �ȴ�. 0�����ϱ��� ������ ������ �ʹٸ�
				break;
			}

			Calender(year, month, nowtime, &ATL);
		}
		
	}

	getchar();

	return 0;
}

//���� �޷¿� ��¥�� ����غ�������
void Calender(int year, int month, struct tm *nowtime, COORD *ATL)//�� �� ����ð� ��Ʋ������ǥ��
{

	/*
		�޷� �� ���� �ٲ𶧸��� �ܼ�â�� ��� ������� �ϹǷ�
		system("cls");�� ����ؾߵȴ�. ������ �̰� ����ϸ� ���� printf()�� ǥ����
		�� �� �޷� ������� ���� ������Ƿ� ����� �Űܼ� ����ϰڴ�.
	*/

	//�⺻Ʋ
	

	char Week_Name[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };//��¥
	int a = 0, b = 0;//�޷��� ��ķ� ǥ��������.. ��� ���� �Ǿ��� ģ����
	int day = 0, now_year = 0, now_month = 0, now_day = 0, cnt = 0;
	int startofworld = JeraWeek(year, month, 1);
	int endofworld = YNday(year, month) - 1;

	now_year = 1900 + nowtime->tm_year;//1900�� �������� �϶�µ� �ֱ׷����� �𸣰ڴ�
	now_month = nowtime->tm_mon + 1;//0���� ����
	now_day = nowtime->tm_mday;

	textcolor(LIGHTGRAY, BLACK); // ȭ�� ��ﶧ ����
	system("cls"); // ȭ���� �����������

	printf("     << %4d��%2d�� >>\n", year, month);

	//���� ǥ�� �� ���� ����
	textcolor(LIGHTRED, DEF_BACKCOLOR);//foreground : ���ڻ�, backgroung : ����
	printf(" %s", Week_Name[0]);

	textcolor(DEF_FORECOLOR, DEF_BACKCOLOR);
	printf(" %s %s %s %s %s", Week_Name[1], Week_Name[2], Week_Name[3], Week_Name[4], Week_Name[5]);

	textcolor(LIGHTBLUE, DEF_BACKCOLOR);
	printf(" %s\n", Week_Name[6]);

	//���� ��ġ����


	for (a = 0; a<6; a++) // ����������
	{
		for (b = 0; b<7; b++) // ��������������
		{
			cnt = (a * 7) + b + 1;
			if (b == SUNDAY) // ��
				textcolor(RED, DEF_BACKCOLOR); // �K��ũ����
			else if (b == SATURDAY) // �����
				textcolor(BLUE, DEF_BACKCOLOR); // �K��ũ���
			else
				textcolor(DARKGRAY, DEF_BACKCOLOR); // �K��ũ��
			//���м�
			if (a == SUNDAY && b < startofworld) // ù�ֿ��� b�� 1���� �������� �������� ����غ���.
				day = YNday(year, month != 1 ? month - 1 : 12) - (startofworld - b - 1);
			else if (a >= 4 && (cnt - startofworld - 1) > endofworld) // �������ֿ��� b�� ������������ ũ�� ������ ù°�ָ� ���
				day = (cnt - startofworld - 1) - endofworld;

			else
			{
				if (b == SUNDAY) // ��
					textcolor(LIGHTRED, DEF_BACKCOLOR); // ��������������
				else if (b == SATURDAY) // ��
					textcolor(LIGHTBLUE, DEF_BACKCOLOR); // �����Ķ�������
				else
					textcolor(LIGHTGRAY, DEF_BACKCOLOR); // ����������
				day = cnt - startofworld;
				if (now_year == year && now_month == month && now_day == day)
					textcolor(BLACK, WHITE); // ���ó�¥�� ���� ǥ�ø� ������ϴϱ� �Ͼ������ �غ���
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
						textcolor(LIGHTRED, DEF_BACKCOLOR); // ������ ������������
				}

			}
			printf("%4d", day);
		}
		printf("\n");

	}
	// �ٛ����ϱ� ���� �ٲ������ �ȱ׷�?
	textcolor(DEF_FORECOLOR, DEF_BACKCOLOR);
	printf("�޷��̵� ����\nW,S �����̵�\nA,D ���̵�");

}





