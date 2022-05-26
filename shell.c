 /*
  * shell.c
  * 
  * Universidad del Valle
  * Escuela de Ingenieria de Sistemas y Computacion
  * Sistemas Operativos
  * Profesor John Alexander Sanabria Ph.D.
  * Presentado por Sebastian Afanador & David Crespo
  * 
  * Entreaga: Proyecto 1 - Shell
  * 
  * */

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>
 #include <string.h>
 #include <stdio_ext.h>
 #include <dirent.h>
 #include "aux.h"
 
int  main(int argc, char *argv[]){
	
	while(1){
		char c[maxLen];
		printf("\x1b[0m" "$ ");
		__fpurge(stdin);
		memset(c,'\0',maxLen);
		scanf("%[^\n]s",c);
		
		if (!strcmp("exit",c))break;
		
		pid_t pid = fork();
		if(!pid){
			if(isDeliver(c)){
				deliver(c);
			}else{
				if(isFastFood(c)){
					char **food = fastCook(prepare(c),dish());
					eatFast(food);
				}else{
					char ***food = cook(prepare(c),pot());
					eat(food);
				}	
			}
		}else wait(NULL);
		
	}	
 
	return 0;
 }

