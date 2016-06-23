all : myls myio mystdio
myls : myls.o
	gcc -o myls myls.o
myls.o : myls.c
	gcc -g -c myls.c
myio : myio.o
	gcc -o myio myio.o
myio.o : myio.c
	gcc -g -c myio.c
mystdio : mystdio.o
	gcc -o mystdio mystdio.o
mystdio.o : mystdio.c
	gcc -g -c mystdio.c
clean :
	rm -rf myls myio mystdio *.o
