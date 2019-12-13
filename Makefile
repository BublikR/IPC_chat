CC = gcc
CLEAN = rm -f

all: server client

server: server.o llist.o
	$(CC) -o server $^

client: client.o
	$(CC) -o client $^

server.o: server.c llist.c
	$(CC) -c $^

client.o: client.c
	$(CC) -c $^

clean:
	$(CLEAN) *.o server client
