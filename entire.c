#include<stdio.h>
#include <stdlib.h>//system()함수에 필요
#include <time.h>
#include <unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
#define M 11

void stage_check();
void search_hole();
void file_save();
void rank();

int replay_check = 0; //0은 시작 x , 1은 시작 o
int undo[5][N][N];
char map_memory[5][N][N];
char map[5][N][N];//전역변수
char name[N][10]; //이름받을때 쓰는거
char p_map[30][30];
int x=0, y=0, z=0, i;
time_t start_time, end_time;
char key; // r,n,e 포함 나머지 입력 값들도 이 key변수로 받을 것.

void rank(){
	int i, j, k, m, n, rank[N], time1[N];
	int l=0;
	//char name[M] 전역변수로 있는 상태
	
	time(&end_time);
	time1[i]=difftime(end_time, start_time);

	for(j=0;j<10;j++)
	{
		for(k=0;k<10;k++)
		{
			if(time1[j]-time1[k]<0)
			{
				l=l+1;
			}
		}
		rank[l]=time1[j];
		l=0;
	}

	for(m=0;m<4;m++)
	{
		for(n=0;n<4;n++)
		{
			if(time1[n] == rank[m])
				printf("%d위 : %s", rank[m], name[N][10]);
		}
	}
}
//이름 입력받는 함수
void get_name()
{
	int i=0,a;
	printf("Start....\n input name : ");
	while(1){
		a = getchar();
		if(i==M){
			while((a=getchar()) != '\n')
				;
			printf("10자 이하의 이름을 입력해 주세요 : ");
			i = 0;
			continue;
		}
		if((a =='\n')||(a == EOF)) {
			name[N][i++] = '\0';
			break;
		}
		name[N][i++] = a;
	}
	system("clear");
	printf("\n");
}

//현재위치 찾는 함수?
int scanchar()
{
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(map[0][i][j]=='@'){
				x=j;
				y=i;
			}
	return 0;
}

//map.txt파일 스캔하는 함수(완성)
int mapscan()
{
	FILE *scan;
	char a;
	scan=fopen("q.txt","r");
	while(fscanf(scan,"%c",&a) != EOF){
		if(y==N){
			y=0;
			z++;
		}
		else if(a=='\n'){
			map[z][y][x]='\n';
			y++;
			x=0;
		}
		else if(a=='$'){
			map[z][y][x]='$';
			x++;
		}
		else if(a=='@'){
			map[z][y][x]='@';
			x++;
		}
		else if(a=='#'){
			map[z][y][x]='#';
			x++;
		}
		else if(a==' '){
			map[z][y][x]=' ';
			x++;
		}
		else if(a=='O'){
			map[z][y][x]='O';
			x++;
		}
		else
			;
	}
	fclose(scan);
	return 0;
}

void undo_scan()
{
	for(int y=0; y<N; y++)
	for(int x=0; x<N; x++){
		undo[4][y][x]= undo[3][y][x];
		undo[3][y][x]= undo[2][y][x];
		undo[2][y][x]= undo[1][y][x];
		undo[1][y][x]= undo[0][y][x];
		undo[0][y][x]= map[z][y][x];
	}
}

////// map출력 함수(거의 완성)
int mapprint1()
{
	int x,y,z=0;
	printf("Hello %s", name);
	printf("\n\n");
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint2로 넘어가는 조건.
	return 0;
}

int mapprint2()
{
	int x,y,z=1;
	printf("Hello %s", name);
	printf("\n\n");
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint3로 넘어가는 조건.
	return 0;
}

int mapprint3()
{
	int x,y,z=2;
	printf("Hello %s", name);
	printf("\n\n");
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint4로 넘어가는 조건.
	return 0;
}

int mapprint4()
{
	int x,y,z=3;
	printf("Hello %s", name);
	printf("\n\n");
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint5로 넘어가는 조건.
	return 0;
}

int mapprint5()
{
	int x,y,z=4;
	printf("Hello %s", name);
	printf("\n\n");
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	return 0;
}

////// ??
int getch()
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

////// 입력포함 모든 옵션 입력받는 함수.(이거 완성하면 끝)
void keyMove()
{

	int key;
	scanchar();
	key=getch();

	system("clear");

	switch(key){

		case 'u': //undo 미완성.

		case 'r':
			{
			if(z==0)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[0][y][x] = map_memory[0][y][x];
			mapprint1();
			}

			if(z==1)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[1][y][x] = map_memory[1][y][x];
			mapprint2();
			}

			if(z==2)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[2][y][x] = map_memory[2][y][x];
			mapprint3();
			}

			if(z==3)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[3][y][x] = map_memory[3][y][x];
			mapprint4();
			}

			if(z==4)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[4][y][x] = map_memory[4][y][x];
			mapprint5();
			}

			break;
			}

		case 'n':
		{
		system("clear");
		start_time =0;
		for(int z=0; z<5; z++)
			for(int y=0; y<N; y++)
				for(int x=0; x<N; x++)
					map[z][y][x] = map_memory[z][y][x];

		mapprint1();
		time(&start_time);
		break;
		}

		case 'e':
		{
			file_save();
			exit(-1);
			break;
		}

		case 's':
		{
			file_save();
			break;
		}

		case 'f': //

		case 't': //ranking

		case 'd':
		{
		system("clear");
		printf("h(왼쪽), j(아래), k(위), l(오른쪽)\n");
		printf("u(undo) \n");
		printf("r(replay) \n");
		printf("n(new) \n");
		printf("e(exit) \n");
		printf("s(save) \n");
		printf("f(file load) \n");
		printf("d(display help) \n");
		printf("t(top) \n");
		printf(" \n ※※※뒤로 가려면 q를 누르세요※※※ ");

		int key2;
		scanchar();
		key2=getch();

		if(key2=='q'){
			system("clear");
		break;
		}
		}

		case 'h':
			if(map[z][y][x-1] == '$'){
				if(map[z][y][x-2] == ' '){
					map[z][y][x-2]='$';
					map[z][y][x]=' ';
					map[z][y][x-=1]='@';
				}
				else if(map[z][y][x-2] == 'O'){
					map[z][y][x-2]='$';
					map[z][y][x]=' ';
					map[z][y][x-=1]='@';
				}
			}
			else if(map[z][y][x-1] == 'O'){
				map[z][y][x]=' ';
				map[z][y][x-=1]='@';
			}
			else if(map[z][y][x-1] == ' '){
				map[z][y][x]=' ';
				map[z][y][x-=1]='@';
			}
			break;

		case 'j':
			if(map[z][y+1][x] == '$'){
				if(map[z][y+2][x] == ' '){
					map[z][y+2][x]='$';
					map[z][y][x]=' ';
					map[z][y+=1][x]='@';
				}
				else if(map[z][y+2][x] == 'O'){
					map[z][y+2][x]='$';
					map[z][y][x]=' ';
					map[z][y+=1][x]='@';
				}
			}
			else if(map[z][y+1][x] == 'O'){
				map[z][y][x]=' ';
				map[z][y+=1][x]='@';
			}
			else if(map[z][y+1][x] == ' '){
				map[z][y][x]=' ';
				map[z][y+=1][x]='@';
			}
			break;

		case 'k':
			if(map[z][y-1][x] == '$'){
				if(map[z][y-2][x] == ' '){
					map[z][y-2][x]='$';
					map[z][y][x]=' ';
					map[z][y-=1][x]='@';
				}
				else if(map[z][y-2][x] == 'O'){
					map[z][y-2][x]='$';
					map[z][y][x]=' ';
					map[z][y-=1][x]='@';
				}
			}
			else if(map[z][y-1][x] == 'O'){
				map[z][y][x]=' ';
				map[z][y-=1][x]='@';
			}
			else if(map[z][y-1][x] == ' '){
				map[z][y][x]=' ';
				map[z][y-=1][x]='@';
			}
			break;

		case 'l':
			if(map[z][y][x+1] == '$'){
				if(map[z][y][x+2] == ' '){
					map[z][y][x+2]='$';
					map[z][y][x]=' ';
					map[z][y][x+=1]='@';
				}
				else if(map[z][y][x+2] == 'O'){
					map[z][y][x+2]='$';
					map[z][y][x]=' ';
					map[z][y][x+=1]='@';
				}
			}
			else if(map[z][y][x+1] == 'O'){
				map[z][y][x]=' ';
				map[z][y][x+=1]='@';
				}
			else if(map[z][y][x+1] == ' '){
				map[z][y][x]=' ';
				map[z][y][x+=1]='@';
			}
			break;
	}
}

//////파일 저장하기(미완성)
void file_save()
{
	time_t stop_time;
	time(&stop_time);
	//double difftime(stop_time,start_time);
	double d_diff_stop = difftime(stop_time,start_time);

	FILE *file_save;
	file_save=fopen("sokoban.txt","w");

	fprintf(file_save,"%s",name);  //이름
	fprintf(file_save," ");

	fprintf(file_save,"%.1f",d_diff_stop); //시간
	fprintf(file_save,"\n");

	fprintf(file_save,"%c",z);//맵 stage
	fprintf(file_save,"\n");

	for(int y=0;y<30;y++)
		for(int x=0;x<30;x++)
			fprintf(file_save,"%c",map[z][y][x]); //맵

	fclose(file_save);
}


//////저장한 파일 불러오기(미완성)
void file_load()
{
	FILE *file_save;
	file_save=fopen("sokoban.txt","r");
	double d_diff_stop;
	char space;
	for(int z=0;z<30;z++)
		for(int y=0;y<30;y++)
			for(int x=0;x<30;x++)
				fscanf(file_save,"%c",&map[z][y][x]);

	fscanf(file_save,"%s %.1f", name, d_diff_stop);

	fscanf(file_save,"%c",map[z][y][x]);
	fclose(file_save);
}

int memory() //초기 맵 상태 저장
{
	if (replay_check == 0){
	for(int z=0; z<5; z++ )
		for(int y=0; y<N; y++ )
			for(int x=0; x<N; x++)
			map_memory[z][y][x] = map[z][y][x];
		}
		x=0,y=0,z=0;
}

//////main 함수.
int main(void)
{
	get_name();
	memory();
	mapscan();
	mapprint1();
	time(&start_time);

	while(1){

		replay_check = 1 ; //움직임을 입력.

		keyMove();
		search_hole();
		mapprint1();
		search_hole();
		stage_check();
		//if (보관함 개수 == 0)
		//while(1) keyMove(),mapprint2()

		//~반복

	}
	time(&end_time);
	//double difftime(end_time, start_time);
	double d_diff = difftime(end_time, start_time);

	return 0;
}

//sokobar 678행 참고.
//undo_scan , undo_print -> 옵션 r과 n 모두 할 수 있을듯?
//undo로 !!!처음 맵을 저장!!!해놓는다면 원래 O위치에 아무것도 없을 때 다시 O가능?
//e
//keymove(hjkl) 보관함 사라지는 문제
//save, load
//ranking -> 옵션 t

void search_hole()
{
	for(int z=0;z<5;z++)
		for(int y=0;y<N;y++)
			for(int x=0;x<N;x++)
			{
				if (map_memory[z][y][x]=='O')
					if (map[z][y][x]==' ')
					map[z][y][x]='O';
			}
}


void next_stage()
{
	if (z==0)
	mapprint2();
	if (z==1)
	mapprint3();
	if (z==2)
	mapprint4();
	if (z==3)
	mapprint5();
}


void stage_check()
{
	int i=0;//필요개수 충족위해 필요 변수
	int o=0;//맵별 똥그라미 개수

		for(int y=0;y<N;y++)
			for(int x=0;x<N;x++)
			if(map_memory[0][y][x]=='O')
			o++;

		for(int y=0;y<N;y++)
			for(int x=0;x<N;x++)
			{
				if (map_memory[0][y][x]=='O')
				 if (map[0][y][x]=='$')
				 i++;

			}
				if(i==o)
				next_stage();//이자리에 next stage만들어서 다음으로.
}
