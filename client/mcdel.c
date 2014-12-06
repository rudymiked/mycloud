/****************************************************

file: mydel.c

RUDY BROOKS

*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "LibCalls.c"

int main(int argc, char *argv[]) {

  char *machine_name = argv[1];
  int tcp_port     = (int)argv[2][0] - '0';
  int secret_key   = (int)argv[3][0] - '0';   
  char *file_name  = argv[4];


  //run Libary/API call
  mycloud_delfile(machine_name, tcp_port, secret_key, file_name);

  /******DEBUGGING********************
  int i;
  for(i=1;i<5;++i)
    printf("%d : %s \n", i, argv[i]);
  ************************************/

  return 0;
}
