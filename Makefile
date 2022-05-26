 
 # Makefile
 # 
 # Universidad del Valle
 # Escuela de Ingenieria de Sistemas y Computacion
 # Sistemas Operativos
 # Profesor John Alexander Sanabria Ph.D.
 # Presentado por Sebastian Afanador & David Crespo
 # 
 # Entreaga: Proyecto 1 - Shell

shell: auxiliar.a
	gcc -L. -o shell shell.c auxiliar.a
auxiliar.a: auxiliar.o
	ar -cvq auxiliar.a auxiliar.o
auxiliar.o:
	gcc -c auxiliar.c
clean:
	rm -f shell a.out *.a *.o 
