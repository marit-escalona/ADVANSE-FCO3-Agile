
APPNAME = fco3
OBJECTS = main.o trl.o input.o program.o user.o dbconn.o utils.o
CFLAGS = -g `mysql_config --cflags`
LDFLAGS = `mysql_config --libs`

fco3 : $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o $(APPNAME) $(LDFLAGS)

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

dbconn.o : dbconn.c dbconn.h
	gcc $(CFLAGS) -c dbconn.c

utils.o : utils.c utils.h
	gcc $(CFLAGS) -c utils.c

.PHONY : clean
clean :
	rm -f *.o fco3

