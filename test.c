#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2]; // file descriptors for pipe
    pid_t pid1, pid2;

    if (pipe(fd) == -1) { // create the pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork(); // create the first child process
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) { // first child process
        close(fd[0]); // close the read end of the pipe
        int data1 = 10;
        write(fd[1], &data1, sizeof(data1)); // write data to the pipe
        exit(EXIT_SUCCESS);
    }

    pid2 = fork(); // create the second child process
    if (pid2 == -1 && pid1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) { // second child process
        close(fd[1]); // close the write end of the pipe
        int data2;
        read(fd[0], &data2, sizeof(data2)); // read data from the pipe
        printf("Data received from child process 1: %d\n", data2);
        exit(EXIT_SUCCESS);
    }

    close(fd[0]); // close the read end of the pipe in parent process
    close(fd[1]); // close the write end of the pipe in parent process
    waitpid(pid1, NULL, 0); // wait for the first child process to terminate
    waitpid(pid2, NULL, 0); // wait for the second child process to terminate
    exit(EXIT_SUCCESS);
}
