#include <stdio.h>
#include <stdlib.h>
#define A3 0x4
#define A4 0x8
void bit(unsigned char option)
{
    if (option & EXIT_SUCCESS)
        printf("1\n");
    if (option & EXIT_FAILURE)
        printf("2\n");
    if (option & A3)
        printf("3\n");
    if (option & A4)
        printf("4\n");
}

int main(int argc, char const *argv[])
{
    bit(EXIT_SUCCESS | EXIT_FAILURE | A3 | A4);
    return 0;
}
