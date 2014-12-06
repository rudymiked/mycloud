CC = gcc
FLAGS = -Wall
LIBS = -pthread
OBJS = mycloudServer
SRCS = mycloudServer.c

all: clean mycloudServer

mycloudServer: mycloudServer.o
	$(CC) $(LIBS) -o mycloudServer mycloudServer.c csapp.c

clean:
	rm -f $(OBJS) *.o

