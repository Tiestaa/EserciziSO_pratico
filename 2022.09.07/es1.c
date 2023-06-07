
// 15:30

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if (argc < 2){
		perror("invalid arguments number\n");
		return -1;
	}
	char* cmd = argv[1];
	char* newArgv[argc-1];
	for (int i = 0; i<argc-1;i++){
		newArgv[i]=argv[i+1];
	}
	newArgv[argc-1] = NULL;
	
	while (1){
		if (fork() == 0){
			if(execvp(cmd,newArgv)==-1){
				perror("execv error");
				break;
			}
		}
		
	}
	return 0;
}

//17:30


