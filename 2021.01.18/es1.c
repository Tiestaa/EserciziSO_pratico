//inizio: 15:15

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	if (argc != 2){
		perror("invalid arguments number");
		return 0;
	}
	DIR* dir;
	if ((dir = opendir(argv[1])) == NULL){
		perror("opendir error");
		return 0;
	}
	
	struct dirent* dent;
	
	while((dent = readdir(dir)) != NULL){
			//controllo se la dent sia un link simbolico
		if (dent -> d_type == DT_LNK){
			//devo rimuovere link simbolico, creare uno nuovo con lo stesso nome ma che sia sul path assoluto
			char* slname = strdup(dent-> d_name);
			
			//devo prendere il realpath. Dunque devo ricostruire tutto il path al link simbolico
			char fullSlPath[PATH_MAX];
			sprintf(fullSlPath,"%s/%s",argv[1],slname);
			
			char* flPath = realpath(fullSlPath,NULL);
			
			//ora devo rimuovere il link simbolico attuale e inserire uno equivalente che usi il path assoluto
			
			if (remove(fullSlPath) < 0){
				perror("remove error");
				return 0;
			}
			
			if ((symlink(flPath,fullSlPath)) < 0){
				perror("symbolic link creation error");
				return 0;
			}
		}
	}
}

// 15:33

