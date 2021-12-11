#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Print kathe line tou apotelesmatos me prefix to "Data received.."
void printWithPrefix(int fd, char* checkChar, char* printLine)
{
    int char_read;
    while( (char_read = read(fd, checkChar, 1) ) > 0)
    {
        if (strcmp(checkChar, "\n") != 0)                           // otan den einai new Line
        {
            sprintf(printLine, "%s%s", printLine, checkChar);       // append to Char sto printLine
        }
        else
        {   
            printf("Data received through pipe %s\n", printLine);   // an \n -> print kai svinw printLine
            memset(printLine, 0, sizeof(printLine));
        }
    }
    if (char_read < 0)              // read error check
    {
        perror("Read error ");
        exit(-1);
    }
}

// Validate oti arithmos twn Arguments einai swstos
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