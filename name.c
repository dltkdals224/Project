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
{        int ch;
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
	int i,a;
	printf("Start....\n input name : "); // 이름 10글자 이내로 입력받기 해결하기.
	i=0;
while(1){
a = getchar();
if(i==M)
{
	while((a = getchar()) != '\n')
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
printf("Hello %s",name);
return 0;
}
// 문제발생 : 이름을 정확히 11자 입력했을시 엔터를 한번더 작성해야하는 버퍼발생
