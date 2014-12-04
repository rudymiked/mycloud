/***************************

file: mclist.c

RUDY BROOKS

******************************/

#include "LibCalls.c"
#include "stdio.h"
#include "stdlib.h"


int main(int argc, char *argv[]){

  int list_buflen = 100;
  char list_buf[list_buflen];

  char *machine_name = argv[1];
  int tcp_port     = (int)argv[2][0] - '0';
  int secret_key   = (int)argv[3][0] - '0';  

  mycloud_listfiles(machine_name, tcp_port, secret_key, list_buf, list_buflen);


  return 0;
}
