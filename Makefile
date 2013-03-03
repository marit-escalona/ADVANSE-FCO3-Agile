
APPNAME = fco3
OBJECTS = main.o trl.o input.o program.o user.o
CFLAGS = -g

fco3 : $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o $(APPNAME)

main.o : main.c
	gcc $(CFLAGS) -c main.c

trl.o : trl.c trl.h
	gcc $(CFLAGS) -c trl.c

input.o : input.c input.h
	gcc $(CFLAGS) -c input.c

program.o : program.c program.h
	gcc $(CFLAGS) -c program.c

user.o : user.c user.h
	gcc $(CFLAGS) -c user.c

.PHONY : clean
clean :
	rm -f *.o fco3

