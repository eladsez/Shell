CC = gcc
DEBG = -Wall -g
OBJECTS = util.o command_helper.o tcp_client.o
# SOURCES = main.c


all:shell server

shell: main.o shell_lib.a
	$(CC) $(DEBG) main.o shell_lib.a -o shell

shell_lib.a: $(OBJECTS)
	ar -rcs shell_lib.a $(OBJECTS)

main.o: main.c shell.h
	$(CC) $(DEBG) -c main.c

tcp_client.o: tcp_client.c
	$(CC) $(DEBG) -c tcp_client.c

util.o: util.c
	$(CC) $(DEBG) -c util.c

command_helper.o: command_helper.c
	$(CC) $(DEBG) -c command_helper.c

server: tcp_server.c
	$(CC) $(DEBG) tcp_server.c -o server 

test_client: tcp_client.c
	$(CC) $(DEBG) tcp_client.c -o client 

clean:
	rm -f *.o *.a
	rm -f shell server
