#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<termio.h>
#define N 30
char map[5][15][N];//전역 변수
int name[10]; //이름받을때 쓰는거
int i,x,y,z,k;

void scanmap() //맵을 배열에 저장하는 함수
{
	FILE *scan;
	scan=fopen("map.txt","r");
	while(1){
		fscanf(scan,"%c",&map[z][y][x]);
		if(map[z][y][x]=='\n'){
			y++;
			x=0;
		}
		else if(y>14){
		y=0;
		z++;
	}
	else if(z==5)
	break;
		else
		x++;
		}
	fclose(scan);
}

void printmap(int n) //맵 출력하는 함수
{
	//항상참으로 하여 실행한 뒤 break;로 빠져나온다.
	while(1){
	printf("%c",map[z][y][x]);
	if(map[z][y][x]=='\n'){
		y++;
		x=0;
	}
	else if(y>14){
	y=0;
	z++;
}
else if(z==n+1)
break;
	else
	x++;
	}
}
int main(){
	scanmap();
	printmap(k);
}
