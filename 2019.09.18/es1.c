#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define MAXPARAM 16


int main(int argc, char* argv[]){
	
	int status = 0;
	pid_t wpid;
	
	int cmdIndex = 0;
	char* curcmd[MAXPARAM];
	
	for (int i = 1; i < argc; i++){
		
		if (strcmp(argv[i],"//") == 0 || strcmp(argv[i],"// ") == 0){
			if (fork() == 0){
				printf("%s\n", curcmd[0]);
				execvp(curcmd[0], curcmd);
				exit(0);
			}
			cmdIndex = 0;
			continue;
		}
		
		curcmd[cmdIndex++] = strdup(argv[i]);
	}
	
	while((wpid = wait(&status) ) > 0)
		;
	return 0;
}
