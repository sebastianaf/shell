 
 # Makefile
 # 
 # Universidad del Valle
 # Escuela de Ingenieria de Sistemas y Computacion
 # Sistemas Operativos
 # Profesor John Alexander Sanabria Ph.D.
 # Presentado por Sebastian Afanador & David Crespo
 # 
 # Entreaga: Proyecto 1 - Shell

shell: aux.a
	gcc -L. -o shell shell.c aux.a
aux.a: aux.o
	ar -cvq aux.a aux.o
aux.o:
	gcc -c aux.c
clean:
	rm -f shell a.out *.a *.o 
