//15:01

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPATHSIZE 1024


void printTree(char* file, int level){
	for(int i = 0; i < level; i++){
		printf("	");
	}
	printf("%s\n", file);
}

void exploreDir(char* path, int level){
	DIR* dir = opendir(path);
	int fdDir = dirfd(dir);
	struct dirent* dent;
	while ((dent = readdir(dir)) != NULL){
		if (strncmp(dent->d_name,".",1) == 0)
			continue;
		
		printTree(dent->d_name, level);

		if (dent->d_type == DT_DIR){		//è una directory
				/* full path */
			char fullPath[MAXPATHSIZE];
			strcpy(fullPath, path);
			strcat(fullPath, "/");
			strcat(fullPath, dent->d_name);
			exploreDir(fullPath, level+1);
		}
	}
}


int main(int argc, char* argv[]){
	if (argc < 2){
		perror("Invalid Arguments number");
		return 0;
	}
	
	char* path = argv[1];
	
	exploreDir(path,0);
	return 0;
}

//16:20
