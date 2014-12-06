/***********************

file: myput.c

RUDY BROOKS

************************/

#include <stdio.h>
#include <stdlib.h>
#include "LibCalls.c"


int main(int argc, char *argv[]) {

  int datalen;
  char *data;

  char *machine_name      = argv[1];
  unsigned int tcp_port   = atoi(argv[2]);
  unsigned int secret_key = atoi(argv[3]);   
  char *file_name         = argv[4];
  size_t result;

  FILE *f = fopen(file_name, "r");

  if (f == 0) { //File does not exist
    fprintf(stderr, "Cannot open input file!\n");
    return -1;
  }

  if (argc != 5) {
    fprintf(stderr, "Usage: ./mcput <machine> <port> <secret key> <filename>\n");
    return -1;
  }

  /******DEBUGGING********************
  int i;
  for(i=1;i<5;++i)
    printf("%d : %s \n", i, argv[i]);
  ************************************/

  fseek(f, 0, SEEK_END);
  unsigned int fileSize = ftell(f);
  datalen = SECRET_KEY_SIZE + REQUEST_TYPE_SIZE + FILE_NAME_SIZE + fileSize;
  rewind(f);

  data = (char*) malloc (sizeof(char)*datalen);
  char *dataPtr = data;
  unsigned int netOrder;
//  if (data == NULL) {fputs ("Memory Error - mcputs", stderr); exit(3);}  

  // Copy secret key into data buffer
  printf("secret_key = %d\n", secret_key);
  netOrder = htonl(secret_key);
  printf("netOrder = %d\n", netOrder);
  printf("&netOrder = %d\n", &netOrder);
  memcpy(dataPtr, &netOrder, SECRET_KEY_SIZE);
  dataPtr += SECRET_KEY_SIZE;

  //char buf[SECRET_KEY_SIZE];
  unsigned int keyTest;
  //memcpy(buf, data, SECRET_KEY_SIZE);
  memcpy(&keyTest, data, SECRET_KEY_SIZE);
  printf("keyTest = %d\n", keyTest);

  // Copy request type into data buffer
  unsigned int request = 1;
  netOrder = htonl(request);
  memcpy(dataPtr, &netOrder, REQUEST_TYPE_SIZE);
  dataPtr += REQUEST_TYPE_SIZE;

  // Copy file name into data buffer
  memcpy(dataPtr, file_name, FILE_NAME_SIZE);
  dataPtr += FILE_NAME_SIZE;

  // Copy file size into data buffer
  netOrder = htonl(fileSize);
  memcpy(dataPtr, &netOrder, MAX_NUM_BYTES_IN_FILE);
  dataPtr += MAX_NUM_BYTES_IN_FILE;

  // Copy file data into data buffer
  result = fread(dataPtr, 1, fileSize, f);
  dataPtr += fileSize;

  printf("d: %s \n", data);
  
  fclose(f);
  free(data);
  //run Libary/API call
  mycloud_putfile(machine_name, tcp_port, secret_key, file_name, data, datalen);
    
  return 0;
}
