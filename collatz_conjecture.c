/*
Name: Prasad Hajare
Program: Collatz conjecture
*/

#include  <stdio.h>
#include  <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void  ChildProcess1(int x);                                            /* child process prototype  */
void  ChildProcess2(int x);                                            /* parent process prototype */
void execute(int x, int y);

int  main(int argc, char *argv[])                                      //Main method
{
	if (argc == 1) {
		printf("Kindly provide the argument\n");
		exit(1);
    }

	int n = atoi(argv[1]);

	if(n < 1 || n > 39){
		printf("Please enter the value between 0 and 40\n");
		exit(1);
	}

     pid_t  pid;

     pid = fork();
     if (pid == 0)
          ChildProcess1(n);
     else
	 {
		 int returnStatus;
		 waitpid(pid, &returnStatus, 0);                      // Parent waits for the child process to get over

		if (returnStatus == 0)                                // Successful termination of the children processes
			printf("Children complete\n");
	 }
}

void ChildProcess1(int m)                                            //Method to execute Child process1
{
     int num = m;

	 printf("From Child 1 init n=%d\n",num);
	 execute(num, 1);

	 pid_t  pid1;
	 pid1 = fork();

	 if (pid1 == 0)
          ChildProcess2(m);
	 else
	 {
		 int returnStatus;
		 waitpid(pid1, &returnStatus, 0);                   // Parent waiting for the child process to get over
	 }
}

void ChildProcess2(int k)                                          //Method to execute Child process2
{
     int num = k + 3;
	 printf("From Child 2 init n=%d\n",num);
	 execute(num, 2);
}

void execute(int num, int child)                                  //Method to execute Collatz conjecture
{
	while(num != 1){
		 if(num%2 == 0){
			 num = num / 2;
			 printf("From Child %d %d\n", child, num);
		 }else{
			 num = num*3 + 1;
			 printf("From Child %d %d\n", child, num);
		 }
	 }
}
