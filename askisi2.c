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
    char* string1 = argv[2];
    char* string2 = argv[3];
    char* pathFile = argv[1];

    int pipePtC[2];             // pipe Parent to Child
    int pipeCtP[2];             // pipe Child to Parent
    int c_pid;                  // child pid
    int fd_file;                // fd gia to open
    
    char command [128];
    int char_read;

    // buffers
    char myChar[2];
    memset(myChar,0,2);

    char buffer[256];
    memset(buffer, 0 , sizeof(buffer));

    validateArgumentNumber(argc, 4);            // elegxei plithos arguments

    /* Create Pipes */
    if (pipe(pipePtC) < 0)                      // pipe Parent to Child
    {
        perror("Pipe Parent to Child error ");
        exit(-1);
    }
    if (pipe(pipeCtP) < 0)                      // pipe Child to Parent
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

        if ( (fd_file = open(pathFile, O_RDONLY)) < 0)  // open File
        {
            perror("Open source failed ");
            exit(-1);
        }   

        //Read File
        while( (char_read = read(fd_file, buffer,sizeof(buffer)-1) ) > 0)   
        {
            //Write sto Child-pipe
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

        printWithPrefix(pipeCtP[0], myChar, buffer);        // prosthetei se kathe \n to prefix (Data..)
        close(pipeCtP[0]);
    }
    else
    {
        /* Child Code */
        close(pipeCtP[0]);
        close(pipePtC[1]);

        dup2(pipePtC[0],0);         // input apo pipe me Parent
        dup2(pipeCtP[1],1);         // output se pipe me Parent

        close(pipeCtP[1]);
        close(pipePtC[0]);

        sprintf(command, "s/%s/%s/g", string1, string2);            // command pou tha bei sto exec
        execl("/usr/bin/sed", "sed", command, pathFile,(char*)0);

        perror("Sed exec didnt work ");                             // de tha ektelestei an piasei exec
        exit(-1);
    }

    return 0;
}