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
  size_t n;

  if (argc != 5) { fprintf(stderr, "Usage: ./mcput <machine> <port> <secret key> <filename>\n"); return -1; }

  // Check if file exists and open it
  FILE *file = fopen(file_name, "r");
  if(file == 0) { fprintf(stderr, "Cannot open input file!\n"); return -1; }

  // Obtain file size
  fseek(file, 0, SEEK_END);
  datalen = ftell(file);
  rewind(file);

  // Allocate memory for the data buffer
  data = (char*) malloc (sizeof(char)*datalen);
  if(data == NULL) { fprintf(stderr, "Memory Error - mcput\n"); return -1; }

  // Copy file data into data buffer and call API
  if((n = fread(data, 1, datalen, file)) == datalen) {
    fclose(file);
    mycloud_putfile(machine_name, tcp_port, secret_key, file_name, data, datalen);
    free(data);
    return 0;
  } else {
    fprintf(stderr, "Error - cannot copy all file data into buffer\n");
    fclose(file);
    free(data);
    return -1;
  }

  return -1;
}

