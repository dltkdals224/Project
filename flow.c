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
_Bool whole_game =1;

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
    double d_diff1, d_diff2, d_diff3, d_diff4, d_diff5, d_diff_all;
    
	while(whole_game){
		_Bool game1=1, game2=1, game3=1, game4=1, game5=1;
	    time_t start_time, end_time;
	    double difftime(end_time, start_time);
	    
		get_name();
	    system("clear");
	    printf("\n\n");

	    mapscan();
	    
		mapprint1();
	    while(game1){
		    int rank_1[5];
		    int tmp, i, j;
		
		    while(1){
		    time(&start_time);
		
		    keyMove();
		    mapprint1();

		    break; //게임을 완료할 조건 입력
			}
		    time(&end_time);
	 	    d_diff1 = difftime(end_time, start_time);
        
		    if(rank_1[4]<d_diff1)
		        rank_1[4] = d_diff1;
        
		    for(i=0; i<4; i++)
                for(j=4; j>i; j--)
                    if(rank_1[j-1]>rank_1[j]){
                        tmp = rank_1[j-1];
                        rank_1[j-1]= rank_1[j];
                        rank_1[j]=tmp;
					}
		
		    FILE *out;
		    out = fopen("ranking", "w");
		    for(i=0; i<5; i++)
			    fprintf(out, "%d\n", rank_1[i]);
		    fclose(out);
		    return 0;
		}
		start_time =0;
        end_time=0;

        mapprint2();
        while(game2){
            int num_2[5];
		    int tmp, i, j;
		
		    while(1){
            time(&start_time);

            keyMove();
            mapprint2();

            break; //게임을 완료할 조건 입력
			}
            time(&end_time);
            d_diff2 = difftime(end_time, start_time);
		
		    if(num_2[4]<d_diff2)
                num_2[4] = d_diff2;
            for(i=0; i<4; i++)
                for(j=4; j>i; j--)
                    if(num_2[j-1]>num_2[j]){
                        tmp = num_2[j-1];
                        num_2[j-1]= num_2[j];
                        num_2[j]=tmp;
					}
			FILE *out;
            out = fopen("ranking", "w");
            for(i=0; i<5; i++)
                fprintf(out, "%d\n", num_2[i]);
            fclose(out);
            return 0;
		}
        start_time =0;
        end_time=0;

	    mapprint3();
        while(game3){
            int num_3[5];
		    int tmp, i, j;
		 
		    while(1){
            time(&start_time);

            keyMove();
            mapprint3();

            break; //게임을 완료할 조건 입력
			}
            time(&end_time);
            d_diff3 = difftime(end_time, start_time);
		  
		    if(num_3[4]<d_diff3)
                num_3[4] = d_diff3;
            for(i=0; i<4; i++)
                for(j=4; j>i; j--)
                    if(num_3[j-1]>num_3[j]){
                        tmp = num_3[j-1];
                        num_3[j-1]= num_3[j];
                        num_3[j]=tmp;
					}
            FILE *out;
            out = fopen("ranking", "w");
            for(i=0; i<5; i++)
                fprintf(out, "%d\n", num_3[i]);
            fclose(out);
            return 0;
		}
        start_time =0;
        end_time=0;

	    mapprint4();
	    while(game4){
		    int num_4[5];
		    int tmp, i, j;
		 
		    while(1){
			time(&start_time);

            keyMove();
            mapprint4();

            break; //게임을 완료할 조건 입력
			}
            time(&end_time);
            d_diff4 = difftime(end_time, start_time);
		   
		    if(num_4[4]<d_diff4)
                num_4[4] = d_diff4;
            for(i=0; i<4; i++)
                for(j=4; j>i; j--)
                    if(num_4[j-1]>num_4[j]){
                        tmp = num_4[j-1];
                        num_4[j-1]= num_4[j];
                        num_4[j]=tmp;
					}
            FILE *out;
            out = fopen("ranking", "w");
            for(i=0; i<5; i++)
                fprintf(out, "%d\n", num_4[i]);
            fclose(out);
            return 0;
		}
        start_time =0;
        end_time=0;

	    mapprint5();
	    while(game5){
		    int num_5[5];
		    int tmp, i, j;
		 
		    while(1){
			time(&start_time);

 			keyMove();
            mapprint5();

            break; //게임을 완료할 조건 입력
			}
            time(&end_time);
            d_diff5 = difftime(end_time, start_time);
			
			if(num_5[4]<d_diff5)
                num_5[4] = d_diff5;
            for(i=0; i<4; i++)
                for(j=4; j>i; j--)
                    if(num_5[j-1]>num_5[j]){
                        tmp = num_5[j-1];
                        num_5[j-1]= num_5[j];
                        num_5[j]=tmp;
					}
            FILE *out;
            out = fopen("ranking", "w");
            for(i=0; i<5; i++)
                fprintf(out, "%d\n", num_5[i]);
            fclose(out);
            return 0;
		}
        start_time =0;
        end_time=0;
	}
    d_diff_all = d_diff1 + d_diff2 + d_diff3 + d_diff4 + d_diff5; //전체 게임 실행 시간 계산
	printf("축하메세지 출력");
	return 0;
}
