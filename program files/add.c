#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

int add(void){


	int myfd; //요리법 쓸 파일
	int num;  //파일번호 파일
	char buf[10]; //filenum으로부터 읽어론 숫자 저장
	ssize_t bytesread; //filenum으로부터 읽어온 바이트 수 저장
//	char str[PATH_MAX];
	char str[]="./recipe/";
	char str2[100];
	
	strcpy(str2, str);
	int a; //파일 값 저장
	char wnum[10]; //정수를 문자열로 바꿀때 저장할 버퍼
	int foldcheck;

	if((foldcheck=mkdir("recipe", 0755))==-1);

	
	if((num = open("./filenum.txt", O_CREAT| O_RDWR, S_IRWXU))==-1)
	{
		perror("Failed to open file");
		return 1 ;
	}; //파일번호 파일 오픈
	while(((bytesread = read(num, buf,1))==-1) && (errno == EINTR)); //filenum read
	strcat(str2, buf);
	strcat(str2,".txt");

	if(((myfd = open(str2, O_CREAT| O_RDWR, S_IRWXU))==-1))
	{
		perror("Failed to open file");
		return 1;
	}  //요리법 쓸 파일 오픈
	copyfile(STDIN_FILENO,myfd);



	a= atoi(buf);
	a=a+1;
	sprintf(wnum, "%d", a);
	

	lseek(num, 0, SEEK_SET);




	while((write(num,wnum,1)==-1) && (errno == EINTR));
	while((close(num)==-1) && (errno == EINTR));
	while((close(myfd)==-1) && (errno == EINTR));
		

	return 0;
}
