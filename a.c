#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<termio.h>
#define N 30
#define M 11

void stage_check();
void search_hole();
void file_save();

int replay_check =0;
int undo[5][N][N];
char map_memory [5][N][N];
int map[5][N][N];
char name[10];
int p_map[30][30];
int x=0, y=0, z=0, i;
time_t start_time, end_time;
char key;

int rank_1[5];
double d_diff1, d_diff2, d_diff3, d_diff4, d_diff5, d_diff_all;
double difftime(end_time, start_time);

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

//이름 입력 받는 함수
void get_name()
{
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
}

//맵 읽어들이기
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

//초기 맵 저장
int memory()
{
     if (replay_check == 0){
         for(int z=0; z<5; z++ )
             for(int y=0; y<N; y++ )
                 for(int x=0; x<N; x++)
                     map_memory[z][y][x] = map[z][y][x];
	 }
	 x=0,y=0,z=0;
 }

//캐릭터가 보관함을 먹어버릴때 보관함을 다시 찍어내는 함수
void search_hole()
{
    for(int z=0;z<5;z++)
        for(int y=0;y<N;y++)
            for(int x=0;x<N;x++){
                if (map_memory[z][y][x]=='O')
                    if (map[z][y][x]==' ')
                        map[z][y][x]='O';
			}
}

//map 출력 함수(거의 완성)
int mapprint1()
{
     int tmp, i, j;
	 int x,y,z=0;
     printf("Hello %s", name);
     for(int y=0;y<N;y++){
         for(int x=0;x<N;x++)
             printf("%c",map[z][y][x]);
	 }
     for(int y=0;y<N;y++)
         for(int x=0;x<N;x++){
             if (map_memory[z][y][x]=='O')
                 if (map[z][y][x]=='$'){
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
					 
                     start_time =0;
					 end_time=0;
					 mappprint2();
				 }
     return 0;
}

int mapprint2()
{
     int tmp, i, j;
	 int x,y,z=1;
     printf("Hello %s\n\n", name);
     for(int y=0;y<N;y++){
         for(int x=0;x<N;x++)
             printf("%c",map[z][y][x]);
         printf("\n");
     }
     for(int y=0;y<N;y++)
         for(int x=0;x<N;x++){
             if (map_memory[z][y][x]=='O')
                 if (map[z][y][x]=='$'){
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

                     start_time =0;
                     end_time=0;
                     mapprint3();
				 }
     return 0;
}

int mapprint3()
{
     int x,y,z=2;
     printf("Hello %S\n\n", name);
     for(int y=0;y<N;y++){
         for(int x=0;x<N;x++)
             printf("%c",map[z][y][x]);
         printf("\n");
     }
     for(int y=0;y<N;y++)
         for(int x=0;x<N;x++){
             if (map_memory[z][y][x]=='O')
                 if (map[z][y][x]=='$')
                     mapprint4();
		 }
     return 0;
}

int mapprint4()
{
     int x,y,z=3;
     printf("Hello %s\n\n", name);
     for(int y=0;y<N;y++){
         for(int x=0;x<N;x++)
             printf("%c",map[z][y][x]);
         printf("\n");
     }
     for(int y=0;y<N;y++)
         for(int x=0;x<N;x++){
             if (map_memory[z][y][x]=='O')
                 if (map[z][y][x]=='$')
                     mapprint5();
		 }
     return 0;
}

int mapprint5()
{
     int x,y,z=4;
     printf("Hello %s\n\n", name);
     for(int y=0;y<N;y++){
         for(int x=0;x<N;x++)
             printf("%c",map[z][y][x]);
         printf("\n");
     }
     return 0;
}

//현재 캐릭터위치 찾는 함수
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

void map1()
{
    time(&start_time);
    keyMove();
	mapprint1();
}

void map2()
{
    while(game2){
            int num_2[5];
            int tmp, i, j;
            while(1){
            time(&start_time);
            while(1){
                replay_check =1;
                keyMove();
                mapprint2();
                search_hole();
                stage_check();
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
        }
        start_time =0;
        end_time=0;
    }
}
void map3()
{
     while(game3){
             int num_3[5];
             int tmp, i, j;

             while(1){
             time(&start_time);

             while(1){
                 replay_check=1;

                 keyMove();
                 mapprint3();
                 search_hole();
                 stage_check();
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
         }
         start_time =0;
         end_time=0;
     }
}
void map4()
{
     while(game4){
             int num_4[5];
             int tmp, i, j;

             while(1){
             time(&start_time);

             while(1){
                 replay_check=1;

                 keyMove();
                 mapprint4();
                 search_hole();
                 stage_check();
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
         }
         start_time =0;
         end_time=0;
     }
}

void map5()
{
     while(game5){
             int num_5[5];
             int tmp, i, j;

             while(1){
             time(&start_time);

             while(1){
                 replay_check =1;

                 keyMove();
                 mapprint5();
                 search_hole();
                 stage_check();
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
         }
         start_time =0;
         end_time=0;
     }
}
//보관함 개수 세는 함수
void search_hole()
{
     for(int z=0;z<5;z++)
         for(int y=0;y<N;y++)
             for(int x=0;x<N;x++){
                 if (map_memory[z][y][x]=='O')
                     if (map[z][y][x]==' ')
                         map[z][y][x]='O';
             }
}

//다음 단계로 넘어가는 함수
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

//게임을 완수했는지 알아보는 함수
void stage_check()
{
     int i=0;//필요개수 충족위해 필요 변수
     int o=0;//맵별 똥그라미 개수

     for(int y=0;y<N;y++)
         for(int x=0;x<N;x++)
             if(map_memory[0][y][x]=='O')
                 o++;
         for(int y=0;y<N;y++)
             for(int x=0;x<N;x++){
                 if (map_memory[0][y][x]=='O')
                     if (map[0][y][x]=='$')
                         i++;
             }
         if(i==o)
             next_stage();
}

//이동 키
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
         case 's': //
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
                 map[0][y][x]=' ';
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
                 map[0][y][x]=' ';
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
                 map[0][y][x]=' ';
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
                 map[0][y][x]=' ';
                 map[0][y][x+=1]='@';
                 }
             else if(map[0][y][x+1] == ' '){
                 map[0][y][x]=' ';
                 map[0][y][x+=1]='@';
             }
            break;
     }
}


100 void undo_scan()
101 {
102     for(int y=0; y<N; y++)
103     for(int x=0; x<N; x++){
104         undo[4][y][x]= undo[3][y][x];
105         undo[3][y][x]= undo[2][y][x];
106         undo[2][y][x]= undo[1][y][x];
107         undo[1][y][x]= undo[0][y][x];
108         undo[0][y][x]= map[z][y][x];
109     }
110 }

//////파일 저장하기(미완성)
403 void file_save()
404 {
405     time_t stop_time;
406     time(&stop_time);
407     //double difftime(stop_time,start_time);
408     double d_diff_stop = difftime(stop_time,start_time);
409
410     FILE *file_save;
411     file_save=fopen("sokoban.txt","w");
412
413     fprintf(file_save,"%s",name);  //이름
414     fprintf(file_save," ");
415
416     fprintf(file_save,"%.1f",d_diff_stop); //시간
417     fprintf(file_save,"\n");
418
419     for(int y=0;y<30;y++)
420         for(int x=0;x<30;x++)
421             fprintf(file_save,"%c",map[z][y][x]); //맵
422
423     fclose(file_save);
424 }
425
426 //////저장한 파일 불러오기(미완성)
427 void file_load()
428 {
429     FILE *file_save;
430     file_save=fopen("sokoban.txt","r");
431     double d_diff_stop;
432     char space;
433     for(int z=0;z<30;z++)
434         for(int y=0;y<30;y++)
435             for(int x=0;x<30;x++)
436                 fscanf(file_save,"%c",&map[z][y][x]);
437
438     fscanf(file_save,"%s %.1f", name, d_diff_stop);
439
440     fscanf(file_save,"%c",map[z][y][x]);
441     fclose(file_save);
442 }

//전체게임을 하는 데 걸리는 랭킹
void rank_game()
{
      int num_game[5];
      int tmp, i, j;

      d_diff_all = d_diff1 + d_diff2 + d_diff3 + d_diff4 + d_diff5;

      if(num_game[4]<d_diff_all)
          num_game[4] = d_diff_all;
      for(i=0; i<4; i++)
          for(j=4; j>i; j--)
              if(num_game[j-1]>num_game[j]){
                  tmp = num_game[j-1];
                  num_game[j-1]= num_game[j];
                  num_game[j]=tmp;
              }
}

