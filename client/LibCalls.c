/**************************

file: LibCalls.c

RUDY BROOKS

***************************/

#include "csapp.h"
#include "../mycloud.h"

// Send bytes of data to the cloud server
// Return 0 for success, -1 for error
int mycloud_putfile(char *MachineName, int TCPport, int SecretKey, char *FileName, char *data, int datalen) {
  int clientfd;
  char *message;
  unsigned int messageSize, netOrder;

  // Set message size according to the protocol
  messageSize = SECRET_KEY_SIZE + REQUEST_TYPE_SIZE + FILE_NAME_SIZE + MAX_NUM_BYTES_IN_FILE + datalen;

  // Allocate memory for the message buffer defined by the protocol
  message = (char*) malloc (sizeof(char)*messageSize);
  if(message == NULL) { fprintf(stderr, "Memory Error - mcputs\n"); return -1; }
  char *messagePtr = message;

  // Copy secret key into message buffer
  netOrder = htonl(SecretKey);
  memcpy(messagePtr, &netOrder, SECRET_KEY_SIZE);
  messagePtr += SECRET_KEY_SIZE;

  // Copy request type into message buffer
  unsigned int request = 1;
  netOrder = htonl(request);
  memcpy(messagePtr, &netOrder, REQUEST_TYPE_SIZE);
  messagePtr += REQUEST_TYPE_SIZE;

  // Copy file name into message buffer
  memcpy(messagePtr, FileName, FILE_NAME_SIZE);
  messagePtr += FILE_NAME_SIZE;

  // Copy file size into message buffer
  netOrder = htonl(datalen);
  memcpy(messagePtr, &netOrder, MAX_NUM_BYTES_IN_FILE);
  messagePtr += MAX_NUM_BYTES_IN_FILE;

  // Copy file data into message buffer
  memcpy(messagePtr, data, datalen);
  messagePtr += datalen;

  clientfd = Open_clientfd(MachineName, TCPport);
  Rio_writen(clientfd, message, messageSize);
  free(message);

  //
  // Receieve operational status
  //
  size_t n;
  char buf[STATUS_SIZE];
  unsigned int status;
  rio_t rio;
  Rio_readinitb(&rio, clientfd);
  
  status = -1;
  if((n = Rio_readnb(&rio, buf, STATUS_SIZE)) == STATUS_SIZE) {
    // Copy binary data from buffer
    memcpy(&netOrder, &buf, STATUS_SIZE);
    status = ntohl(netOrder);
  }
  Close(clientfd);
  return status;
}

//retrieve bytes of data from "FileName" 
//returns the number of bytes in the file, or -1 for error
int mycloud_getfile(char *MachineName, int TCPport, int SecretKey, char *Filename, char *data, int datalen) {

  int clientfd;
  char *message;
  unsigned int messageSize, netOrder;

  messageSize = SECRET_KEY_SIZE + REQUEST_TYPE_SIZE + FILE_NAME_SIZE;

  // Allocate memory for the message buffer defined by the protocol
  message = (char*) malloc (sizeof(char)*messageSize);
  if(message == NULL) { fprintf(stderr, "Memory Error - mcputs\n"); return -1; }
  char *messagePtr = message;

  // Copy secret key into message buffer
  netOrder = htonl(SecretKey);
  memcpy(messagePtr, &netOrder, SECRET_KEY_SIZE);
  messagePtr += SECRET_KEY_SIZE;

  // Copy request type into message buffer
  unsigned int request = 0;
  netOrder = htonl(request);
  memcpy(messagePtr, &netOrder, REQUEST_TYPE_SIZE);
  messagePtr += REQUEST_TYPE_SIZE;

  // Copy file name into message buffer
  memcpy(messagePtr, Filename, FILE_NAME_SIZE);
  messagePtr += FILE_NAME_SIZE;

  clientfd = Open_clientfd(MachineName, TCPport);
  Rio_writen(clientfd, message, messageSize);
  Rio_readn(clientfd, data, datalen);
  Close(clientfd);
  free(message);

  
  return 0;
}



// send message to server requesting to delete "FileName"
// return 0 for success, -1 for error
int mycloud_delfile(char *MachineName, int TCPport, int SecretKey, char *Filename) { 

  int clientfd;
  char *message;
  unsigned int messageSize, netOrder;

  messageSize = SECRET_KEY_SIZE + REQUEST_TYPE_SIZE + FILE_NAME_SIZE;

  // Allocate memory for the message buffer defined by the protocol
  message = (char*) malloc (sizeof(char)*messageSize);
  if(message == NULL) { fprintf(stderr, "Memory Error - mcputs\n"); return -1; }
  char *messagePtr = message;

  // Copy secret key into message buffer
  netOrder = htonl(SecretKey);
  memcpy(messagePtr, &netOrder, SECRET_KEY_SIZE);
  messagePtr += SECRET_KEY_SIZE;

  // Copy request type into message buffer
  unsigned int request = 2;
  netOrder = htonl(request);
  memcpy(messagePtr, &netOrder, REQUEST_TYPE_SIZE);
  messagePtr += REQUEST_TYPE_SIZE;

  // Copy file name into message buffer
  memcpy(messagePtr, Filename, FILE_NAME_SIZE);
  messagePtr += FILE_NAME_SIZE;

  clientfd = Open_clientfd(MachineName, TCPport);
  Rio_writen(clientfd, message, messageSize);
  Close(clientfd);
  free(message);

  printf("Files Successfully Deleted\n");
  return 0;

}

// sends request to server for all files in server
// server - prints each file separated by '\n'
// 0 = success, -1 = error

int mycloud_listfiles(char *MachineName, int TCPport, int SecretKey, char *list_buf, int list_buf_len) {

  int clientfd;
  char *message;
  unsigned int messageSize, netOrder;

  messageSize = SECRET_KEY_SIZE + REQUEST_TYPE_SIZE;

  // Allocate memory for the message buffer defined by the protocol
  message = (char*) malloc (sizeof(char)*messageSize);
  if(message == NULL) { fprintf(stderr, "Memory Error - mcputs\n"); return -1; }
  char *messagePtr = message;

  // Copy secret key into message buffer
  netOrder = htonl(SecretKey);
  memcpy(messagePtr, &netOrder, SECRET_KEY_SIZE);
  messagePtr += SECRET_KEY_SIZE;

  // Copy request type into message buffer
  unsigned int request = 3;
  netOrder = htonl(request);
  memcpy(messagePtr, &netOrder, REQUEST_TYPE_SIZE);
  messagePtr += REQUEST_TYPE_SIZE;

  clientfd = Open_clientfd(MachineName, TCPport);
  Rio_writen(clientfd, message, messageSize);
  // Retrieve list buffer from server
  Rio_readn(clientfd, list_buf, list_buf_len);
  printf("list: %s \n", list_buf);
  Close(clientfd);
  free(message);
    
  return 0;

}
