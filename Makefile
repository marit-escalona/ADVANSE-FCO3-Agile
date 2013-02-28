
fco3 : main.o trl.o
	gcc main.o trl.o -o fco3

main.o : main.c
	gcc -c main.c

trl.o : trl.c trl.h
	gcc -c trl.c


.PHONY : clean
clean :
	rm -f *.o fco3

