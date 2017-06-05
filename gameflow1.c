#include<stdio.h>
#include<stdlib.h> //system()함수쓸때 필요
#include<time.h> //시간함수
#include<unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
int map[5][N][N];//전역 변수
int name[10]; //이름받을때 쓰는거
int p_map[30][30];
int x,y;
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
int scanchar(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(map[0][i][j]=='@'){
				x=j;
				y=i;
			}
	return 0;
}

int arrange(){

        static int a,b;        
	static int arrange[0][N][N];

        for(int y=0;y<N;y++)
		for(int x=0;x<N;x++)
			if(map[0][y][x]=='O'){
				a=x;
				b=y;
	                         
			}
	return 0;
}

void keyMove(){
	int key;
	scanchar();
	key=getch();

	system("clear");
	

	switch(key){
		case 'h':
			if(map[0][y][x-1] == '$'){
				if(map[0][y][x-2] == ' '){
					if(arrange[0][y][x]=='O')
						map[0][y][x]='O';
					        map[0][y][x-2]='$';
						map[0][y][x-=1]='@';
					else
						map[0][y][x-2]='$';
					        map[0][y][x]=' ';
					        map[0][y][x-=1]='@';
				}
				else if(map[0][y][x-2] == 'O'){
					if(arrange[0][y][x]=='O')
						map[0][y][x]='O';
					        map[0][y][x-2]='$';
						map[0][y][x-=1]='@';
					else
						map[0][y][x-2]='$';
					        map[0][y][x]=' ';
					        map[0][y][x-=1]='@';
				}
			}
			else if(map[0][y][x-1] == 'O'){
				if(arrange[0][y][x]=='O')
					map[0][y][x]='O';
					map[0][y][x-=1]='@';
			        else
					map[0][y][x-=1]='@';
			                map[0][y][x]=' '; 	
			}

			else if(map[0][y][x-1] == ' '){
				if(arrange[0][y][x]=='O')
					map[0][y][x]='O';
				        map[0][y][x-=1]='@';
				else
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
	system("clear");
	mapscan();

	mapprint();
	while(1){
		keyMove();
		mapprint();
	}
	return 0;
}


