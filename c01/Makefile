all : myls myio mystdio hello shell1

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
hello : hello.o
	gcc -o hello hello.o
hello.o : hello.c
	gcc -g -c hello.c
shell1 : shell1.o
	gcc -o shell1 shell1.o
shell1.o : shell1.c
	gcc -g -c shell1.c
clean :
	rm -rf myls myio mystdio hello shell1 *.o
