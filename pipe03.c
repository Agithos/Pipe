#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

// gcc -o ??? ???.c -lm

double sum_sqrt(int,int);

int main(){
	int n, fd[2];
	pid_t pid;
	double par,chi;

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
		chi = sum_sqrt(1000,2000);
		printf("child's sum = %1f\n",chi);
		write(fd[1], &chi, sizeof(chi));
		printf("child finished\n");
		return 0;

	} 
	else {			/* parent */
		close(fd[1]);
		double temp = sum_sqrt(2000,3000);
		wait(0);
		n = read(fd[0], &par, sizeof(par));
		printf("Number of received chars = %d\n",n);
		printf("Parent wiht id: %d receives : %1f\n",getpid(),par);
		printf("total sum = %1f\n",par+temp);
		return 0;
	}

}

double sum_sqrt(int a,int b){
	double s = 0;
	for(int i = a; i<b; i++){
		s += sqrt(i);
	}
	return s;	
}
