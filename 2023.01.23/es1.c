
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc, char* argv[]){
	if (argc != 2){
		perror("Invalid Arguments\n");
		exit(-1);
	}
	
	int fd;
	char* fifo = argv[1];
	
	if (mkfifo(fifo,0666)<0){
		perror("impossible to create a pipe\n");
		exit(-1);
	}
	
	fd = open(fifo, O_RDONLY );
	
	char buf[BUFSIZE];

	while(1){
		memset(buf,0,BUFSIZE);	//SVUOTA IL BUFFER
		if (read(fd,buf,BUFSIZE) > 0){
			if ( strcmp("FINE\n", buf) == 0)
				break;
				
			else
				printf(buf);
		}
	}
	close(fd);
	remove(fifo);
	return 0;
}
