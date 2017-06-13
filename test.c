#include<stdio.h>
#include <stdlib.h>//system()함수에 필요
#include <time.h>
#include <unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
#define M 11


int mapscan(); // map.txt파일을 삼차원 배열 map[z][y][x]에 저장하는 함수.
int mapmemory(); // 움직이지 않았을 때 map 상태를 저장해놓는 함수.(r과n에 필요)

int getch(); // 한문자씩 받게 해주는 함수.

void get_name(); // 이름 입력받는 함수.

int scanchar(); // @(창고지기)의 위치 찾는 함수
void keyMove(); // 움직임포함 모든 명령키 입력받고 실행하는 함수.

void mapprint(); // mapscan으로 저장한 배열을 출력하는 함수.
void search_hole(); // 보관함이 사라졌을 때 재출력 하는 함수.

void undo_scan(); // undo를 실행하기위해 이전의 움직임을 저장하는 함수.
void undo_do(); // u를 눌렀을 때 undo를 실행하는 함수.

void game_file_save(); // s를 눌렀을 때 save를 하는 함수.
void game_file_load(); // f를 눌렀을 때 file load를 하는 함수.

void stage_check_end();// 게임 시작시 $의 개수와 O의 개수가 일치하지 않으면 종료하는 함수.
void stage_check_clear(); // next_stage로 넘어가기 위한 조건을 실시간으로 찾는 함수.

void end(); // 게임 끝났을 때 함수.

//void rank();
//void load_rank();

int stage_clear = 0;
int u=0; //undo 횟수를 기록하기위해 사용하는 변수. keymove의 'u'에서 사용하기위해 전역변수.
int a=0; //움직임 하나에 a++; ( next_stage에서 undo 바로사용 방지. )
int replay_check = 0; //0은 시작 x 를 나타내고 , 1은 시작 o를 나타낸다.
char undo_memory[5][N][N]; // undo 를 해내기 위해 5칸의 배열에 하나씩 밀어가며 저장하고 u키를 입력했을 때 바로 전의 것을 불러 오도록 한다.
char map_memory[5][N][N]; // map.txt 파일 처음모습을 기억해두고 r이나 n을 눌렀을 때 map[z][y][x]에 대입하여 초기모습 불러옴.
char map[5][N][N]; //실시간으로 변하는 맵 상황.
char name[100][100]; //이름받을때 쓰는 이름배열.
int x=0, y=0, z=0, i, n; //n은 이름
time_t start_time, end_time; //시간 변수.
double d_diff_stop=0; //게임을 세이브 했을 경우 start_time부터 까지의 시간차를 기록하여 저장해놓는 변수.
char key; // r,n,e 포함 나머지 입력 값들도 이 key변수로 받을 것.


//이름 입력받는 함수
void get_name()
{
	char a;
	int j;

	printf("Start....\n input name : ");
rename :
	for(j=0; j<100; j++)
	{
		a = getchar();
		name[n][j]=a;
		if(a=='\n')
			break;
	}

	if(j==0 && a=='\n')
	{
		printf("1글자 이상의 이름을 입력해 주세요 :");
		j = 0;
		n++;
		goto rename;
	}

	else if(j>10)
	{
		printf("10글자 이하의 이름을 입력해 주세요 :");
		j = 0;
		n++;
		goto rename;
	}


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
	scan=fopen("map.txt","r");
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


// mapprint 말 그래도 저장된 map배열의 내용을 프린트하는 함수.
void mapprint()
{
	int x,y;
	system("clear");
	printf("Hello %s", name[n]);
	printf("\n");
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
}


// 한 문자씩 입력 받게 해주는 실습에서 배운 내용의 함수.
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

// 입력포함 모든 옵션 입력받는 함수. (작동 키)
void keyMove()
{

	char key;
	scanchar();
	key=getch();

	system("clear");

	switch(key){

		case 'u':

			//a는 움직인 횟수(맵별로 초기화), u은 언두 횟수. <= 언두가 맵을 넘어서 실행되지 않도록 하기 위함.
			if(a>u)
				undo_do();
			printf("\n(Command) u\n\n");
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

			printf("\n(Command) r\n\n");

			break;


		case 'n':

			system("clear");
			start_time =0;
			for(int c=0; c<5; c++)
				for(int b=0; b<N; b++)
					for(int a=0; a<N; a++)
						map[c][b][a] = map_memory[0][b][a];

			printf("\n(Command) n\n\n");
			time(&start_time);
			break;


		case 'e':

			game_file_save();
			system("clear");

			printf("\n\n");
			printf("SEE YOU %s. . . .",name[n]);
			printf("\n");
			printf("\n(Command) e\n\n");
			exit(-1);
			break;


		case 's':

			game_file_save();
			printf("\n(Command) s\n\n");
			break;


		case 'f':

			game_file_load();
			printf("\n(Command) f\n\n");
			break;


		case 't':

			//load_rank();
			printf("\n(Command) f\n\n");
			break;


		case 'd':

			system("clear");
			printf("  Hello %s",name[n]);
			printf("\n\n");
			printf("h(왼쪽), j(아래), k(위), l(오른쪽)\n");
			printf("u(undo) \n");
			printf("r(replay) \n");
			printf("n(new) \n");
			printf("e(exit) \n");
			printf("s(save) \n");
			printf("f(file load) \n");
			printf("d(display help) \n");
			printf("t(top) \n");
			printf("\n(Command) d\n");
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

//파일 저장하기
void game_file_save()
{
	time_t stop_time;
	time(&stop_time);
	//double difftime(stop_time,start_time);
	double diff_time = difftime(stop_time,start_time);

	d_diff_stop += diff_time;
	FILE *file_save;
	file_save=fopen("sokoban.txt","w");

	fprintf(file_save,"%s\n",name[n]);  //이름 저장
	fprintf(file_save,"%.1f\n",d_diff_stop);  //시간 저장
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


//저장한 파일 불러오기
void game_file_load()
{
	FILE *record_load;
	record_load=fopen("sokoban.txt","r");

	char tmp;
	start_time = 0;
	time(&start_time);

	fscanf(record_load,"%s",name[n]);
	fscanf(record_load,"%c",&tmp);
	fscanf(record_load,"%lf",&d_diff_stop);
	fscanf(record_load,"%c",&tmp);

	fscanf(record_load,"map %d",&z);
	z--;
	fscanf(record_load,"%c",&tmp);
	for(int y=0;y<30;y++)
		for(int x=0;x<30;x++)
			fscanf(record_load,"%c",&map[z][y][x]);
	fclose(record_load);

	stage_check_clear();
	search_hole();

}

//r이나 n을 눌렀을 때 새 게임을 위해 초기 맵상태를 map_memory배열에 따로 저장해놓는 함수.
int mapmemory()
{
	if (replay_check == 0){
		for(int z=0; z<5; z++ )
			for(int y=0; y<N; y++ )
				for(int x=0; x<N; x++)
					map_memory[z][y][x] = map[z][y][x];
	}

}


//보관함에 @나 $가 들어갔다가 나오면 사라지는 것을 방지하기 위한 함수.
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

//stage완료 조건을 확인하는 함수 <= O의 자리에 $가 모두 올라올 경우로 설정.
void stage_check_clear()
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
		a=0;
		stage_clear++;
	}
}


//게임 시작시 $의 개수와 O의 개수가 일치하지 않으면 종료하는 함수.
void stage_check_end()
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

	if(m!=o) // $랑 O가 일치하지 않으면 종료하는 부분.
	{
		printf("Error : map파일의 $와 O 개수가 동일하지 않습니다.\n");
		printf("프로그램을 종료합니다.");
		exit(-1); // main()함수가 아닌 함수에서 함수를 종료하는 exit(-1)함수.
	}
}


//게임종료시 축하메시지 출력 위한 함수.
void end()
{
	system("clear");
	printf("\n\n");
	printf("축하드립니다 %s 님 모든 스테이지를 클리어 하셨습니다.",name[n]);
	printf("\n");
}


//main 함수.
int main(void)
{
	mapscan(); // map.txt 스캔하여 map배열에 저장.
	stage_check_end(); // $랑 O 개수 미일치하는 맵이 있을 시 게임 종료.
	get_name(); // 이름 입력 받음.
	mapmemory(); // 새 게임시 초기화를 위해 초기맵을 따로 저장해둠.

	time(&start_time); // 시작할 때 시간 start_time 변수에 입력받음.

	while(1){
		replay_check = 1 ; // 움직인 상태를 뜻함.(map배열과 mapmemory배열이 달라지기 시작.)

		mapprint(); // keymove가 반영된 map배열을 while문 안에서 계속 출력.
		keyMove(); // while문 안에서 반복적으로 동작을 입력받음.

		search_hole(); // 반복적으로 보관함 자리 ' '으로 공백일 시 다시 O를 출력.
		stage_check_clear(); // 반복적으로 스테이지를 깼는지 검사.

		if(stage_clear == 5) // stage를 하나 깰 때마다 변수 stage_clear=0값을 하나씩 올려 5가 될 시 반복문을 탈출하게 함.
			break;
	}
	time(&end_time); // 끝나는 순간의 시간 end_time 변수에 입력받음.
	double d_diff = d_diff_stop + difftime(end_time, start_time); //게임시간(d_diff)을 저장. 이렇게 하는 이유는 중간에 세이브를 할 시 start_time이 한번 0이 됐다가 다시 시작하기 때문.

	//rank()

	end(); // 게임종료와 축하메시지 출력.
	printf("클리어에 걸린 시간 : %.1fsec",d_diff); // 클리어에 걸린 시간 출력.
	printf("\n\n");
	return 0;
}

// 파일로드 되면 이상하게 되는 부분 *****
// 파일로드를 동일한 이름만 할수 있게 하는 부분 ***
// 파일 로드 후 시간 문제 ****
// (Command) 문제.. **
// ranking 문제 *****
