#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#ifndef PATH_MAX 
#define PATH_MAX 255
#endif

int  print(const char *dirname)
{
	DIR *dirp;
	struct dirent *direntp;
	int fd;
	char buf[20];
	char tmp[50];
	char mycwd[PATH_MAX];
	if((dirp = opendir(dirname))==NULL)
	{
		perror("Failed to open directory");
		return 1;
	}
	if(getcwd(mycwd, PATH_MAX) == NULL){
		perror("Failed to get current working directory");
		return 1;
	}
	else{
		strcat(mycwd, "/");
		strcat(mycwd, dirname);
		strcat(mycwd, "/");
	}
	while((direntp = readdir(dirp)) != NULL)
	{
		if(strcmp(direntp->d_name,".")== 0) continue;
		else if(strcmp(direntp->d_name,"..")==0) continue;
		else
		{	
			printf("%s\t", direntp->d_name);
			strcpy(tmp,mycwd);
			strcat(tmp, direntp->d_name);
			if((fd = open(tmp, O_RDONLY))==-1)
			{
				perror("Failed to open file");
				return 1;
			}
			while((readline(fd,buf,sizeof(buf)) == -1) && (errno == EINTR));
			printf("%s\n", buf);
			while((close(fd)==-1) && (errno == EINTR));
		}
	}
	while((closedir(dirp) == -1) && (errno == EINTR));
	return 0;
}
/*
int readline(int fd, char *buf, int nbyte)
{
	int numread = 0;
	int returnval;
	
	while(numread < nbyte - 1)
	{
		returnval = read(fd, buf+numread, 1);
		if((returnval == -1) && (errno == EINTR)) continue;
		if((returnval == 0) && (numread == 0)) return 0;
		if(returnval == 0) break;
		if(returnval == -1) return -1;
		numread++;
		if(buf[numread-1] == '\n')
		{
			buf[numread] = '\0';
			return numread;
		}
	}
	errno = EINVAL;
	return -1;
}*/
