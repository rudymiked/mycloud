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
  size_t n;
  FILE *fstream;

  if (argc != 5) { fprintf(stderr, "Usage: ./mcget <machine> <port> <secret key> <filename>i\n"); return -1;}

  //run Libary/API call
  int status = mycloud_getfile(machine_name, tcp_port, secret_key, file_name, data, datalen);
  
  // Write to file
  if ((fstream = Fopen(file_name, "w")) != NULL) { 
    Fwrite(data, sizeof(char), datalen, fstream);
    Fclose(fstream);
    return 0;
  } else { 
    printf("Cannot open file: %s !\n", file_name);
    return -1;
  }

  return -1;
}
