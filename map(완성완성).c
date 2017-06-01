#include<stdio.h>
#include<stdlib.h> //system()함수쓸때 필요
#include<time.h> //시간함수
#include<unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
int map[5][N][N];//전역 변수
int name[10]; //이름받을때 쓰는거
int p_map[30][30];
int x=0,y=0,z=0,i;

//mapscan()함수는 map.txt라는 한 파일로부터 모든 map을 저장받는다.
int mapscan()
{
	FILE *scan;
	int a;
	scan=fopen("map.txt","r");
	while(fscanf(scan,"%c",&a) != EOF){
    	if(y==N){
      	 y=0;
     	 z++;
   		 }
		else if(a=='\n'){
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

//아래의 mapprint함수들은 stage를 따로따로 불러오는 각각의 함수.
int mapprint1()
{
  int x,y,z=0;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
		printf("\n");
	}
	return 0;
}
int mapprint2()
{
  int x,y,z=1;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
		printf("\n");
	}
	return 0;
}
int mapprint3()
{
  int x,y,z=2;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
		printf("\n");
	}
	return 0;
}
int mapprint4()
{
  int x,y,z=3;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
		printf("\n");
	}
	return 0;
}
int mapprint5()
{
  int x,y,z=4;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
		printf("\n");
	}
	return 0;
}
//아래 main함수 실행화면을 보기위해 mapprint함수를 모두 실행해놨지만 단계 클리어시 다음 함수 실행하면됨.
int main()
{
	mapscan();
	mapprint1();
	mapprint2();
	mapprint3();
	mapprint4();
	mapprint5();
	return 0;
}
//이거를 이렇게 함수 5개로하면 좀 그런가요?
