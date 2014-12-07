/***********************

file: mycloudServer.c

RUDY BROOKS

************************/

#include <stdio.h>
#include <stdlib.h>
#include "../mycloud.h"
#include "csapp.h"

int validKey(int connfd, unsigned int secretKey);
int getRequest(int connfd);
int storeRequest(int connfd);
int retrieveRequest(int connfd);
int deleteRequest(int connfd);
int listFilesRequest(int connfd);



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

        if(validKey(connfd, secretKey)) {
            
        }

	Close(connfd);
    }
    exit(0);
}

// Return 0 if key is valid, -1 if invalid
int validKey(int connfd, unsigned int secretKey) {
    size_t n;
    char buf[SECRET_KEY_SIZE];
    rio_t rio;
    unsigned int clientKey, netOrder;

    Rio_readinitb(&rio, connfd);
    if((n = Rio_readnb(&rio, buf, SECRET_KEY_SIZE)) == 4) {
        printf("server received %d bytes\n", (int)n);
        printf("server's secret key is %d\n", secretKey);
        
        // Copy binary data from buffer
        memcpy(&netOrder, &buf, SECRET_KEY_SIZE);
        clientKey = ntohl(netOrder);        

        if(clientKey == secretKey) {
            printf("successfully authenticated the client's secret key of %d\n", clientKey);
            return 0;
        } else {
            printf("invalid client secret key of %d\n", clientKey);
            return -1;
        }
    }    
    return -1;
}

// returns the request type or -1 if invalid
int getRequest(int connfd) {
    size_t n;
    char buf[REQUEST_TYPE_SIZE];
    rio_t rio;
    unsigned int requestType;

    Rio_readinitb(&rio, connfd);
    if((n = Rio_readnb(&rio, buf, REQUEST_TYPE_SIZE)) == 4) {
        printf("server received %d bytes\n", (int)n);

        // Copy binary data from buffer
        memcpy(&requestType, &buf, REQUEST_TYPE_SIZE);
        return requestType;
    }
    return -1;
}

int storeRequest(int connfd) {

}

int retrieveRequest(int connfd) {

}

int deleteRequest(int connfd) {

}

int listFilesRequest(int connfd) {

}
