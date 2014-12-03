CC = gcc
FLAGS = -Wall
LIBS = -pthread
OBJS = mycloudServer
SRCS = mycloudServer.c

all: mycloudServer
.PHONY : all

mycloudServer: mycloudServer.o
	$(CC) $(LIBS) -o mycloudServer mycloudServer.c csapp.c

.PHONY : clean

clean:
	rm $(OBJS)

