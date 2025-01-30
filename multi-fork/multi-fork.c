#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid, pid1, pid2;

  // fork a child process
  pid = fork();

  if (pid == 0) { // Child process
    // fork another child process
    pid1 = fork();

    if (pid1 == 0) { // Grandchild process
      // fork another child process
      pid2 = fork();

      if (pid2 == 0) { // Great-grandchild process
        printf("Level 3\n");
        return 0; // Terminate great-grandchild process
      } else {
        printf("Level 2\n");
        return 0; // Terminate grandchild process
      }
    } else {
      printf("Level 1\n");
      return 0; // Terminate child process
    }
  } else {
    printf("This is the root\n");
  }

  return 0; // Terminate root process
}