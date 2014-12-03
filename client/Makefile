CC = gcc
FLAGS = -Wall
LIBS = -pthread
OBJS = mcdel mcput mclist mcget
SRCS = mcdel.c mcput.c mclist.c mcget.c


all: mcdel mcput mclist mcget
.PHONY : all

mcdel: mcdel.o
	$(CC) -o mcdel mcdel.c
mcput: mcput.o
	$(CC) $(LIBS) -o mcput mcput.c csapp.c
mclist: mclist.o
	$(CC) -o mclist mclist.c
mcget: mcget.o
	$(CC) -o mcget mcget.c

.PHONY : clean

clean:
	rm $(OBJS)
