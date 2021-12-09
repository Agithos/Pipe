#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>


int main(){
	int n, fd[2];
	pid_t pid;
	char line[48];
	memset(line,0,sizeof(line));

	if (pipe(fd) < 0){
		perror("pipe error :");
		return 1;
	}
	if ( (pid = fork()) < 0){
		perror("fork error : ");
		return 1;
	}
	if (pid == 0) {		/* child */
		close(fd[0]);
		write(fd[1], "Hello from child.\n", sizeof(line));
		return 0;

	} 
	else {			/* parent */
		close(fd[1]);
		n = read(fd[0], line, sizeof(line));
	printf("Number of received chars = %d\n",n);
		printf("Parent receives : %s",line);
		return 0;
	}

}
