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

    char myChar[1];
    int pipePtC[2];             // pipe Parent to Child
    int pipeCtP[2];             // pipe Child to Parent
    int c_pid;                  // child pid
    int fd_file;
    
    char finalPrint[256];
    char command [128];
    int char_read;
    char buffer[128];
    memset(buffer, 0 , sizeof(buffer));
    sprintf(finalPrint, "Data received through pipe ");

    pipe(pipePtC);
    pipe(pipeCtP);

    // elegxw oti den einai -1
    if((c_pid = fork()) != 0)
    {
        /* Parent Code */
        close(pipePtC[0]);
        close(pipeCtP[1]);

        if ( (fd_file = open(pathFile, O_RDONLY)) < 0)  // anoigw arxeio (infile)
        {
            perror("Error reading\n");
        }   

        while( (char_read = read(fd_file, buffer,sizeof(buffer)) ) > 0)        // i thelei fd me th mia to arxeio
        {
            write(pipePtC[1], buffer, char_read);   // grafw sto input
            memset(buffer, 0, sizeof(buffer));
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

        //char* command = sprintf("s/",string1,"/",string2,"/g");  // command init ?
        dup2(pipePtC[0],0);
        dup2(pipeCtP[1],1);

        close(pipeCtP[1]);
        close(pipePtC[1]);

        sprintf(command, "s/%s/%s/g", string1, string2);
        execl("/usr/bin/sed", "sed", command, pathFile,(char*)0);
    }

    return 0;
}