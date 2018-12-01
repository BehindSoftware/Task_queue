#Compiler 
CC=gcc
#Compiler parameters
CFLAGS=-c -Wall

all: queue
	
queue: queue.o
	$(CC) queue.o -o queue

queue.o: queue.h queue.c
	$(CC) $(CFLAGS) queue.c

clean: 
	rm -rf *o queue

