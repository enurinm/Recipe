#include <errno.h>
#include <unistd.h>
#define BLKSIZE 1024
#include <stdio.h>



int copyfile(int fromfd, int tofd) {
	char *bp;
	char buf[BLKSIZE];
	int bytesread, byteswritten = 0;
	int totalbytes = 0;
	
	for( ; ; ){
		while(((bytesread = read(fromfd, buf, BLKSIZE)) == -1) && (errno == EINTR));  // 시그널에 의한 인터럽트를 다룸
		if(bytesread <= 0) break; //fromfd에서의 실제 에러나 파일의 끝 //ctrl+D도 해당되는가???? 물어보기
		bp = buf;
		while(bytesread > 0){
			while(((byteswritten = write(tofd, bp, bytesread))== -1) && (errno == EINTR));  //시그널에 의한 인터럽트 다룸
			if(byteswritten <= 0) break;  //tofd에서 실제 에러
			totalbytes += byteswritten;
			bytesread -= byteswritten;
			bp += byteswritten;

		}
	
		if(byteswritten == -1) break;
	}
	return totalbytes;


}
