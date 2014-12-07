/***********************

file: mycloudServer.c

RUDY BROOKS

************************/

#include <stdio.h>
#include <stdlib.h>
#include "../mycloud.h"
#include "csapp.h"

int validKey(rio_t *rio, unsigned int secretKey);
int getRequest(rio_t *rio);
int storeRequest(rio_t *rio, int connfd);
int retrieveRequest(rio_t *rio, int connfd);
int deleteRequest(rio_t *rio, int connfd);
int listFilesRequest(rio_t *rio, int connfd);

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

        rio_t rio;
        Rio_readinitb(&rio, connfd);
        
        // Authenticate key
        if(validKey(&rio, secretKey) == 0) {
            // Identify request type
            int requestType = getRequest(&rio);
            if(requestType == 0) {
                int status = retrieveRequest(&rio, connfd);
            } else if(requestType == 1) {
                int status = storeRequest(&rio, connfd);
            } else if(requestType == 2) {
                int status = deleteRequest(&rio, connfd);
            } else if(requestType == 3) {
                int status = listFilesRequest(&rio, connfd);
            }
        }
	Close(connfd);
    }
    exit(0);
}

// Return 0 if key is valid, -1 if invalid
int validKey(rio_t *rio, unsigned int secretKey) {
    size_t n;
    char buf[SECRET_KEY_SIZE];
    unsigned int clientKey, netOrder;

    if((n = Rio_readnb(rio, buf, SECRET_KEY_SIZE)) == SECRET_KEY_SIZE) {
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

// Returns the request type or -1 if invalid
int getRequest(rio_t *rio) {
    size_t n;
    char buf[REQUEST_TYPE_SIZE];
    unsigned int requestType, netOrder;

    if((n = Rio_readnb(rio, buf, REQUEST_TYPE_SIZE)) == REQUEST_TYPE_SIZE) {
        printf("server received %d bytes\n", (int)n);

        // Copy binary data from buffer
        memcpy(&netOrder, &buf, REQUEST_TYPE_SIZE);
        requestType = ntohl(netOrder);
        return requestType;
    }
    return -1;
}

// Return 0 if the store succeeds, -1 if fails
int storeRequest(rio_t *rio, int connfd) {
    size_t n;
    char fileNameBuf[FILE_NAME_SIZE];
    char fileName[FILE_NAME_SIZE];
    char fileSizeBuf[MAX_NUM_BYTES_IN_FILE];
    unsigned int fileSize, netOrder, status, messageSize;
    char dataBuf[MAX_FILE_SIZE];
    char *data, message;
    FILE *fstream;
    
    // Read file name
    if((n = Rio_readnb(rio, fileNameBuf, FILE_NAME_SIZE)) == FILE_NAME_SIZE) {
        printf("server received %d bytes\n", (int)n);

        // Copy binary data from buffer
        memcpy(&fileName, &fileNameBuf, FILE_NAME_SIZE);
        printf("fileName = %s\n", fileName);
    } else {
        status = -1;
    }

    // Read file size
    if((n = Rio_readnb(rio, fileSizeBuf, MAX_NUM_BYTES_IN_FILE)) == MAX_NUM_BYTES_IN_FILE) {
        printf("server received %d bytes\n", (int)n);

        // Copy binary data from buffer
        memcpy(&netOrder, &fileSizeBuf, MAX_NUM_BYTES_IN_FILE);
        fileSize = ntohl(netOrder);
        printf("fileSize = %d\n", fileSize);
    } else {
        status = -1;
    }

    // Read file data
    if((n = Rio_readnb(rio, dataBuf, fileSize)) == fileSize) {
        printf("server received %d bytes\n", (int)n);

        // Allocate memory for the data
        data = (char*) malloc (sizeof(char)*fileSize);
        if(data == NULL) { fprintf(stderr, "Memory Error - mcput\n"); return -1; }

        // Copy binary data from buffer
        memcpy(data, &dataBuf, fileSize);
    } else {
        status = -1;
    }

    // Write to file
    if((fstream = Fopen(fileName, "w")) != NULL) {
        Fwrite(data, sizeof(char), fileSize, fstream);
        Fclose(fstream);
        status = 0;
    } else {
        status = -1;
    }
    free(data);

    /*************************
     * Send response message *
     *************************/

    // Set message size according to the protocol
    messageSize = STATUS_SIZE;

    // Allocate memory for the message buffer defined by the protocol
    message = (char*) malloc (sizeof(char*)*messageSize);
    if(message == NULL) { fprintf(stderr, "Memory Error - mcputs\n"); return -1; }
    char *messagePtr = message;

    // Copy the operational status into message buffer
    netOrder = htonl(status);
    memcpy(messagePtr, &netOrder, STATUS_SIZE);
    messagePtr += STATUS_SIZE;

    // Send the response message
    Rio_writen(connfd, message, messageSize);
    free(message);

    return status;
}

int retrieveRequest(rio_t *rio, int connfd) {

}

int deleteRequest(rio_t *rio, int connfd) {

}

int listFilesRequest(rio_t *rio, int connfd) {

}
