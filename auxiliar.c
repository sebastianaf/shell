 /*
  * auxiliar.c
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
 #include <fcntl.h>
 #include <sys/stat.h>

int maxLen = 100;
int bowlSize = 2;
char*error="comando no valido";

/**
 * Valida si no hay mas letras depues
 * */
int isLast(char *c,int i){
	i++;
	for(;i<strlen(c);i++){
		if(c[i]!=' ')return 0;
	}return 1;
}

/**
 * Limpia los espacios sobrantes
 * */
char * prepare(char *c){
	int loops=2;
	char **b = malloc(sizeof(char*)*loops);
	for(int l=0;l<loops;l++){
		b[l] = malloc(sizeof(char)*maxLen);
	}
	int l=0;
	int i=0;
	int j=0;
	int s=0;
	for(;l<loops;l++){
		for(;i<strlen(c)&&c[i]!='>';i++){
			if(c[i]==' '){
				if(i!=0&&!isLast(c,i)&&s==0){
					b[l][j]=c[i];
					j++;
					s++;
				}
				s++;
				continue;
			}
			b[l][j]=c[i];
			j++;
			s=0;
		}
	b[l][j]='\0';
	c=b[l];
	i=0;
	j=0;
	
	}
	return b[l-1];
}


/**
 * Prueba si hay pipe o stream
 * */
int isFastFood(char * c){
	for(int i=0;i<strlen(c);i++){
		if(c[i]=='|')return 0;
	}
	return 1;
}

/**
 * Recipiente para un comando sencillo
 * */
char ** dish(){
	char ** b;
	b = malloc(sizeof(char*)*maxLen);
	for(int i=0;i<maxLen;i++){
		b[i]=malloc(sizeof(char)*maxLen);
	}
	return b;
}

/**
 * Recipiente para un comando con pipe
 * */
char *** pot(){
	char *** b;
	b = malloc(sizeof(char*)*bowlSize);
	for(int i=0;i<bowlSize;i++){
		b[i] = malloc(sizeof(char*)*maxLen);
		for(int j=0;j<maxLen;j++){
			b[i][j]=malloc(sizeof(char)*maxLen);
		}
	}
	return b;
}

/**
 * Procesa un comando simple y lo pone en un 
 * recipiente simple
 * */
char ** fastCook(char *c,char **b){
	int i  = 0;
	int i2 = 0;
	for(int j=0;j<strlen(c)||c[j]=='>';j++){
		if(c[j]==' '){
			b[i][i2]='\0';
			i++;
			i2=0;
		}else{
			b[i][i2]=c[j];
			i2++;
		}
	}
	b[i][i2]='\0';
	i++;
	b[i]=NULL;
	return b;
}


/**
 * Procesa un comando con pipe y lo
 * pone en un recipiente multiple
 * */
char *** cook(char *c,char ***b){
	int i = 0;
	int j = 0;
	int k = 0;
	
	char**c2=malloc(sizeof(char*)*2);
	c2[0]=malloc(sizeof(char)*maxLen);
	c2[1]=malloc(sizeof(char)*maxLen);


	for(;i<strlen(c)||c[j]=='>';i++){
		if(c[i]=='|'){
			j++;
			k=0;
			continue;
		}
		c2[j][k]=c[i];
		k++;
	}
	
	fastCook(prepare(c2[0]),b[0]);
	fastCook(prepare(c2[1]),b[1]);
	
	return b;
}


/**
 * Ejecuta un codigo simple
 * */
void eatFast(char**f){
	int e = execvp(f[0],f);
	if(e==-1)printf("\x1b[31m" "%s\n",error);
	exit(EXIT_SUCCESS);
}

/**
 * Ejecuta un codigo de pipe
 * */
void eat(char***f){
	int fd[2],e1,e2;
	pipe(fd); 
	if (fork()!=0) {
			close(fd[0]);
			close(1);
			dup(fd[1]); 
			close(fd[1]);
			e1 = execvp(f[0][0],f[0]);
			if(e1)printf("\x1b[31m" "%s\n",error);
			exit(EXIT_SUCCESS);
	}else{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			e2 = execvp(f[1][0],f[1]);
			if(e2)printf("\x1b[31m" "%s\n",error);
			exit(EXIT_SUCCESS);
	}
}

char*address(char*c){
	int i=0;
	int j=0;
	for(;i<strlen(c);i++){
		if(c[i]=='>'){
			i++;
			break;
		}
	}
	
	char*p=malloc(sizeof(char)*maxLen);
	for(;j<strlen(c);j++){
		p[j]=c[i];
		i++;
	}
	p[j]='\0';
	return fastCook(prepare(p),dish())[0];
}

void deliver(char*c){
	struct stat s;
	int e = stat(address(c),&s);
	if(e){
		printf("\x1b[31m" "no existe %s\n",address(c));
		exit(EXIT_SUCCESS);
	}else{
		printf("%d",isFastFood(prepare(c)));
		close(1);
		open(address(c),O_CREAT | O_WRONLY,0777);
		
		if(isFastFood(c)){
			char**food = fastCook(prepare(c),dish());
			eatFast(food);
		}else{
			char***food = cook(prepare(c),pot());
			eat(food);
		}
	}
}

int isDeliver(char*c){
	for(int i=0;i<strlen(c);i++){
		if(c[i]=='>')return 1;
	}return 0;
}
