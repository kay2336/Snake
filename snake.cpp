#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>

// ��������
typedef struct pointXY
{
	int x;
	int	y;
}MYPOINT;

// �ߵ�����
struct snake
{
	int num;		 // �ߵĽ���
	MYPOINT xy[100]; // ����೤100��
	char postion;	 // ����
}snake;

// ʳ�������
struct food
{
	MYPOINT fdxy;	 // ʳ�������
	int eatgrade;	 // ����ʳ���ж��ٷ�
	int flag;		 // ʳ���Ƿ����
}food;

// ������
HWND hwnd = NULL;

// ö�ٷ���С���̣�����ֵ��
enum movPostion { right=77, left=75, down=80, up=72 };

/***********************************************
*			��ʼ���ߣ�     initSnake
*			���ߣ�	       drawSnake
*			�ƶ��ߣ�       moveSnake
*			�������ƣ�     keyDown
*           ��ʼ��ʳ�   initFood
*			��ʳ�	   drawFood
*			��ʳ�	   eatFood
*			��ײǽײ�Լ��� snakeDie
*			��ͣ��		   pauseMoment
************************************************/
void initSnake();
void drawSnake();
void moveSnake();
void keyDown();
void initFood();
void drawFood();
void eatFood();
int snakeDie();
void showGrade();
void pauseMoment();

// ������
int main()
{ 
	srand((unsigned int)time(NULL));
	hwnd = initgraph(640, 400);
	setbkcolor(WHITE);
	cleardevice();
	initSnake();
	drawSnake();

	while (1)
	{
		cleardevice();

		showGrade();
		
		// ����eat��draw��˳��ᵼ��ÿ�γ�һ��ʳ����ϽǾ���һ��ʳ�� ?
		drawFood();
		drawSnake();
		if (snakeDie() == 1)
			break;
		if (food.flag == 0)
			initFood();
		eatFood();
		moveSnake();

		// ֻ�����а������µ�ʱ��Ž��հ�������Ҫһֱ��
		keyDown();
		Sleep(100);
	}
	
	getchar();   //��ֹ������
	closegraph();
	return 0;
}

// ��ʼ��λ�ã�������ǰ������
void initSnake()
{
	snake.xy[2].x = 0, snake.xy[2].y = 0;
	snake.xy[1].x = 10, snake.xy[1].y = 0;
	snake.xy[0].x = 20, snake.xy[0].y = 0;

	snake.num = 3;

	snake.postion = right;
}

// �����ߵ���״
void drawSnake()
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(GREEN);
		//setfillcolor(RGB(rand()%255, rand() % 255, rand() % 255));
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x+10, snake.xy[i].y+10);
	}
}

// ���߶�����
void moveSnake()
{
	// ����һ�ڶ���ǰ��һ�ڵ�����
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	// ���е�һ��
	switch (snake.postion)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	default:
		break;
	}
}

// �������ڣ����������е㷴���ࣩ
void keyDown()
{
	// �������������󣬿����ǲ�֧����
	// error C4996 : 'getch' : The POSIX name for this item is deprecated.Instead, 
	// use the ISO C and C++ conformant name : _getch.See online help for details.
	int userKey;
	while (_kbhit())
	{
		pauseMoment();
		userKey = _getch();
		switch (userKey)
		{
		case right:
			if (snake.postion != right)
			{
				snake.postion = right;
			}
			break;
		case left:
			if (snake.postion != left)
			{
				snake.postion = left;
			}
			break;
		case down:
			if (snake.postion != down)
			{
				snake.postion = down;
			}
			break;
		case up:
			if (snake.postion != up)
			{
				snake.postion = up;
			}
			break;
		default:
			break;
		}

	}
}

// �������ʳ��
void initFood()
{
	food.fdxy.x = rand() % 64 * 10;
	food.fdxy.y = rand() % 40 * 10;
	food.flag = 1;

	// ���ʳ����������, �����²���
	for (int i = 0; i < snake.num; i++)
	{
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y)
		{
			food.fdxy.x = rand() % 64 * 10;
			food.fdxy.y = rand() % 40 * 10;
			i = 0;
		}
	}
}

// ��ʳ��
void drawFood()
{
	setfillcolor(GREEN);
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x+10, food.fdxy.y+10);
}

// ��ʳ��
void eatFood()
{
	if (food.fdxy.x == snake.xy[0].x && food.fdxy.y == snake.xy[0].y)
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}

// ��ײǽ����ײ�Լ�
// 0: ����
// 1: ����
int snakeDie()
{
	// ײǽ
	if (snake.xy[0].x > 640 || snake.xy[0].x < 0
		|| snake.xy[0].y > 480 || snake.xy[0].x < 0)
	{
		MessageBox(hwnd, _T("����~����"), _T("С��"), MB_OK);
		return 1;
	}

	// ײ�Լ�
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x
			&& snake.xy[0].y == snake.xy[i].y)
		{
			MessageBox(hwnd, _T("����~����"), _T("���"), MB_OK);
			return 1;
		}
	}
	return 0;
}

// ��ʾ����
void showGrade()
{
	// https://blog.csdn.net/weixin_72549244/article/details/130038932
	TCHAR grade[100];
	_stprintf_s(grade, _T("%d"), food.eatgrade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	outtextxy(570, 20, _T("������"));
	outtextxy(610, 20, grade);

}

// ��ͣ
void pauseMoment()
{
	if (_getch() == 32)
	{
		while (_getch() != 32);
	}
}










