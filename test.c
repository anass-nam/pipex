#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("dd", O_RDWR | O_CREAT | O_TRUNC);
    char    buff[10];
    write(fd, "anass nammal", 12);
    write(fd, "\n", 1);
    close(fd);
    return 0;
}
