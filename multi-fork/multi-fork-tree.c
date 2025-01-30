#include <stdio.h>
#include <unistd.h>

int main(){
  pid_t pid, pid1, pid2;

  pid = fork();
  if (pid == 0) { // 2^1 = 2 processes
      // Child process
      printf("1. Child process: pid = %d, fork() returned = %d\n", getpid(), pid);
  } else {
      // Parent process
      printf("1. Parent process: pid = %d, fork() returned = %d\n", getpid(), pid);
  }

  pid1 = fork(); // 2ˆ2 = 4 processes
  if (pid1 == 0) {
      // Child process
      printf("2. Child process: pid = %d, fork() returned = %d\n", getpid(), pid1);
  } else {
      // Parent process
      printf("2. Parent process: pid = %d, fork() returned = %d\n", getpid(), pid1);
  }

  pid2 = fork(); //  2^3 = 8 processes
  if (pid2 == 0) {
      // Child process
      printf("3. Child process: pid = %d, fork() returned = %d\n", getpid(), pid2);
  } else {
      // Parent process
      printf("3. Parent process: pid = %d, fork() returned = %d\n", getpid(), pid2);
  }

  return 0;

}