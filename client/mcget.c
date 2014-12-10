/*****************************

file: mcget.c

RUDY BROOKS

*******************************/

#include <stdio.h>
#include <stdlib.h>
#include "LibCalls.c"


int main(int argc, char *argv[]) {

  int datalen = MAX_NUM_BYTES_IN_FILE;
  char *data;
  char *machine_name        = argv[1];
  unsigned int tcp_port     = atoi(argv[2]);
  unsigned int secret_key   = atoi(argv[3]);   
  char *file_name           = argv[4];
  FILE *fstream;

  if (argc != 5) { fprintf(stderr, "Usage: ./mcget <machine> <port> <secret key> <filename>i\n"); return -1;}

  //run Libary/API call
  int status = mycloud_getfile(machine_name, tcp_port, secret_key, file_name, &data, &datalen);

  //printf("datalen: %d\n", datalen);
  //printf("%s \n", data);

  // write to stdout
  //write(1, data, datalen);   <- also prints
  printf("%s \n", data);

  return status;
}
