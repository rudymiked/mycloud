CC = gcc
FLAGS = -Wall
LIBS = -pthread
OBJS = mcdel mcput mclist mcget
SRCS = mcdel.c mcput.c mclist.c mcget.c


all: clean mcdel mcput mclist mcget

mcdel: mcdel.o
	$(CC) $(FLAGS) $(LIBS) -o mcdel mcdel.c csapp.c
mcput: mcput.o 
	$(CC) $(FLAGS) $(LIBS) -o mcput mcput.c csapp.c
mclist: mclist.o
	$(CC) $(FLAGS) $(LIBS) -o mclist mclist.c csapp.c
mcget: mcget.o
	$(CC) $(FLAGS) $(LIBS) -o mcget mcget.c csapp.c

clean:
	rm -f $(OBJS) *.o
