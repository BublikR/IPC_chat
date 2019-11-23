CC = gcc
CLEAN = rm -f

all: server client

server: server.o
	$(CC) -o server $^

client: client.o
	$(CC) -o client $^

server.o: server.c
	$(CC) -c $^

client.o: client.c
	$(CC) -c $^

clean:
	$(CLEAN) *.o server client
