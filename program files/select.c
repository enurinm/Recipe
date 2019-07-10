#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <termios.h>

#define _CRT_SECURE_NO_WARNINGS
#define BUFF_SIZE 1024

int getch(){
    
	struct termios oldt, newt;
    	int ch;

    	tcgetattr( STDIN_FILENO, &oldt );

    	newt = oldt;
    	newt.c_lflag &= ~( ICANON | ECHO );
    	tcsetattr( STDIN_FILENO, TCSANOW, &newt );

    	ch = getchar();
    	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    	return ch;
}

char *get_recipenum(){
	int c;
	int num;
	char line[10]={0};
	char *str = malloc(sizeof(char)*20);
	int i=0;
	
	c=getch();

	//if(c==27) 메인 페이지로 돌아가기
	//if(다른 키라면)
	
	if(c>=49 && c<=57){		// getch() 입력이 숫자이면

		while(c!=10){		// 엔터키 입력시
			printf("%c",c);
			line[i]=c;
			i++;
			c=getch(); 
		}
	}
	strcpy(str, line);
	return str;

}

void recipe_select(){
	
	int fd;				// filedes
	char dir[100]="./recipe/";
	char txt[10]=".txt";
	char *recipenum;
	
	recipenum = get_recipenum();
	
	strcat(recipenum, txt);
	strcat(dir, recipenum);		// dir = dir + 입력받은 숫자(recipenum) + .txt (const char *path에 사용)
	


	
	if((fd=open(dir,O_RDONLY))>0){
	//	printf("\n%s",dir);		// 디렉토리 표시 테스트용. 지우고 next() 사용
		recipie_next(dir,O_RDONLY);
		free(recipenum);
		close(fd);
	}

	else{
		printf("Recipe number unexist.\n");	// 찾는 파일 없을 경우 다시 실행
		free(recipenum);
		recipe_select();
		close(fd);
	}

}

/*
int main(){

	recipe_select();

	return 0;
}


*/












	

	
