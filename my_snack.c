#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ESC 27

#define SNACK_COLOR 15
#define FOOD_COLOR 10
#define BG_COLOR 0
#define WALL_COLOR 55
#define TEXT_COLOR 10

#define TRUE 1
#define FALSE 0

#define FINAL_SNACK_SPEED 100 //蛇的最大速度

struct snack
{
	int x, y; //蛇的坐标
	struct snack * next;
};

int score = 0;
int food_position[2];//食物位置
int max_score = 0;

void gotoxy(int x, int y)    //设置输出坐标 ，以字节为单位
{
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(int b)         //设置颜色函数
{
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ;
    SetConsoleTextAttribute(hConsole,b) ;
}

//此函数显示墙壁
void show_wall()
{
    //傻逼的画墙方法（纯粹是觉得循环太麻烦，这个只要复制就好）
    int a[20][30] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    };
    set_color(WALL_COLOR);
    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j< 30; j++)
        {
            if (a[i][j] == 1)
            {
                set_color(WALL_COLOR);
                printf("■");
            }
            else
            {
                set_color(BG_COLOR);
                printf("  ");
            }
        }
        printf("\n");
    }
    set_color(TEXT_COLOR);
    gotoxy(62, 3);
    printf("Made By: 梦中谁人happy");
    gotoxy(62, 5);
    printf("请将输入法切换到英文状态再移动");
    set_color(TEXT_COLOR);
    gotoxy(62, 7);
	printf("使用'w','a','s','d'来移动");
	gotoxy(62, 9);
	printf("按下ESC键退出");
	gotoxy(62, 11);
	printf("当前分数：  %d", score);
	gotoxy(62, 13);
	printf("最高分数：  %d", max_score);

}

//产生食物
void make_food(struct snack * mySnack)
{
    srand(clock());
    int x = rand()%52+1; //因为我这里的最右边的墙的 x 坐标为 58
    int y = rand()%17+1; //            最下边的墙的 y 坐标为 19
    food_position[0] = x % 2?x+1:x;//确保x方向上的是偶数
    food_position[1] = y;
    struct snack * p = mySnack;
    while(p != NULL)
    {
        if (food_position[0] == p->x || food_position[1] == y)//如果和蛇有重合则重新生成食物
        {
            x = rand()%57+1;
            y = rand()%17+1;
            food_position[0] = x % 2?x+1:x;//确保x方向上的是偶数
            food_position[1] = y;
            struct snack * p = mySnack;
            p = mySnack;
        }
        p = p->next;
    }
    set_color(FOOD_COLOR);
    gotoxy(food_position[0], food_position[1]);
    printf("●");
}

//判断是否吃到食物，如果吃到返回TRUE
int isEat(struct snack * mySnack)
{
    int flag = FALSE;
    if (mySnack->x == food_position[0] && food_position[1] == mySnack->y)
    {
        flag = TRUE;
    }
    return flag;
}

//此函数初始化界面
void init(struct snack * mySnack)
{
	show_wall();
	make_food(mySnack);
	draw_Snack(mySnack);
}

//判断蛇是否撞墙
int hitWall(struct snack * mySnack)
{
    int flag = FALSE;
    if (mySnack->y<1 || mySnack->y>19 || mySnack->x<2 || mySnack->x>58)
    	flag = TRUE;
    return flag;
}

//判断蛇是否撞到自己
int hitSelf(struct snack * mySnack)
{
    int flag = FALSE;
    struct snack * p = mySnack->next;
    while(p != NULL)
    {
        if (p->x == mySnack->x && p->y == mySnack->y)
            flag = TRUE;
        p = p->next;
    }
    return flag;
}

//画出蛇
void draw_Snack(struct snack * mySnack)
{
	set_color(SNACK_COLOR);
	struct snack * p = mySnack;
	gotoxy(p->x, p->y);
	printf("■");
	p = p->next;
	if (p != NULL)
    {
        while (p != NULL)
        {
            gotoxy(p->x, p->y);
            printf("●");
            p = p->next;
        }

    }
}

int main(void)
{
	system("mode con cols=100 lines=25");//设置控制台窗口大小
	int direct = UP;
	int key = 0;
	int delay_time = 500;
	int choice;
	struct snack * mySnack = (struct snack *)malloc(sizeof(struct snack));
	mySnack->x = 30;
	mySnack->y = 10;
	mySnack->next = NULL;

	struct snack * p;
	struct snack * tail; //用于保存最后一个节点
	struct snack * perTail; //用于保存最后一个节点的前驱节点

	FILE * fp = fopen("record.txt", "a+");  //打开最高纪录文件
	if (fp == NULL)
	{
		printf("打开历史记录文件失败！");
		exit(-1);
	}
	char sc[8];

	if (fgets(sc, 8, fp) != NULL)
		max_score = atoi(sc);

	init(mySnack);
	while (1)
	{
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			case 'w':
			case 'W':
				if (direct != DOWN)
				{
					direct = UP;
				}
				break;
			case 's':
			case 'S':
				if (direct != UP)
				{
					direct = DOWN;
				}
				break;
			case 'a':
			case 'A':
				if (direct != RIGHT)
				{
					direct = LEFT;
				}
				break;
			case 'd':
			case 'D':
				if (direct != LEFT)
				{
					direct = RIGHT;
				}
				break;
			case ESC:
				choice = MessageBox(NULL,TEXT("您要退出吗？"),TEXT("警告"),MB_ICONINFORMATION|MB_YESNO);
				switch (choice){
				case IDYES:
					if (score > max_score)
					{
						fclose(fp);
						fp = fopen("record.txt", "w");
						if(fp == NULL)
						{
							printf("打开记录文件失败！");
							exit(-1);
						}
						fprintf(fp, "%d", score);
						fclose(fp);
					}
						exit(0);
						break;
				case IDNO:
						break;
				}
			}
		}

        p = (struct snack *)malloc(sizeof(struct snack));  //生成一个新的节点用来作为蛇新的头部

		if (direct == UP)
        {
            p->y = (mySnack->y)-1;
            p->x = mySnack->x;
        }
		else if(direct == DOWN)
        {
            p->y = mySnack->y+1;
            p->x = mySnack->x;
        }
		else if(direct == LEFT)
        {
            p->x = mySnack->x-2;
            p->y = mySnack->y;
        }
		else
        {
            p->x = mySnack->x +2;
            p->y = mySnack->y;
        }
        p->next = mySnack;
        mySnack = p;

        if (isEat(mySnack)) //如果吃到了食物就重新生成新的食物并且不去掉蛇尾节点
        {
        	score++;
        	if (delay_time > FINAL_SNACK_SPEED)
        		delay_time -= 50;
        	set_color(TEXT_COLOR);
        	gotoxy(62, 9);
			printf("当前分数：  %d", score);
            make_food(mySnack); //吃到食物之后要生成新的食物
        }
        else  //如果没吃到食物就把链表中的尾结点去掉，并且原来画尾结点的位置用背景色填充
        {
            tail = mySnack;
            perTail = NULL;
            while (tail->next != NULL)
            {
                perTail = tail;
                tail = tail->next;
            }
            set_color(BG_COLOR);
            gotoxy(tail->x, tail->y);
            printf("■");
            free(tail);
            perTail->next = NULL; //将尾结点的指针域指向NULL
        }

		if (hitWall(mySnack) || hitSelf(mySnack))
		{
			//游戏结束
			if (score > max_score)
			{
				fclose(fp);
				fp = fopen("record.txt", "w");
				if(fp == NULL)
				{
					printf("打开记录文件失败！");
					exit(-1);
				}
				fprintf(fp, "%d", score);
				fclose(fp);
			}
			MessageBox(NULL,TEXT("oo 您挂了，请重来吧！"),TEXT("不好意思"),MB_OK);
			exit(0);
		}
		draw_Snack(mySnack);
		Sleep(delay_time);
	}

	return 0;
}
