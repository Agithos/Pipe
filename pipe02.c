#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int sum_up(int,int);

int main(){
	int n, fd[2];
	pid_t pid;
	int par,chi;

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
		chi = sum_up(1000,2000);
		printf("child's sum = %d\n",chi);
		write(fd[1], &chi, sizeof(chi));
		printf("child finished\n");
		return 0;

	} 
	else {			/* parent */
		close(fd[1]);
		int temp = sum_up(2000,3000);
		wait(0);
		n = read(fd[0], &par, sizeof(par));
		printf("Number of received chars = %d\n",n);
		printf("Parent wiht id: %d receives : %d\n",getpid(),par);
		printf("total sum = %d\n",par+temp);
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
