#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int sum_up(int,int);

int main(){
	int n, fd[2],fda[2];
	pid_t pid;
	char line[64];
	memset(line,0,sizeof(line));

	if (pipe(fd) < 0){
		perror("pipe error :");
		return 1;
	}
	if (pipe(fda) < 0){
		perror("pipe error :");
		return 1;
	}
	if ( (pid = fork()) < 0){
		perror("fork error : ");
		return 1;
	}
	if (pid == 0) {		/* child */
		close(fd[0]);
		sprintf(line,"Hello from child with id: %d  my sum = %d\n",getpid(),sum_up(0,20000));
		write(fd[1], line, sizeof(line));
	
		return 0;

	} 
	else {			/* parent */
		if ( (pid = fork()) < 0){
			perror("fork error : ");
			return 1;
		}
		if (pid == 0) {		/* child */
			close(fda[0]);
			sprintf(line,"Hello from child with id: %d  my sum = %d\n",getpid(),sum_up(20000,40000));
			write(fda[1], line, sizeof(line));
	
			return 0;

		} 
		close(fd[1]);
		n = read(fd[0], line, sizeof(line));
		printf("Number of received chars = %d\n",n);
		printf("Parent wiht id: %d receives : %s",getpid(),line);
		close(fda[1]);
		n = read(fda[0], line, sizeof(line));
		printf("Number of received chars = %d\n",n);
		printf("Parent wiht id: %d receives : %s",getpid(),line);
		system("ps");
		return 0;
	}

}

int sum_up(int a,int b){
	int s = 0;
	for(int i = a; i<b; i++){
		s += i;
	}
	return s;	
}
