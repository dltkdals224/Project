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
	
	int x=0,y=0,z=0,a;
	FILE *scan;
	scan=fopen("map","r");
	for(;z<5;z++)
		for(;y<30;y++)
			for(;x<30;x++)
				map[z][y][x]=' ';
	while((fscanf(scan,"%c",&a))!=EOF){
		if(a=='\n'){
			map[z][y][x]=a;
			y++;}
		else if(a=='#'){
			map[z][y][x]=a;
			x++;}
		else if(a=='O'){
			map[z][y][x]=a;
			x++;}
		else if(a=='@'){
			map[z][y][x]=a;
			x++;}
		else if(a=='$'){
			map[z][y][x]=a;
			x++;}

		}
	fclose(scan);
	return 0;
}

int printmap()
{
	int i,j,a;
	for(i=0;i<30;i++)
		for(j=0;j<30;j++)
		{
			printf("%c",map[0][i][j]);
		}
	return 0;
}	
int main()
{
	int i=0,a;
	
	system("clear");
	printf("Start....\ninput name : ");// 이름 10글자 이내로 입력받기 해결하기.
		for(i=0;i<10;i++)
		{
			name[i]=getch();
			if(name[i]=='\n')
				break;
				}
	system("clear");
	scanmap();
	printmap();
	return 0;
}
