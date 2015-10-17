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

#define FINAL_SNACK_SPEED 100 //�ߵ�����ٶ�

struct snack
{
	int x, y; //�ߵ�����
	struct snack * next;
};

int score = 0;
int food_position[2];//ʳ��λ��
int max_score = 0;

void gotoxy(int x, int y)    //����������� �����ֽ�Ϊ��λ
{
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(int b)         //������ɫ����
{
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ;
    SetConsoleTextAttribute(hConsole,b) ;
}

//�˺�����ʾǽ��
void show_wall()
{
    //ɵ�ƵĻ�ǽ�����������Ǿ���ѭ��̫�鷳�����ֻҪ���ƾͺã�
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
                printf("��");
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
    printf("Made By: ����˭��happy");
    gotoxy(62, 5);
    printf("�뽫���뷨�л���Ӣ��״̬���ƶ�");
    set_color(TEXT_COLOR);
    gotoxy(62, 7);
	printf("ʹ��'w','a','s','d'���ƶ�");
	gotoxy(62, 9);
	printf("����ESC���˳�");
	gotoxy(62, 11);
	printf("��ǰ������  %d", score);
	gotoxy(62, 13);
	printf("��߷�����  %d", max_score);

}

//����ʳ��
void make_food(struct snack * mySnack)
{
    srand(clock());
    int x = rand()%52+1; //��Ϊ����������ұߵ�ǽ�� x ����Ϊ 58
    int y = rand()%17+1; //            ���±ߵ�ǽ�� y ����Ϊ 19
    food_position[0] = x % 2?x+1:x;//ȷ��x�����ϵ���ż��
    food_position[1] = y;
    struct snack * p = mySnack;
    while(p != NULL)
    {
        if (food_position[0] == p->x || food_position[1] == y)//����������غ�����������ʳ��
        {
            x = rand()%57+1;
            y = rand()%17+1;
            food_position[0] = x % 2?x+1:x;//ȷ��x�����ϵ���ż��
            food_position[1] = y;
            struct snack * p = mySnack;
            p = mySnack;
        }
        p = p->next;
    }
    set_color(FOOD_COLOR);
    gotoxy(food_position[0], food_position[1]);
    printf("��");
}

//�ж��Ƿ�Ե�ʳ�����Ե�����TRUE
int isEat(struct snack * mySnack)
{
    int flag = FALSE;
    if (mySnack->x == food_position[0] && food_position[1] == mySnack->y)
    {
        flag = TRUE;
    }
    return flag;
}

//�˺�����ʼ������
void init(struct snack * mySnack)
{
	show_wall();
	make_food(mySnack);
	draw_Snack(mySnack);
}

//�ж����Ƿ�ײǽ
int hitWall(struct snack * mySnack)
{
    int flag = FALSE;
    if (mySnack->y<1 || mySnack->y>19 || mySnack->x<2 || mySnack->x>58)
    	flag = TRUE;
    return flag;
}

//�ж����Ƿ�ײ���Լ�
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

//������
void draw_Snack(struct snack * mySnack)
{
	set_color(SNACK_COLOR);
	struct snack * p = mySnack;
	gotoxy(p->x, p->y);
	printf("��");
	p = p->next;
	if (p != NULL)
    {
        while (p != NULL)
        {
            gotoxy(p->x, p->y);
            printf("��");
            p = p->next;
        }

    }
}

int main(void)
{
	system("mode con cols=100 lines=25");//���ÿ���̨���ڴ�С
	int direct = UP;
	int key = 0;
	int delay_time = 500;
	int choice;
	struct snack * mySnack = (struct snack *)malloc(sizeof(struct snack));
	mySnack->x = 30;
	mySnack->y = 10;
	mySnack->next = NULL;

	struct snack * p;
	struct snack * tail; //���ڱ������һ���ڵ�
	struct snack * perTail; //���ڱ������һ���ڵ��ǰ���ڵ�

	FILE * fp = fopen("record.txt", "a+");  //����߼�¼�ļ�
	if (fp == NULL)
	{
		printf("����ʷ��¼�ļ�ʧ�ܣ�");
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
				choice = MessageBox(NULL,TEXT("��Ҫ�˳���"),TEXT("����"),MB_ICONINFORMATION|MB_YESNO);
				switch (choice){
				case IDYES:
					if (score > max_score)
					{
						fclose(fp);
						fp = fopen("record.txt", "w");
						if(fp == NULL)
						{
							printf("�򿪼�¼�ļ�ʧ�ܣ�");
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

        p = (struct snack *)malloc(sizeof(struct snack));  //����һ���µĽڵ�������Ϊ���µ�ͷ��

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

        if (isEat(mySnack)) //����Ե���ʳ������������µ�ʳ�ﲢ�Ҳ�ȥ����β�ڵ�
        {
        	score++;
        	if (delay_time > FINAL_SNACK_SPEED)
        		delay_time -= 50;
        	set_color(TEXT_COLOR);
        	gotoxy(62, 9);
			printf("��ǰ������  %d", score);
            make_food(mySnack); //�Ե�ʳ��֮��Ҫ�����µ�ʳ��
        }
        else  //���û�Ե�ʳ��Ͱ������е�β���ȥ��������ԭ����β����λ���ñ���ɫ���
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
            printf("��");
            free(tail);
            perTail->next = NULL; //��β����ָ����ָ��NULL
        }

		if (hitWall(mySnack) || hitSelf(mySnack))
		{
			//��Ϸ����
			if (score > max_score)
			{
				fclose(fp);
				fp = fopen("record.txt", "w");
				if(fp == NULL)
				{
					printf("�򿪼�¼�ļ�ʧ�ܣ�");
					exit(-1);
				}
				fprintf(fp, "%d", score);
				fclose(fp);
			}
			MessageBox(NULL,TEXT("oo �����ˣ��������ɣ�"),TEXT("������˼"),MB_OK);
			exit(0);
		}
		draw_Snack(mySnack);
		Sleep(delay_time);
	}

	return 0;
}
