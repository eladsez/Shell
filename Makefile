CC = gcc
DEBG = -Wall -g
OBJECTS = command_helper.o util.o 
# SOURCES = main.c

all:shell server
	#./shell && make clean

shell: main.o shell_lib.a
	$(CC) $(DEBG) main.o shell_lib.a -o shell

shell_lib.a: $(OBJECTS)
	ar -rcs shell_lib.a $(OBJECTS)

main.o: main.c shell.h
	$(CC) $(DEBG) -c main.c

util.o: util.c
	$(CC) $(DEBG) -c util.c

command_helper.o: command_helper.c
	$(CC) $(DEBG) -c command_helper.c

server: tcp_server.c
	$(CC) $(DEBG) tcp_server.c -o server 

clean:
	rm -f *.o *.a test*
	rm -f shell server
