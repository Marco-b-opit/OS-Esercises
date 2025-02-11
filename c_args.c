#include <stdio.h>

int main(int arg_count, char *arg_values[]){

  if(arg_count < 2){
    printf("Usage %s <filename>\n", arg_values[0]);
  }

  printf("Total number of args: %d\n", arg_count);

  return 0;
}