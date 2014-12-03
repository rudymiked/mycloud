#include "../testing/client.c"

int mycloud_putfile(char *MachineName, int TCPport, int SecretKey, char *FileName, char *data, int datalen) {


  
  //send bytes of data to the cloud server
  //return 0 for success, -1 for error

}


int mycloud_getfile(char *MachineName, int TCPport, int SecretKey, char *Filename, char *data, int datalen) {

  //retrieve bytes of data from "FileName" 
  //returns the number of bytes in the file, or -1 for error


}

int mycloud_delfile(char *MachineName, int TCPport, int SecretKey, char *Filename) { 

  //send message to server requesting to delete "FileName"
  //return 0 for success, -1 for error


}


int mycloud_listfiles(char *MachineName, int TCPport, int SecretKey, char *listbuf, int listbuflen) {

  //sends request to server for all files in server
  //prints each file separated by '\n'
  // 0 = success, -1 = error


}
