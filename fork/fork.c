#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork(); // First fork
    printf("%d", pid1);

    if (pid1 == 0) {
        // First child process
        printf("First child process\n");
    } else {
        // Parent process
        printf("Parent process\n");

        pid2 = fork(); // Second fork

        if (pid2 == 0) {
            // Second child process
            printf("Second child process\n");
        } else {
            // Parent process again
            printf("Second child process\n");
        }
    }

    return 0;
}