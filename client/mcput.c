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
  datalen = SECRET_KEY_SIZE + REQUEST_TYPE_SIZE + FILE_NAME_SIZE + ftell(f);
  rewind(f);

  data = (char*) malloc (sizeof(char)*datalen);
//  if (data == NULL) {fputs ("Memory Error - mcputs", stderr); exit(3);}  

  result = fread(data, 1, datalen, f); 

  printf("d: %s \n", data);
  
  fclose(f);
  free(data);
  //run Libary/API call
  mycloud_putfile(machine_name, tcp_port, secret_key, file_name, data, datalen);
    
  return 0;
}
