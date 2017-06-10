#include<stdio.h>
#include <stdlib.h>//system()함수에 필요
#include <time.h>
#include <unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
#define M 11


int scanchar(); // @(창고지기)의 위치 찾는 함수.

int mapscan(); // map.txt파일을 삼차원 배열 map[z][y][x]에 저장하는 함수.
int mapmemory(); // 움직이지 않았을 때 map 상태를 저장해놓는 함수.(r과n에 필요)

int getch(); // 한문자씩 받게 해주는 함수.
void get_name(); // 이름 입력받는 함수.
void mapprint(); // mapscan으로 저장한 배열을 출력하는 함수.
void keymove(); // 움직임포함 모든 명령키 입력받고 실행하는 함수.
void undo_scan(); // undo를 실행하기위해 이전의 움직임을 저장하는 함수.
void undo_do(); // u를 눌렀을 때 undo를 실행하는 함수.
void file_save(); // s를 눌렀을 때 save를 하는 함수.
void file_load(); // f를 눌렀을 때 file load를 하는 함수.

void stage_check_cheking();// 게임 시작시 $의 개수와 O의 개수가 일치하지 않으면 종료하는 함수.
void stage_check_nextstage(); // next_stage로 넘어가기 위한 조건을 실시간으로 찾는 함수.
void search_hole(); // 보관함이 사라졌을 때 재출력 하는 함수.
void end(); // 게임 끝났을 때 함수.

//void rank();
//void load_rank();

int stage_clear = 0;
int u=0; //undo 횟수를 기록하기위해 사용하는 변수. keymove의 'u'에서 사용하기위해 전역변수.
int a=0; //움직임 하나에 a++; ( next_stage에서 undo 바로사용 방지. )
int replay_check = 0; //0은 시작 x , 1은 시작 o
char undo_memory[5][N][N];
char map_memory[5][N][N];
char map[5][N][N];//전역변수
char name_rank[100][10];
char name[10]; //이름받을때 쓰는거
char record_name[N][10];
char p_map[30][30];
int x=0, y=0, z=0, i;
time_t start_time, end_time;
double d_diff_stop=0;
char key; // r,n,e 포함 나머지 입력 값들도 이 key변수로 받을 것.

void rank_save(){
	FILE *ran;
	FILE *ran3;
	ran3=fopen("ranking","w");
	ran=fopen("ranking_1","a");
	int i, j, k, m, n, rank[N], time1[N];
	int l=0;
	int a, b=0, c=0;
	//char name[M] 전역변수로 있는 상태
	
	fprintf(ran,"%s :",name);
	fprintf(ran,"%d\n",end_time-start_time);
	fclose(ran);

	FILE *ran2;
	ran2=fopen("ranking_1","r");

	while((a=getchar())!=EOF){
		if(b==1){
			fscanf(ran2,"%d",time1[c]);
			c++;
		}
		if(a==':'){
			b=1;}
	}
	c=0;
	while((a=getchar())!=EOF){
		if(a==':'){
			break;
		}
		fscanf(ran2, "%s", name_rank[c]);
		c++;
	}
	fclose(ran2);


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
		for(n=0;n<100;n++)
		{
			if(time1[n] == rank[m])
				fprintf(ran3, "%d위 : %s", m+1, name_rank[n][10]);
		}
	}
	fclose(ran3);
}
void rank_load(){
	FILE *ran;
	FILE *ran3;
	ran3=fopen("ranking","w");
	ran=fopen("ranking_1","a");
	int i, j, k, m, n, rank[N], time1[N];
	int l=0;
	int a, b=0, c=0;
	//char name[M] 전역변수로 있는 상태
	system("clear");

	fprintf(ran,"%s :",name);
	fprintf(ran,"%d\n",end_time-start_time);
	fclose(ran);

	FILE *ran2;
	ran2=fopen("ranking_1","r");

	while((a=getchar())!=EOF){
		if(b==1){
			fscanf(ran2,"%d",time1[c]);
			c++;
		}
		if(a==':'){
			b=1;}
	}
	c=0;
	while((a=getchar())!=EOF){
		if(a==':'){
			break;
		}
		fscanf(ran2, "%s", name_rank[c]);
		c++;
	}
	fclose(ran2);


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
		for(n=0;n<100;n++)
		{
			if(time1[n] == rank[m])
				printf("%d위 : %s", m+1, name_rank[n][10]);
		}
	}
	fclose(ran3);
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

//undo 메모리 옮기기.
void undo_do()
{

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
	if(z<6)
	printf("map %d\n",z+1);
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

			//a는 움직인 횟수.(맵별로 초기화) , u은 언두 횟수.
			if(a>u)
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
					map[c][b][a] = map_memory[0][b][a];

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
		
			rank_load();
		
			int key3;
			scanchar();
			key3=getch();
			if(key3=='q')
				system("clear");

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
		printf(" \n ※※※뒤로 가려면 d 혹은 q를 눌러주세요※※※ \n\n");

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
			a++;
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
			a++;
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
			a++;
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
			a++;
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

	fscanf(record_load,"%.1f",&d_diff_stop);
	fscanf(record_load,"%c",&tmp);

	fscanf(record_load,"map%d",&z);
	z--;
	fscanf(record_load,"%c",&tmp);
	for(int z=0;z<5;z++)
		for(int y=0;y<30;y++)
			for(int x=0;x<30;x++)
				fscanf(record_load,"%c",&map[z][y][x]);

	fclose(record_load);

	stage_check_nextstage();
	search_hole();
}

int mapmemory() //초기 맵 상태 저장
{
	if (replay_check == 0){
	for(int z=0; z<5; z++ )
		for(int y=0; y<N; y++ )
			for(int x=0; x<N; x++)
			map_memory[z][y][x] = map[z][y][x];
		}

}


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
void stage_check_nextstage()
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
			if(z<4)
			z++;
			a++;
			stage_clear++;
		}
}


//게임 시작시 $의 개수와 O의 개수가 일치하지 않으면 종료하는 함수.
void stage_check_cheking()
{
	int o=0;
	int m=0;

	for(int y=0; y<N; y++)
		for(int x=0; x<N; x++)
		if(map[z][y][x]=='O')
		o++;

	for(int y=0; y<N; y++)
		for(int x=0; x<N; x++)
		if(map[z][y][x]=='$')
		m++;

	if(m!=o)
	{
	 printf("Error : map파일의 $와 O 개수가 동일하지 않습니다.\n");
	 printf("프로그램을 종료합니다.");
	 exit(-1);
 	}
}


//끝나는 함수.
void end()
{
	system("clear");

	printf("\n\n");
	printf("축하드립니다 %s님 모든 스테이지를 클리어 하셨습니다.",name);
	printf("\n");
}





//////main 함수.
int main(void)
{
	mapscan();
	stage_check_cheking();
	get_name();

	time(&start_time);

	mapmemory();

	while(1){
		replay_check = 1 ; //움직임을 입력.

		mapprint();
		keyMove();

		search_hole();
		stage_check_nextstage();

		if(stage_clear == 5){
		rank_save();
		break;
		}
	}
	time(&end_time);
	double d_diff = d_diff_stop + difftime(end_time, start_time);

	//rank()

	end();
	printf("클리어에 걸린 시간 : %.1fsec",d_diff);
	printf("\n\n");
	return 0;
}
