#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char* argv[]){
	if (argc != 2 )	{
		perror("Invalid arguments number");
		return 0;
	}
	
	char* path = argv[1];
	
	
	//Uso lo lstat per verificare se si tratta di un link
	
	struct stat st;
	
	if (lstat(path, &st) < 0){
		perror ("stat error");
		return 0;
	}
	
	if (S_ISLNK(st.st_mode)){	//sono in un link simbolico.
		
		//prendo il path del file puntato
		char* realPF = realpath(path,NULL);
		
		char* originalLSPath = strdup(path);
		
		
		if (realPF == NULL){
			perror ("realpath error");
			return 0;
		}
		
		char* tmpRPF = strdup(realPF);
		char* dirPathFl = dirname(tmpRPF);	//path della directory in cui devo inserire il symlink
		tmpRPF = strdup(realPF);
		char* nameFl = basename(tmpRPF);
		
		char* tmpPath = strdup(path);
		char* nameLS =  basename(tmpPath);		//name del link simbolico
		tmpPath = strdup(path);
		char* dirPathLS = dirname(path);
		
		char newFlPath[PATH_MAX];
		memset(newFlPath, 0, PATH_MAX);
		
		sprintf(newFlPath, "%s/%s", dirPathLS, nameFl);
	
		
		//posso usare la rename per spostare il file.
		rename(realPF,newFlPath);	//sposto il file realPF nella cartella path
	
		
		char newLSPath[PATH_MAX];
		memset (newLSPath, 0, PATH_MAX);
		
		
		sprintf(newLSPath,"%s/%s", dirPathFl ,nameLS);
		
		symlink(realpath(newFlPath,NULL),newLSPath);	
		
		remove(originalLSPath);
	}
	return 0;
}
