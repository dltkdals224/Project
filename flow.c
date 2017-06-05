#include<stdio.h>
#include <stdlib.h>//system()함수에 필요
#include <time.h>
#include <unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
int map[5][N][N];//전역변수
#define M 11
int name[10]; //이름받을때 쓰는거
int p_map[30][30];
int x=0, y=0, z=0, i;
void get_name()
{
    char name[M] = "";
	int i=0,a;
	printf("Start....\n input name : ");
	while(1){
	    a = getchar();
		if(i==M){
		    while((a=getchar()) != '\n')
				;
				printf("1자 이상 10자 이하의 이름을 입력해 주세요 : ");
				i = 0;
				continue;
		}
		if((a =='\n')||(a == EOF)) {
			name[i++] = '\0';
			break;
		}
		name[i++] = a;
	}
	printf("Hello %s", name);
}

int scanchar(){ //현재 위치 찾는 함수
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(map[0][i][j]=='@'){
				x=j;
				y=i;
			}
	return 0;
}

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

void keyMove()
{
	int key;
	scanchar();
	key=getch();

	system("clear");

	switch(key){
		case 'h':
			if(map[0][y][x-1] == '$'){
				if(map[0][y][x-2] == ' '){
					map[0][y][x-2]='$';
					map[0][y][x]=' ';
					map[0][y][x-=1]='@';
				}
				else if(map[0][y][x-2] == 'O'){
					map[0][y][x-2]='$';
					map[0][y][x]=' ';
					map[0][y][x-=1]='@';
				}
			}
			else if(map[0][y][x-1] == 'O'){
				map[0][y][x]='O';
				map[0][y][x-=1]='@';
			}
			else if(map[0][y][x-1] == ' '){
				map[0][y][x]=' ';
				map[0][y][x-=1]='@';
			}
			break;

		case 'j':
			if(map[0][y+1][x] == '$'){
				if(map[0][y+2][x] == ' '){
					map[0][y+2][x]='$';
					map[0][y][x]=' ';
					map[0][y+=1][x]='@';
				}
				else if(map[0][y+2][x] == 'O'){
					map[0][y+2][x]='$';
					map[0][y][x]=' ';
					map[0][y+=1][x]='@';
				}
			}
			else if(map[0][y+1][x] == 'O'){
				map[0][y][x]='O';
				map[0][y+=1][x]='@';
			}
			else if(map[0][y+1][x] == ' '){
				map[0][y][x]=' ';
				map[0][y+=1][x]='@';
			}
			break;

		case 'k':
			if(map[0][y-1][x] == '$'){
				if(map[0][y-2][x] == ' '){
					map[0][y-2][x]='$';
					map[0][y][x]=' ';
					map[0][y-=1][x]='@';
				}
				else if(map[0][y-2][x] == 'O'){
					map[0][y-2][x]='$';
					map[0][y][x]=' ';
					map[0][y-=1][x]='@';
				}
			}
			else if(map[0][y-1][x] == 'O'){
				map[0][y][x]='O';
				map[0][y-=1][x]='@';
			}
			else if(map[0][y-1][x] == ' '){
				map[0][y][x]=' ';
				map[0][y-=1][x]='@';
			}
			break;

		case 'l':
			if(map[0][y][x+1] == '$'){
				if(map[0][y][x+2] == ' '){
					map[0][y][x+2]='$';
					map[0][y][x]=' ';
					map[0][y][x+=1]='@';
				}
				else if(map[0][y][x+2] == 'O'){
					map[0][y][x+2]='$';
					map[0][y][x]=' ';
					map[0][y][x+=1]='@';
				}
			}
			else if(map[0][y][x+1] == 'O'){
				map[0][y][x]='O';
				map[0][y][x+=1]='@';
			}
			else if(map[0][y][x+1] == ' '){
				map[0][y][x]=' ';
				map[0][y][x+=1]='@';
			}
			break;
	}
}

int main(void)
{
    get_name();
	system("clear");
	printf("\n\n"); //get_name 함수호출 후 clear 실행했는데 "Hello 이름"이 찍힌다...

	mapscan();
	mapprint1();
	while(1){
		keyMove();
		mapprint1();
	}
	return 0;
}
