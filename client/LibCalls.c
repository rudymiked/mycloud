#include "csapp.h"
#include "../mycloud.h"

int mycloud_putfile(char *MachineName, int TCPport, int SecretKey, char *FileName, char *data, int datalen) {

  int clientfd;
  char buf[datalen];

//  printf("Machine_name: %s\n", MachineName);
//  printf("TCPport: %d \n", TCPport); 

  FILE *file = Fopen(FileName, "r+");

  clientfd = Open_clientfd(MachineName, TCPport);
  printf("Clientfd: %d \n", clientfd); 

  //rio_readn(fd, data, datalen);
  
  while (Fgets(buf,datalen,file) !=NULL) {
    Rio_writen(clientfd, buf, strlen(buf));
    Rio_readn(clientfd, data, datalen);
    Fputs(buf, stdout);
  }

  Close(clientfd);
  
  return 0;
  
  //send bytes of data to the cloud server
  //return 0 for success, -1 for error

}


int mycloud_getfile(char *MachineName, int TCPport, int SecretKey, char *Filename, char *data, int datalen) {

  int clientfd;
//  char buf[datalen];

  clientfd = Open_clientfd(MachineName, TCPport);
  printf("Clientfd: %d \n", clientfd); 

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
