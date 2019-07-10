


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void r_flusht(void) ;

void recipie_next(const char *path,int flag){ 
	int x=0;
	char rbuf[100];
	
	int fildes=open(path,flag);
	x=recipie(rbuf,-2,fildes);
	
	if(x==1){  
		printf("Come back to the main screen.\n");
		return;
	}
}


int recipie(char *rbuf,int bytesread,int fildes){ 
	char c;
	int i;

	 if((bytesread==-1)||(bytesread==0)){
                printf("End of the recipie.\n");
                return 0;
        	}

	printf("\nDo you want to see the next recipie? (y/n)");
	scanf("%c",&c);
	r_flusht();
	
	for(i=0;i<bytesread;i++){
		rbuf[i]='\0';
	}
	
	if((c=='y')||(c=='Y')){
		bytesread=readline(fildes,rbuf,99);
		printf("%s\n",rbuf);
		recipie(rbuf,bytesread,fildes);
		
	}
	else if((c=='n')||(c=='N')){
		printf("Close the recipie.\n");
		return 1;
	}
	else{
		printf("Wrong enterance.\n");
		recipie(rbuf,bytesread,fildes);
	}

	

}


int readline(int fd, char *buf, int nbyte)
{
        int numread = 0;
        int returnval;

        while(numread < nbyte - 1)
        {
	//	while (returnval = read(fd, buf+numread, 1), returnval==-1 && errno==EINTR);
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
}

void r_flusht() 
{ 
   int temp = 0; 
   while (temp != '\n' && temp !=EOF) 
   temp = getchar(); 
}
