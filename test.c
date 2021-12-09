#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

//sed s/str1/str2/g
// infile -> sed

int main(void)
{
    int pipePtC[2];             // pipe Parent to Child
    int pipeCtP[2];             // pipe Child to Parent
    int c_pid;                  // child pid
    int fd_file;
    int char_read;
    char* buffer[128];
    memset(buffer, 0 , sizeof(buffer));


    char* string1 = "ijkl";             //argv[1];
    char* string2 = "01af";             //argv[2];
    char* pathFile = "./infile.txt"     //argv[3];

    pipe(pipePtC);
    pipe(pipeCtP);

    // elegxw oti den einai -1
    if((c_pid = fork()) != 0)
    {
        /* Parent Code */
        close(pipePtC[0]);
        close(pipeCtP[1]);

        fd_file = open(pathFile, O_RDONLY);     // anoigw arxeio (infile)

        while( (char_read = read(fd_file, buffer,sizeof(buffer)-1)) > 0)        // i thelei fd me th mia to arxeio
        {
            write(pipePtC[1], buffer, char_read);   // grafw sto input
            memset(buffer, 0, sizeof(buffer));
        } 
        close(pipePtc[1]);

        while( (char_read = read(pipeCtP[0], buffer, sizeof(buffer)-1)) > 0)
        {
            printf("Edw: %s",char_read);
        }
        close(pipeCtP[0]);
    }
    else
    {
        /* Child Code */
        close(pipeCtP[0]);
        close(pipePtC[1]);

        char* command = sprintf("sed s/",string1,"/",string2,"/g");  // command init ?
        dup2(pipePtC[0],0);
        dup2(pipeCtP[1],1);
        close(pipeCtP[1]);
        close(pipePtC[1]);
        execl("usr/bin/sed", "sed", "s/ijklmno/010101/g", "./infile.txt",(char*)0);
    }

    return 0;
}






// char* path_file = "./infile.txt";
// char* str1 = "ijklmno";
// char* str2 = "01010101";

// int main()
// {
//     
//    

//     int fd[2];
//     int c_fd;
//     int fd_file;
//     pipe(fd);
//     fd_file = open(path_file);
//     dup2(fd_file,fd[0]);

//     c_fd = fork();
//     if(c_fd == 0)
//     {
//         close(fd[0]);
//         sprintf()
//         dup()
//         system()
//     }
//     else
//     {
//         close(fd[1]);
//     }
    
//     //dup infile me fd[0]
// }



// sed s/

/*
void test1()
{
    printf("Test1");
}
*/