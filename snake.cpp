#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

// 坐标属性
typedef struct pointXY
{
	int x;
	int	y;
}MYPOINT;

// 蛇的属性
struct snake
{
	int num;		 // 蛇的节数
	MYPOINT xy[100]; // 蛇最多长100节
	char postion;	 // 方向
}snake;

// 食物的属性
struct food
{
	MYPOINT fdxy;	 // 食物的坐标
	int eatgrade;	 // 吃了食物有多少分
	int flag;		 // 食物是否存在
};

// 主窗口
HWND hwnd = NULL;

// 枚举方向（小键盘，键码值）
enum movPostion { right=77, left=75, down=80, up=72 };


/***********************************************
*			初始化蛇：  initSnake
*			画蛇：	    drawSnake
*			移动蛇：    moveSnake
*			按键控制：  keyDown
*           初始化食物：initFood
*			画食物：	drawFood
*			吃食物：	eatFood
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

		//只有在有按键按下的时候才接收按键，蛇要一直动
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
	
	getchar();   //防止闪屏捏
	closegraph();
	return 0;
}

// 初始化位置，节数，前进方向
void initSnake()
{
	snake.xy[2].x = 0, snake.xy[2].y = 0;
	snake.xy[1].x = 10, snake.xy[1].y = 0;
	snake.xy[0].x = 20, snake.xy[0].y = 0;

	snake.num = 3;

	snake.postion = right;
}

// 画出蛇的形状
void drawSnake()
{
	for (int i = 0; i < snake.num; i++)
	{
		// 黑色边框矩形
		setlinecolor(BLACK);
		// 内填充绿色矩形
		setfillcolor(GREEN);
		// 画矩形
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x+10, snake.xy[i].y+10);
	}
}

// 让蛇动起来
void moveSnake()
{
	// 后面一节都是前面一节的坐标
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	printf("move: %d\n", snake.postion);
	// 特判第一节
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

// 按键读取出大问题
void keyDown()
{
	// 编译器的问题捏，可能是不支持了
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


















