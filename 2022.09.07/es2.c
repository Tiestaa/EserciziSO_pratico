#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	if (argc < 2){
		perror("invalid arguments number\n");
		return -1;
	}
	clock_t start;
	clock_t end;
	char* cmd = argv[1];
	char* newArgv[argc-1];
	for (int i = 0; i<argc-1;i++){
		newArgv[i]=argv[i+1];
	}
	newArgv[argc-1] = NULL;
	
	while (1){
		start = clock();
		if (fork() == 0){
			if(execvp(cmd,newArgv)==-1){
				perror("execv error");
				break;
			}
			exit(0);
			
		}
		else{
			wait(NULL);
		}
		end = clock();
		if(((float)(end - start) / CLOCKS_PER_SEC) < 1)
			break;
	}
	return 0;
}

