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

	//if(c==27) ���� �������� ���ư���
	//if(�ٸ� Ű���)
	
	if(c>=49 && c<=57){		// getch() �Է��� �����̸�

		while(c!=10){		// ����Ű �Է½�
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
	strcat(dir, recipenum);		// dir = dir + �Է¹��� ����(recipenum) + .txt (const char *path�� ���)
	


	
	if((fd=open(dir,O_RDONLY))>0){
	//	printf("\n%s",dir);		// ���丮 ǥ�� �׽�Ʈ��. ����� next() ���
		recipie_next(dir,O_RDONLY);
		free(recipenum);
		close(fd);
	}

	else{
		printf("Recipe number unexist.\n");	// ã�� ���� ���� ��� �ٽ� ����
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












	

	
