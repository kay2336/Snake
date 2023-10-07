#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>

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
}food;

// 主窗口
HWND hwnd = NULL;

// 枚举方向（小键盘，键码值）
enum movPostion { right=77, left=75, down=80, up=72 };

/***********************************************
*			初始化蛇：     initSnake
*			画蛇：	       drawSnake
*			移动蛇：       moveSnake
*			按键控制：     keyDown
*           初始化食物：   initFood
*			画食物：	   drawFood
*			吃食物：	   eatFood
*			蛇撞墙撞自己： snakeDie
*			暂停：		   pauseMoment
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

// 主函数
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
		
		// 调换eat和draw的顺序会导致每次吃一个食物，左上角就闪一下食物 ?
		drawFood();
		drawSnake();
		if (snakeDie() == 1)
			break;
		if (food.flag == 0)
			initFood();
		eatFood();
		moveSnake();

		// 只有在有按键按下的时候才接收按键，蛇要一直动
		keyDown();
		Sleep(100);
	}
	
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
		setlinecolor(BLACK);
		setfillcolor(GREEN);
		//setfillcolor(RGB(rand()%255, rand() % 255, rand() % 255));
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

// 调整窗口（两个窗口有点反人类）
void keyDown()
{
	// 编译器的问题捏，可能是不支持了
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

// 随机生成食物
void initFood()
{
	food.fdxy.x = rand() % 64 * 10;
	food.fdxy.y = rand() % 40 * 10;
	food.flag = 1;

	// 如果食物在蛇身上, 则重新产生
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

// 画食物
void drawFood()
{
	setfillcolor(GREEN);
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x+10, food.fdxy.y+10);
}

// 吃食物
void eatFood()
{
	if (food.fdxy.x == snake.xy[0].x && food.fdxy.y == snake.xy[0].y)
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}

// 蛇撞墙或者撞自己
// 0: 继续
// 1: 输了
int snakeDie()
{
	// 撞墙
	if (snake.xy[0].x > 640 || snake.xy[0].x < 0
		|| snake.xy[0].y > 480 || snake.xy[0].x < 0)
	{
		MessageBox(hwnd, _T("杂鱼~杂鱼"), _T("小鬼"), MB_OK);
		return 1;
	}

	// 撞自己
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x
			&& snake.xy[0].y == snake.xy[i].y)
		{
			MessageBox(hwnd, _T("杂鱼~杂鱼"), _T("大鬼"), MB_OK);
			return 1;
		}
	}
	return 0;
}

// 显示分数
void showGrade()
{
	// https://blog.csdn.net/weixin_72549244/article/details/130038932
	TCHAR grade[100];
	_stprintf_s(grade, _T("%d"), food.eatgrade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	outtextxy(570, 20, _T("分数："));
	outtextxy(610, 20, grade);

}

// 暂停
void pauseMoment()
{
	if (_getch() == 32)
	{
		while (_getch() != 32);
	}
}










