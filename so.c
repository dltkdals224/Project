#include<stdio.h>
void keyMove();
void keyMove(){
	int key;
	int j=0;
	int i=0;

	key=getchar();

	switch(key){
		case 'h':
			j--;
			break;
			
		case 'j':
			i++;
			break;

		case 'k':
			i--;
			break;

		case 'l':
			j++;
			break;
	}

	if(map[0][j+1][i]=='#'||map[0][j+1][i]=='O'||map[0][j-1][i]=='#'||map[0][j-1][i]=='O'||map[0][j][i+1]=='#'||map[0][j][i+1]=='O'||map[0][j][i-1]=='#'||map[0][j][i-1]='O'){
		map[0][j][i]=='@';}
	
	else if(map[0][j+1][i]=='$'){
		if(map[0][j+2][i]=='O'){
			map[0][j+2][i]=='$';
			map[0][j+1][i]=='@';
		}
		if(map[0][j+2][i]==' '){
		        map[0][j+2][i]=='$';
			map[0][j+1][i]=='@';
		}
	        if(map[0][j+2][i]=='#'||map[0][j+2][i]=='O'){
			map[0][j][i]=='@';
			map[0][j+1][i]=='$';
		}}

        
	else if(map[0][j-1][i]=='$'){
		if(map[0][j-2][i]=='O'){
			map[0][j-2][i]=='$';
			map[0][j-2][i]=='@';
		}
		if(map[0][j-2][i]==' '){
		        map[0][j-1][i]=='$';
			map[0][j-1][i]=='@';
		}
	        if(map[0][j-2][i]=='#'||map[0][j-2][i]=='O'){
			map[0][j][i]=='@';
			map[0][j-1][i]=='$';
		}}
		
	
	else if(map[0][j][i+1]=='$'){
		if(map[0][j][i+2]=='O'){
			map[0][j][i+2]=='$';
			map[0][j][i+1]=='@';
		}
		if(map[0][j][i+2]==' '){
		        map[0][j][i+2]=='$';
			map[0][j][i+1]=='@';
		}
	        if(map[0][j][i+2]=='#'||map[0][j][i+2]=='O'){
			map[0][j][i]=='@';
			map[0][j][i+1]=='$';
		}}

		
	else if(map[0][j][i-1]=='$'){
		if(map[0][j][i-2]=='O'){
			map[0][j][i-2]=='$';
			map[0][j][i-1]=='@';
		}
		if(map[0][j][i-2]==' '){
		        map[0][j][i-2]=='$';
			map[0][j][i-1]=='@';
		}
	        if(map[0][j][i-2]=='#'||map[0][j][i-2]=='O'){
			map[0][j][i]=='@';
			map[0][j][i-1]=='$';
		}}

	
	else if(map[0][j+1][i]==' '){map[0][j+1][i]=='@';}
        else if(map[0][j-1][i]==' '){map[0][j-1][i]=='@';}
	else if(map[0][j][i+1]==' '){map[0][j][i+1]=='@';}
	else if(map[0][j][i-1]==' '){map[0][j][i-1]=='@';}
		
}	
