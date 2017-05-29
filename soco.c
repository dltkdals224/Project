#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<termio.h>
#define N 30
int map[5][N][N];//전역 변수
int name[10]; //이름받을때 쓰는거

int getch()//실습09 7번문제
{
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0,TCSAFLUSH,&buf);
	ch = getchar();
	tcsetattr(0,TCSAFLUSH,&save);

	return ch;
}

int scanmap()
{
	int i=0,j=0,a;
	FILE *scan;
	scan=fopen("map","r");
	while((a=getc(scan))!=EOF){
		if(a=='\n')
			map[0][j][i]=getc(scan);
			j++;
			i=0;
		
		else
			map[0][j][i]=getc(scan);
			i++;
}
int main()
{
	int i=0,a;
	
	printf("Start....\ninput name : ");// 이름 10글자 이내로 입력받기 해결하기.
		for(i=0;i<10;i++)
		{
			name[i]=getch();
			if(name[i]=='\n')
				break;
				}
	system("clear");
}
