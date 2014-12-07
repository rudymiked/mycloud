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
  Close(clientfd);
  free(message);
  return 0;
}


int mycloud_getfile(char *MachineName, int TCPport, int SecretKey, char *Filename, char *data, int datalen) {

  int clientfd;
  char buf[datalen];

  clientfd = Open_clientfd(MachineName, TCPport);
  printf("Clientfd: %d \n", clientfd); 

  /*while (Fgets(buf,datalen,file) !=NULL) {
    Rio_readn(clientfd, data, datalen);
    Rio_writen(clientfd, buf, strlen(buf));
    Fputs(buf, stdout);
  }*/

  Close(clientfd);

  //retrieve bytes of data from "FileName" 
  //returns the number of bytes in the file, or -1 for error

  return 0;
}

int mycloud_delfile(char *MachineName, int TCPport, int SecretKey, char *Filename) { 

  int clientfd;

  clientfd = Open_clientfd(MachineName, TCPport);
  printf("Clientfd: %d \n", clientfd); 


  //send message to server requesting to delete "FileName"
  //return 0 for success, -1 for error

  return 0;

}


int mycloud_listfiles(char *MachineName, int TCPport, int SecretKey, char *listbuf, int listbuflen) {

  int clientfd;

  clientfd = Open_clientfd(MachineName, TCPport);
  printf("Clientfd: %d \n", clientfd); 

  //sends request to server for all files in server
  //prints each file separated by '\n'
  // 0 = success, -1 = error
  
  return 0;

}
