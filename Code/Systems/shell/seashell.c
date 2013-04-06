#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "shell.h"

int main(){
  /*  int check = prompt();
  while(check == 1)
    check = prompt();
  printf("exited");
  */
  while(1)
    prompt();
  return 0;
}
