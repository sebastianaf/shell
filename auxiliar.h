 /*
  * aux.h
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

#ifndef __SHELL__
#define __SHELL__
int maxLen;
char*address(char*c);
int isFastFood(char *c);
char**dish();
char***pot();
char***cook(char*c,char***b);
char**fastCook(char*c,char**b);
void eatFast(char**f);
void eat(char***f);
char*prepare(char*c);
void deliver(char*address);
int isDeliver(char*c);

#endif
