#include "pipex.h"

void    redirect(const char *file, char option)
{
    int fd;

    if (option == 'i')
    {
        fd = open(file, O_RDONLY, 0444);
        fd = dup2(fd, STDIN_FILENO);
    }
    else if (option == 'o')
    {
        fd = open(file, O_RDONLY, 0222);
        fd = dup2(fd, STDOUT_FILENO);
    }
    if (fd == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}