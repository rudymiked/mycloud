/***************************

file: mclist.c

RUDY BROOKS

******************************/

#include "LibCalls.c"
#include "stdio.h"
#include "stdlib.h"


int main(int argc, char *argv[]){

  int list_buflen;
  char *list_buf;

  char *machine_name = argv[1];
  unsigned int tcp_port     = atoi(argv[2]);
  unsigned int secret_key   = atoi(argv[3]);  

  mycloud_listfiles(machine_name, tcp_port, secret_key, list_buf, list_buflen);

  printf("%s \n", list_buf);

  return 0;
}
