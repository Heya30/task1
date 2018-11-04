#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LINE_MAX 25    //地图行 i = 30
#define ROW_MAX 45     //地图列 j = 50
#define lengthNum 200  //蛇长的最大值
int snakeLength;       //蛇长度
int sx[LINE_MAX],sy[ROW_MAX];
int sx2[LINE_MAX],sy2[ROW_MAX];
int fx,fy;
int dx,dy;
int map[LINE_MAX][ROW_MAX] = {0};
char direction;
int scores;
int m ;
int bomb_x,bomb_y;
int start_level,level;
int again;


void gotoxy(int x,int y){

	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos;

	pos.X=x;

	pos.Y=y;

	SetConsoleCursorPosition(handle,pos);

}

void start_interface(){
    gotoxy(0,5);
    printf("*************************************************\n\n\n\n");
    printf("欢迎进入贪吃蛇\n\n\n");
    printf("请切换英文输入法\n\n\n\n\n");
    printf("请选择游戏难度(请输入一个1-20的数字):\n\n\n\n");
    printf("*************************************************\n");
    gotoxy(0,18);
    scanf("%d",&start_level);
    system("pause");



}
void start_date(){

	int i,j;
	m = 200 - 10*(level-1);
	sx[0]=15;sy[0]=15;//蛇的初始位置

	sx[1]=15;sy[1]=16;
	snakeLength = 2;

	fx=8;fy=7;//食物
	dx=12;dy=13;
	level = start_level ;
	bomb_x = 4; bomb_y = 20;
	scores = 0;
	map[sx[0]][sy[0]]=1;

	map[sx[1]][sy[1]]=1;

	map[fx][fy]=2;

	map[dx][dy] = 3;
	for(i=0;i<LINE_MAX;i++)

		for(j=0;j<ROW_MAX;j++)

			if(i==0||j==0||i==LINE_MAX-1||j==ROW_MAX-1)

                    map[i][j]=4;
    map[bomb_x][bomb_y] = 5;


}


void show(){
    gotoxy(0,0);
    int i, j;
    for (i = 0; i <LINE_MAX;i++)
    {
        for(j = 0; j < ROW_MAX; j++)
            {
                if(map[i][j] == 1)
                    printf("■");
                else if(map[i][j] == 2)
                    printf("+ ");
                else if(map[i][j] == 3)
                    printf("- ");
                else if(map[i][j] == 4)
                    printf("* ");
                else if(map[i][j] == 5)
                    printf("炸");
                else
                    printf("  ");
            }
        printf("\n");
    }
    printf("分数为:%d分\n",scores );
    printf("等级为：%d级",level);
}

void move(){

	int i;

	if(kbhit())    //输入方向
	{
	    direction = getch();
	}

    if (direction=='w')

		{
            map[sx[snakeLength-1]][sy[snakeLength-1]] = 0;
		    for(i = snakeLength-1; i >= 1; i--)
            {
                sx[i] = sx[i-1];
                sy[i] = sy[i-1];
            }
            sx[0]--;
            map[sx[0]][sy[0]] = 1;
		}
    if (direction=='s')

		{
            map[sx[snakeLength-1]][sy[snakeLength-1]] = 0;
		    for(i = snakeLength-1; i >= 1; i--)
            {
                sx[i] = sx[i-1];
                sy[i] = sy[i-1];
            }
            sx[0]++;
            map[sx[0]][sy[0]] = 1;
		}
    if (direction=='d')

		{
            map[sx[snakeLength-1]][sy[snakeLength-1]] = 0;
		    for(i = snakeLength-1; i >= 1; i--)
            {
                sx[i] = sx[i-1];
                sy[i] = sy[i-1];
            }
            sy[0]++;
            map[sx[0]][sy[0]] = 1;
		}
    if (direction=='a')
    {
        map[sx[snakeLength-1]][sy[snakeLength-1]] = 0;
        for(i = snakeLength-1; i >= 1; i--)
        {
            sx[i] = sx[i-1];
            sy[i] = sy[i-1];
        }
        sy[0]--;
        map[sx[0]][sy[0]] = 1;
    }


}

void lengthChange(){
    int i ,k;
    if (sx[0] == fx && sy[0] == fy)

    {
        snakeLength++;
        scores++;
        while(1){
            srand((unsigned)time(NULL));
            fx=rand()%(LINE_MAX-2)+1;
            fy=rand()%(ROW_MAX-2)+1;
            if(sx[0] != fx ||sy[0] != fy)
                break;

        }
        map[fx][fy]=2;
        printf("\a");
    }
    if(sx[0] == dx &&sy[0]==dy)
        {
        map[sx[snakeLength-1]][sy[snakeLength-1]] = 0;
        snakeLength--;
        scores--;
        while(1){
            srand((unsigned)time(NULL));
            dx=rand()%(LINE_MAX-2)+1;
            dy=rand()%(ROW_MAX-2)+1;
            if(sx[0] != dx ||sy[0] != dy)
                break;
            }
        map[dx][dy]=3;
        }
    if(sx[0] == bomb_x && sy[0] == bomb_y)
    {
        for( k = snakeLength-1 ;k>=snakeLength/2 ;k-- )
            map[sx[k]][sy[k]] = 0;
        snakeLength = snakeLength/2;
        while(1){
            srand((unsigned)time(NULL));
            bomb_x=rand()%(LINE_MAX-2)+1;
            bomb_y=rand()%(ROW_MAX-2)+1;
            m += 10;
            if(sx[0] != dx ||sy[0] != dy)
                break;
            }
        map[bomb_x][bomb_y] = 5;
        scores = scores /2 ;
    }
    if(level <= 20 )
        m = 200 - 10*(level-1);
    else
        m = 0;
    level = start_level +scores/5;
}

void deathJudge(){
    int i ;
    if (sx[0] == 0 ||sy[0] ==0 ||sx[0]==LINE_MAX - 1 ||sy[0] ==ROW_MAX - 1 )    //判断是否撞墙
    {
        system("cls");
        printf("\n\n\n\n游戏结束");
        getch();
        exit(1);
    }
    for(i = 1;i <= m; i++)
    {
        if (sx[0] == sx[i] && sy[0] == sy[i])
        {   system("cls");
            printf("\n\n\n\n游戏结束");
            getch();
            exit(1);
        }

    }
    if (snakeLength < 2 )
    {
        system("cls");
        printf("\n\n\n\n游戏结束");
        getch();
        exit(1);
    }
}

int main()
{
    tryagain:start_interface();
    start_date();
    while(1)
	{
        show();//打印画面
		move();//与用户输入有关的更新
        lengthChange();
        Sleep(m);
        deathJudge();
	}

    return 0;
}
