#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ask2_help.h"

int main(int argc, char* argv[])
{
    char* string1 = "ijkl"; //argv[2];
    char* string2 = "0101"; //argv[3];
    char* pathFile = argv[1];

    char myChar[2];
    memset(myChar,0,2);
    int pipePtC[2];             // pipe Parent to Child
    int pipeCtP[2];             // pipe Child to Parent
    int c_pid;                  // child pid
    int fd_file;
    
    char finalPrint[512];
    memset(finalPrint, 0, sizeof(finalPrint));
    char command [128];
    int char_read;
    char buffer[256];
    memset(buffer, 0 , sizeof(buffer));

    validateArgumentNumber(argc, 2);    //4

    /* Create Pipes */
    if (pipe(pipePtC) < 0)
    {
        perror("Pipe Parent to Child error ");
        exit(-1);
    }
    if (pipe(pipeCtP) < 0)
    {
        perror("Pipe Child to Parent error ");
        exit(-1);
    }

    /* Make Fork */
    if( (c_pid = fork()) < 0)
    {
        perror("Fork error ");
        exit(-1);
    }
    if (c_pid != 0)
    {
        /* Parent Code */
        close(pipePtC[0]);
        close(pipeCtP[1]);

        if ( (fd_file = open(pathFile, O_RDONLY)) < 0)  // anoigw arxeio (infile)
        {
            perror("Open source failed ");
            exit(-1);
        }   

        while( (char_read = read(fd_file, buffer,sizeof(buffer)-1) ) > 0)        // i thelei fd me th mia to arxeio
        {
            if ( (write(pipePtC[1], buffer, char_read)) != char_read)   //write error check
            {
                perror("Write error ");
                exit(-1);
            };
            memset(buffer, 0, sizeof(buffer));
        } 
        if (char_read < 0)                                              // read error check
        {
            perror("Read error ");
            exit(-1);
        }

        close(pipePtC[1]);
        wait(0);

        printWithPrefix(pipeCtP[0], myChar, finalPrint);
        close(pipeCtP[0]);
    }
    else
    {
        /* Child Code */
        close(pipeCtP[0]);
        close(pipePtC[1]);

        dup2(pipePtC[0],0);
        dup2(pipeCtP[1],1);

        close(pipeCtP[1]);
        close(pipePtC[1]);

        sprintf(command, "s/%s/%s/g", string1, string2);
        execl("/usr/bin/sed", "sed", command, pathFile,(char*)0);

        perror("Sed exec didnt work ");
        exit(-1);
    }

    return 0;
}