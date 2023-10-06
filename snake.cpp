#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

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
};

// ������
HWND hwnd = NULL;

// ö�ٷ���С���̣�����ֵ��
enum movPostion { right=77, left=75, down=80, up=72 };


/***********************************************
*			��ʼ���ߣ�  initSnake
*			���ߣ�	    drawSnake
*			�ƶ��ߣ�    moveSnake
*			�������ƣ�  keyDown
*           ��ʼ��ʳ�initFood
*			��ʳ�	drawFood
*			��ʳ�	eatFood
*			
************************************************/
void initSnake();
void drawSnake();
void moveSnake();
void keyDown();
void initFood();
void drawFood();
void eatFood();

int main()
{ 
	hwnd = initgraph(640, 400);
	setbkcolor(WHITE);
	cleardevice();
	initSnake();
	drawSnake();

	while (1)
	{
		cleardevice();
		drawSnake();
		moveSnake();

		//ֻ�����а������µ�ʱ��Ž��հ�������Ҫһֱ��
		keyDown();

		Sleep(100);
	}

	//while (1)
	//{
	//	printf("\n");
	//	int ch = _getch();
	//	printf("%d\n", ch);
	//	ch = _getch();
	//	printf("%d\n", ch);
	//}
	
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
		// ��ɫ�߿����
		setlinecolor(BLACK);
		// �������ɫ����
		setfillcolor(GREEN);
		// ������
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
	printf("move: %d\n", snake.postion);
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

// ������ȡ��������
void keyDown()
{
	// �������������󣬿����ǲ�֧����
	// error C4996 : 'getch' : The POSIX name for this item is deprecated.Instead, 
	// use the ISO C and C++ conformant name : _getch.See online help for details.
	int userKey;
	while (_kbhit())
	{
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


















