#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<termio.h>
#define N 30
#define M 11
int map[5][N][N];//전역 변수
int name[10]; //이름받을때 쓰는거
int getch()//실습09 7번문제
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

int main(void)
{
	char name[M] = " ";
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
    system("clear");
	printf("Hello %s",name);
	printf("\n");

    _Bool game =1; //게임 시작-게임 정지후 다시 시작할때, 새로운 게임 시작할때 필요
    while (game){ //rank 5개 저장
    	int rank[5];
		int i, j, tmp;
		time_t start_time, final_time; //게임실행 시간 계산
        long long gap_time;
		FILE *out; //게임실행시간을 rank 파일에 저장
		out = fopen("rank", "a");
        time(&start_time); //게임 시작 시간
        printf("123354656789876543245267"); //게임 실행코드 입력
		time(&final_time); //게임 종료 시간
        gap_time = start_time - final_time;
		if(gap_time>rank[4]) // 새로운 기록(시간)을 기존에 저장되어있던 기록중 가장 낮은 기록과 비교하여 걸린시간이 더 짧으면 인덱스에 저장 or 걸린시간이 더 길면 값을 버림
			rank[4] = gap_time;
		for(i=0; i<4; i++) //저장된 인덱스 값들을 버블로 다시 정렬
			for(j=4; j>i; j--)
				if(rank[j-1] > rank[j]){
					tmp = rank[j-1];
					rank[j-1] = rank[j];
					rank[j] = tmp;
				}
		fclose(out);
		return 0;
	}
	return 0;
}

