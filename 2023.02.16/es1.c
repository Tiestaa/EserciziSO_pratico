/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Fare un programma di copia parallelo di file.
	pcp file1 file2
pcp deve creare due processi figli; mentre un processo copia la prima meta’ del file, l'altro deve
copiare l’altra meta’.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 3){
		perror("wrong input");
		return -1;
	}
	
	FILE* inputFile = fopen(argv[1],"r");
	FILE* outputFile = fopen(argv[2], "w");
		
		/* find middle of stream */
	
	fseek(inputFile, 0, SEEK_END);
	int size = ftell(inputFile);
	
	if (fork()==0){		//primo processo figlio, deve fare la copy della prima metà del file
		fseek(inputFile,0,SEEK_SET);
		do{
			fputc(fgetc(inputFile),outputFile);
		} while(ftell(inputFile) != (size/2));	//controllo SUS
	}
	
	else{
		if (fork() == 0){	//secondo processo figlio, deve fare la copu della seconda metà del file
			int curChar;
			fseek(inputFile, (size/2), SEEK_SET);
			fseek(outputFile,(size/2), SEEK_SET);
			while(1){
				curChar = fgetc(inputFile);
				if (curChar == EOF)			//se è EOF non lo copio ma esco direttamente
					break;
				fputc(curChar,outputFile);
			}
		}
	} 
	
	fclose(inputFile);		//chiusura dei file 
	fclose(outputFile);	
	return 0;
}

/*
	NON usare feof per loop
	https://stackoverflow.com/questions/4906341/why-do-i-get-a-%c3%bf-char-after-every-include-that-is-extracted-by-my-parser-c/4906442#4906442
*/
