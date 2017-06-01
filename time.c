#include <stdio.h>
#include <time.h> // 시간함수를 사용할 수 있게 해주는 헤더파일
int n; 
double d_diff; // start_time과 end_time의 차이를 difftime함수로 계산하여 d_diff에 대입.
int main(void)
{
time_t start_time, end_time; // time_t 는 시간에대한 형.
time(&start_time); // time() 시간 입력 함수 - &변수 로 시간을 저장.
printf("아무 수나 입력하세요 : ");
scanf("%d",&n);
printf("\n%d\n",n);
time(&end_time); // 마찬가지로 &변수로 시간 저장.
double difftime(end_time, start_time); //difftime 형과 변수 선언, 계산 (변수자리 딴거 넣어도 되는지 모르겠음)
d_diff = difftime(end_time, start_time); // d_diff에 두 시간의 차이 저장.
printf("소요된 시간 : %f",d_diff); //변환명세 %f로 출력.
return 0;
}
