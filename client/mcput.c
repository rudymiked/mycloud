/***********************

file: myput.c

RUDY BROOKS

************************/

#include <stdio.h>
#include <stdlib.h>
#include "LibCalls.c"


int main(int argc, const char *argv[]) {

  int datalen = 50;
  char *data = "DATA!!";

  char *machine_name = argv[1];
  int tcp_port     = atoi(argv[2]);
  int secret_key   = atoi(argv[3]);   
  char *file_name  = argv[4];

  FILE *f = fopen(file_name, "r");

  if (f == 0) { //File does not exist
    fprintf(stderr, "Cannot open input file!\n");
    return -1;
  }
 
  if (argc != 5) {
    fprintf(stderr, "Usage: ./mcput <machine> <port> <secret key> <filename>\n");
    return -1;
  }

  /******DEBUGGING********************/
  int i;
  for(i=1;i<5;++i)
    printf("%d : %s \n", i, argv[i]);
  /************************************/

  //run Libary/API call
  mycloud_putfile(machine_name, tcp_port, secret_key, file_name, data, datalen);

  
  fclose(f);
  
  return 0;
}
