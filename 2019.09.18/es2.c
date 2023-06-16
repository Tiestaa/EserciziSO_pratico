#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define MAXPARAM 16


int main(int argc, char* argv[]){
	if (argc < 2){
		perror("Invalid arguments number");
		exit(0);
	}
	
	int status = 0;
	pid_t wpid;
	
	int cmdIndex = 0;
	char* curcmd[MAXPARAM];
	
	int maxCmd = atoi(argv[1]);
	int activecmd = 0;
	
	for (int i = 2; i < argc; i++){
	
		if (activecmd == maxCmd) {
			wait(NULL);
			activecmd--;
		}
		if (strcmp(argv[i],"//") == 0 || strcmp(argv[i],"// ") == 0){
			if (fork() == 0){
				activecmd++;
				execvp(curcmd[0], curcmd);
				exit(0);
			}
			cmdIndex = 0;
			
			continue;
		}
		
		curcmd[cmdIndex++] = strdup(argv[i]);
	}
	
	while((wpid = wait(NULL) ) > 0)
		;
	return 0;
}
