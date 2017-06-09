#include<stdio.h>
#include <stdlib.h>//system()함수에 필요
#include <time.h>
#include <unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
#define M 11

void keymove();
void undo_scan();
void undo_do();
void file_load();
void stage_check();
void search_hole();
void file_save();
void end();

//void rank();
//void load_rank();

int replay_check = 0; //0은 시작 x , 1은 시작 o
char undo_memory[5][N][N];
char map_memory[5][N][N];
char map[5][N][N];//전역변수
char name[10]; //이름받을때 쓰는거
char record_name[N][10];
char p_map[30][30];
int x=0, y=0, z=0, i;
time_t start_time, end_time;
double d_diff_stop=0;
char key; // r,n,e 포함 나머지 입력 값들도 이 key변수로 받을 것.

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
			name[i++] = '\0';
			break;
		}
		name[i++] = a;
	}
	//name[N][10] = name; <- ranking에 필요
	system("clear");
	printf("\n");
}

//현재위치 찾는 함수?(@)
int scanchar()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(map[z][i][j]=='@'){
				x = j;
				y = i;
				return 0;
			}
		}
	}
}

//map.txt파일 스캔해서 map[z][y][x]에 저장해놓는 함수(완성)
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
	z=0;
	fclose(scan);
	return 0;
}

//undo 스캔 해놓기.
void undo_scan()
{
	for(int y=0; y<N; y++)
		for(int x=0; x<N; x++){
			undo_memory[4][y][x]= undo_memory[3][y][x];
			undo_memory[3][y][x]= undo_memory[2][y][x];
			undo_memory[2][y][x]= undo_memory[1][y][x];
			undo_memory[1][y][x]= undo_memory[0][y][x];
			undo_memory[0][y][x]= map[z][y][x];
		}
}

//undo 프린트.
void undo_do()
{
	int u = 0;

	if(u==5)
	return;

	for(int y=0; y<N; y++)
		for(int x=0; x<N; x++){
			map[z][y][x] = undo_memory[0][y][x];
			undo_memory[0][y][x] = undo_memory[1][y][x];
			undo_memory[1][y][x] = undo_memory[2][y][x];
			undo_memory[2][y][x] = undo_memory[3][y][x];
			undo_memory[3][y][x] = undo_memory[4][y][x];
		}
		u++;

}

//mapprint 하나로 합쳐놈?
void mapprint()
{
	int x,y;
	printf("Hello %s", name);
	printf("\n\n");
	printf("map%d\n",z+1);
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
		}
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

		case 'u':

			undo_do();
			break;


		case 'r':

			if(z==0)
			{
				for(int b=0; b<N; b++)
					for(int a=0; a<N; a++)
					map[0][b][a] = map_memory[0][b][a];
					z=0;
			mapprint();
			}

			if(z==1)
			{
				for(int b=0; b<N; b++)
					for(int a=0; a<N; a++)
					map[1][b][a] = map_memory[1][b][a];
					z=1;
			mapprint();
			}

			if(z==2)
			{
				for(int b=0; b<N; b++)
					for(int a=0; a<N; a++)
					map[2][b][a] = map_memory[2][b][a];
					z=2;
			mapprint();
			}

			if(z==3)
			{
				for(int b=0; b<N; b++)
					for(int a=0; a<N; a++)
					map[3][b][a] = map_memory[3][b][a];
					z=3;
			mapprint();
			}

			if(z==4)
			{
				for(int b=0; b<N; b++)
					for(int a=0; a<N; a++)
					map[4][b][a] = map_memory[4][b][a];
					z=4;
			mapprint();
			}

			break;


		case 'n':

		system("clear");
		start_time =0;
		for(int c=0; c<5; c++)
			for(int b=0; b<N; b++)
				for(int a=0; a<N; a++)
					map[c][b][a] = map_memory[c][b][a];

		mapprint();
		time(&start_time);
		break;


		case 'e':

			file_save();
			system("clear");

			printf("\n\n");
			printf("SEE YOU %s. . . .",name);
			printf("\n");
			exit(-1);
			break;


		case 's':

			file_save();
			break;


		case 'f':

			file_load();
			break;


		case 't':

			//load_rank();
			break;


		case 'd':
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

		if(key2=='q')
			system("clear");
		break;

		case 'h':
		undo_scan();
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
		undo_scan();
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
		undo_scan();
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
		undo_scan();
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
void file_save() //game_file_save로 변경
{
	time_t stop_time;
	time(&stop_time);
	//double difftime(stop_time,start_time);
	double d_diff_stop = difftime(stop_time,start_time);

	FILE *file_save;
	file_save=fopen("sokoban.txt","w");

	fprintf(file_save,"%s",name);  //이름 저장
	fprintf(file_save," ");

	fprintf(file_save,"%.1f",d_diff_stop);  //시간 저장
	fprintf(file_save,"\n");
	fprintf(file_save,"map %d\n",z+1);
//맵 저장
if(z==0)
	for(int b=0;b<30;b++)
		for(int a=0;a<30;a++)
			fprintf(file_save,"%c",map[0][b][a]);
if(z==1)
	for(int b=0;b<30;b++)
		for(int a=0;a<30;a++)
			fprintf(file_save,"%c",map[1][b][a]);
if(z==2)
	for(int b=0;b<30;b++)
		for(int a=0;a<30;a++)
			fprintf(file_save,"%c",map[2][b][a]);
if(z==3)
	for(int b=0;b<30;b++)
		for(int a=0;a<30;a++)
			fprintf(file_save,"%c",map[3][b][a]);
if(z==4)
	for(int b=0;b<30;b++)
		for(int a=0;a<30;a++)
			fprintf(file_save,"%c",map[4][b][a]);
	fclose(file_save);
}


//////저장한 파일 불러오기(미완성)
void file_load() //game_file_load로 변경
{
	FILE *record_load;
	record_load=fopen("sokoban.txt","r");

	char tmp;
	start_time = 0;
	time(&start_time);

	fscanf(record_load,"%s",name);
	fscanf(record_load,"%c",&tmp);

	fscanf(record_load,"%f",&d_diff_stop);
	fscanf(record_load,"%c",&tmp);

	fscanf(record_load,"map%d",&z);
	z--;
	fscanf(record_load,"%c",&tmp);
	for(int z=0;z<5;z++)
		for(int y=0;y<30;y++)
			for(int x=0;x<30;x++)
				fscanf(record_load,"%c",&map[z][y][x]);

	fclose(record_load);

	stage_check();
	search_hole();
}

int memory() //초기 맵 상태 저장
{
	if (replay_check == 0){
	for(int z=0; z<5; z++ )
		for(int y=0; y<N; y++ )
			for(int x=0; x<N; x++)
			map_memory[z][y][x] = map[z][y][x];
		}

}

//////main 함수.
int main(void)
{
	get_name();
	mapscan();
	//mapprint();
	//scanchar();
	time(&start_time);
	//search_hole();
	memory();
	while(1){
		replay_check = 1 ; //움직임을 입력.
		mapprint();
		keyMove();


		search_hole();
		stage_check();
		//if (보관함 개수 == 0)
		//while(1) keyMove()

		//~반복
	}
	time(&end_time);
	//double difftime(end_time, start_time);
	double d_diff = d_diff_stop + difftime(end_time, start_time);
	//rank()
	end();
	return 0;
}

//sokobar 678행 참고.
//undo_scan , undo_print -> 옵션 r과 n 모두 할 수 있을듯?
//undo로 !!!처음 맵을 저장!!!해놓는다면 원래 O위치에 아무것도 없을 때 다시 O가능?
//e
//keymove(hjkl) 보관함 사라지는 문제
//save, load
//ranking -> 옵션 t

//구멍 메우는 함수
void search_hole()
{
		for(int y=0;y<N;y++)
			for(int x=0;x<N;x++)
			{
				if (map_memory[z][y][x]=='O')
					if (map[z][y][x]==' ')
						map[z][y][x]='O';
			}
}

//stage완료 조건을 확인하는 함수
void stage_check()
{
	int i=0;//필요개수 충족위해 필요 변수
	int o=0;//맵별 똥그라미 개수

		for(int y=0;y<N;y++)
			for(int x=0;x<N;x++)
			if(map_memory[z][y][x]=='O')
			o++;

		for(int y=0;y<N;y++)
			for(int x=0;x<N;x++)
			{
				if (map_memory[z][y][x]=='O')
				 if (map[z][y][x]=='$')
				 i++;
			}
		if(i==o){
			z++;
		}
				//next_stage();//이자리에 next stage만들어서 다음으로.
}

//끝나는 함수.
void end()
{
	system("clear");

	printf("\n\n");
	printf("SEE YOU %s. . . .",name);
	printf("\n");
}
