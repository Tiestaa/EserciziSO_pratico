#include <unistd.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){

	int status;
	prctl(PR_SET_CHILD_SUBREAPER,1,0,0,0);
	//in questo modo i miei figli mi vedono come se fossi l'init
	prctl(PR_SET_NAME, "nonno",0,0,0);
	
	pid_t pid[2] = {0};
	// 0-> figlio, 1 -> nipote
	
	int child2parent[2];
	pipe(child2parent);
	
	if ((pid[0] = fork()) == 0){
		//sono nel figlio
		prctl(PR_SET_NAME, "figlio",0,0,0);
		int IDp;
		
		if ((IDp=fork()) == 0){
			//sono nel nipote
			//nipote deve diventare orfano
			prctl(PR_SET_NAME, "nipote",0,0,0);
			sleep(30);
			exit(status);
		}
		
		else{
			write(child2parent[1], &IDp, sizeof(pid_t));
			//figlio deve subito morire
			sleep(10);
			exit(status);
		}
		
	}
	read(child2parent[0],&pid[1],sizeof(pid_t));
	printf("PID figlio: %d\tPID nipote: %d\n", pid[0], pid[1]);
	
	if (wait(&status) == pid[0]){
		printf("figlio(PID: %d) e' terminato\n", pid[0]);
		if (wait(&status) == pid[1]){
			printf("nipote(PID: %d) e' terminato\n", pid[1]);
		}
	}

	prctl(PR_SET_CHILD_SUBREAPER,0,0,0,0);
	return 0;
}
