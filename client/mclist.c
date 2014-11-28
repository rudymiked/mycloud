/***************************

file: mclist.c

RUDY BROOKS

******************************/



#include "../Libcalls.c"
#include "stdio.h"
#include "stdlib.h"



int main(int argc, const char *argv[]){

  int datalen = 0;
  char *data;

  char *machine_name = argv[1];
  int tcp_port     = (int)argv[2][0] - '0';
  int secret_key   = (int)argv[3][0] - '0';  

  mycloud_getlist(machine_name, tcp_port, secret_key, file_name, data, datalen);


  return 0;
}
