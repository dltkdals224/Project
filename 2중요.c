#include<stdio.h>
#include<stdlib.h> //system()함수쓸때 필요
#include<time.h> //시간함수
#include<unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
int map[5][N][N];//전역 변수
int name[10]; //이름받을때 쓰는거
int p_map[30][30];
int mapscan()
{
	FILE *scan;		
	int a;
	int x=0,y=0,z=0,i;
	scan=fopen("map5.txt","r");
	while(fscanf(scan,"%c",&a) != EOF){
		if(a=='\n'){
			y++;
			x=0;
			}
		else if(a=='$'){
			map[z][y][x]='$';
			x++;}
		else if(a=='@'){
			map[z][y][x]='@';
			x++;}
		else if(a=='#'){
			map[z][y][x]='#';
			x++;}
		else if(a==' '){
			map[z][y][x]=' ';
			x++;}
		else if(a=='O'){
			map[z][y][x]='O';
			x++;}
		else
			;
	}
	fclose(scan);
	return 0;
}
int mapprint()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			printf("%c",map[0][i][j]);
		printf("\n");
	}
	return 0;
}
int main()
{
	int q=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			map[0][i][j]=' ';
	mapscan();
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			printf("%c", map[0][i][j]);
		printf("\n");	
	}
	return 0;}
