myls : myls.o
	gcc -o myls myls.o
myls.o : myls.c
	gcc -g -c myls.c
myio : myio.o
	gcc -o myio myio.o
myio.o : myio.c
	gcc -g -c myio.c
clean :
	rm -rf myls myio *.o
