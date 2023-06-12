#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>

/*
https://stackoverflow.com/questions/29079011/copy-file-function-in-c   
** Function return value meaning
 * -1  error
 * 0 Success
 */
 
int File_Copy (char* FileSource, char* FileDestination){
    int   c;
    FILE *stream_R;
    FILE *stream_W; 

    stream_R = fopen (FileSource, "r");
    if (stream_R == NULL)
        return -1;
    stream_W = fopen (FileDestination, "w");   //create and write to file
    if (stream_W == NULL)
     {
        fclose (stream_R);
        return -2;
     }    
    while ((c = fgetc(stream_R)) != EOF)
        fputc (c, stream_W);
    fclose (stream_R);
    fclose (stream_W);

    return 0;
}


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
		
			char* slname = strdup(dent-> d_name);
			
			//devo prendere il realpath. Dunque devo ricostruire tutto il path al link simbolico
			char fullSlPath[PATH_MAX];
			sprintf(fullSlPath,"%s/%s",argv[1],slname);
			
			char* flPath = realpath(fullSlPath,NULL);
			
			if (remove(fullSlPath) < 0){
				perror("remove error");
				return 0;
			}
			
			//path del file copia con il nome
			char cpFlPath[PATH_MAX];
			//faccio una copia di flPath in quanto basename lo va a modificare
			char* tmp = strdup(flPath);
			
			sprintf(cpFlPath,"%s/%s",argv[1],basename(tmp));
			
			File_Copy(flPath, cpFlPath);
		}
	}
	return 0;
}


