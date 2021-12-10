#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void printWithPrefix(int fd, char* checkChar, char* printLine)
{
    int char_read;
    while( (char_read = read(fd, checkChar, 1) ) > 0)
    {
        if (strcmp(checkChar, "\n") == 0)
        {
            printf("%s\n", printLine);
            memset(printLine, 0, sizeof(printLine));
            sprintf(printLine, "Data received through pipe ");
        }
        else
        {   
            sprintf(printLine, "%s%s", printLine, checkChar);
        }
    }
}

void validateArgumentNumber(int argumentNumber, int rightNumber)
{
    if (argumentNumber == rightNumber)
    {
        return;
    }
    else if (argumentNumber > rightNumber)
    {
        printf("Too many arguments\n");
        exit(-1);
    }
    else
    {
        printf("Too few arguments\n");
        exit(-1);
    }
}