#include <unistd.h>
#include <string.h>
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