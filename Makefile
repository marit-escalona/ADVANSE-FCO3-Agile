
APPNAME = fco3
OBJECTS = main.o trl.o input.o

fco3 : $(OBJECTS)
	gcc $(OBJECTS) -o $(APPNAME)

main.o : main.c
	gcc -c main.c

trl.o : trl.c trl.h
	gcc -c trl.c

input.o : input.c input.h
	gcc -c input.c

.PHONY : clean
clean :
	rm -f *.o fco3

