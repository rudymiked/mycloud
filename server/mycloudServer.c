/***********************

file: mycloudServer.c

RUDY BROOKS

************************/

#include <stdio.h>
#include <stdlib.h>
#include "../mycloud.h"
#include "csapp.h"

int validKey(int connfd, unsigned int secretKey);

int main(int argc, char **argv) 
{
    int listenfd, connfd, port;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    unsigned int secretKey;

    if (argc != 3) {
	fprintf(stderr, "usage: %s <port> <secret key>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);
    secretKey = atoi(argv[2]);

    listenfd = Open_listenfd(port);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	/* Determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			   sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
	printf("server connected to %s (%s)\n", hp->h_name, haddrp);

        validKey(connfd, secretKey);
	Close(connfd);
    }
    exit(0);
}

// returns 0 if key is valid and -1 if invalid
int validKey(int connfd, unsigned int secretKey) {
    size_t n;
    char buf[SECRET_KEY_SIZE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    if((n = Rio_readnb(&rio, buf, SECRET_KEY_SIZE)) == 4) {
        printf("server received %d bytes\n", (int)n);
        printf("server's secret key is %d\n", secretKey);
        if(atoi(buf) == secretKey) {
            printf("server authenticated the secret key %d\n", atoi(buf));
            return 0;
        } else {
            printf("invalid secret key %d\n", atoi(buf));
            return -1;
        }
    }    
    return -1;
}



