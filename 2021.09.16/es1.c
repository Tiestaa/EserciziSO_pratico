#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdlib.h>

#define MAXBUFSZ sizeof(struct inotify_event) + NAME_MAX + 1
#define MAXPAR 16
#define APICE 39


/*https://stackoverflow.com/questions/9895216/how-to-remove-all-occurrences-of-a-given-character-from-string-in-c*/

void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

int main(){
	
	if (mkdir("./exec",0777) < 0){
		perror("mkdir error\n");
		return 0;
	}
	
	int fd;
	if ((fd = inotify_init()) < 0){
		perror("inotify error\n");
		return 0;
	}
	
	int wd;
	if ((wd = inotify_add_watch(fd,"./exec",IN_CREATE))< 0){
		perror("addwath error\n");
		return 0;
	}
	
	struct inotify_event inev;
	char* flname;
	char delim[] = " ";
	char c2rm = (char) APICE;
	
	read(fd,&inev,MAXBUFSZ);
	if (inev.wd == wd && inev.mask == IN_CREATE){
		char* allName = strdup(inev.name);
		flname = strdup(inev.name);
		remove_all_chars(flname,c2rm);
		//parsing della stringa per prendere comando e parametri
		
		char* token = strtok(flname, delim);
		char* cmd = strdup(token);
		char* argv[MAXPAR];
		int i =	0;
		while(token != NULL){
			argv[i++] = strdup (token);
			token = strtok(NULL, delim);
		}
		
		/* esecuzione del codice */
		if (fork() == 0){
			execvp(cmd,argv);
			exit (0);
		}
		else{
			wait(NULL);
			//rimozione del file una volta utilizzato
			char fullPath[PATH_MAX];
			sprintf(fullPath,"%s/%s","./exec", allName);
			remove(fullPath);
			printf("\nfullPath da rimuovere: %s\n", fullPath);
		}
	}
	
	inotify_rm_watch(fd,wd);
	rmdir("./exec");
	return 0;
}

//FINITO, un'ora
//unico problema: che delimitatore uso??
