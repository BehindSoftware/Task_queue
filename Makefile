#Compiler 
CC=gcc
#Compiler parameters
CFLAGS=-c -Wall

all: queue
	
queue: queue.o
	$(CC) $(CFLAGS) queue.c -o queue

queue.o: queue.h queue.c
	$(CC) $(CFLAGS) queue.c

clean: 
	rm -rf *o queue

