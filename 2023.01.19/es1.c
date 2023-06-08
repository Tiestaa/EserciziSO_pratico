//18:00

//FILE* stream stdin


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFSIZE 1024
#define CMDSIZE 32
#define MAXPAR 32
#define MAXPARSIZE 64

int main(int argc, char* argv[]){
	char input[BUFSIZE];
	char* crtinput;
	char cmd[CMDSIZE];
	char* pmts[MAXPAR];
	char delim[] = " ";
	
	int len;
	int fdpipe[2];
	pipe(fdpipe);
	
	//dup2(fileno(stdin),fdpipe[1]);	//output -> mypipe
	
	if (fgets(input,BUFSIZE,stdin)== NULL){
		perror("first line error");
		return 0;
	}
	
	/* PARSE THE INPUT FILE */
	strcpy(cmd,strtok(input,delim));
	pmts[0] = malloc(CMDSIZE*sizeof(char));
	strcpy(pmts[0],cmd);
	
	int i= 0;
	while((crtinput=strtok(NULL,delim))!= NULL){
		pmts[++i] = malloc(MAXPARSIZE*sizeof(char));
		
		len = strlen(crtinput);
		
		strcpy(pmts[i],crtinput);	
	}
	pmts[i][len-1] = '\0';
	
	/* EXECUTE THE FIRST COMMAND*/
	if (fork() == 0){
		execvp(cmd,pmts);
		exit(1);
	}else
		wait(NULL);
		
	if (fgets(input,BUFSIZE,stdin) == NULL){
		perror("second line error");
		return 0;
	}
	
	/* PARSE THE INPUT FILE */
	strcpy(cmd,strtok(input,delim));
	pmts[0] = malloc(CMDSIZE*sizeof(char));
	strcpy(pmts[0],cmd);
	
	i=0;
	while((crtinput=strtok(NULL,delim))!= NULL){
		pmts[++i] = malloc(MAXPARSIZE*sizeof(char));
		
		len = strlen(crtinput);
		
		strcpy(pmts[i],crtinput);	
	}
	if (i!=0)pmts[i][len-1] = '\0';
	
	return 0;
}

//BOOOH IMPOSSIBILE
