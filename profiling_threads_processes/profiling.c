/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
​ *
​ * ​ ​ Redistribution,​ ​ modification​ ​ or​ ​ use​ ​ of​ ​ this​ ​ software​ ​ in​ ​ source​ ​ or​ ​ binary
​ * ​ ​ forms​ ​ is​ ​ permitted​ ​ strictly for educational purposes.​ ​ Users​ ​ are
​ * ​ ​ permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded
​ * ​ ​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for
​ * ​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ profiling.c
​ * ​ ​ @brief​ ​ An implementation source code file profiling the creation of pthreads
 *           and processes (fork+execvp) using the clock() function in the time.h 
 *           standard header
 *	 @implementation  Pay attention to the #define for threads and processes 
 *					  #define FORK_EXECV_PROCESS : for profiling process creation
 *					  #define PTHREAD_CREATE : for profiling pthread 	
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ October ​ 4 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FORK_EXECV_PROCESS
//#define PTHREAD_CREATE

clock_t start, end;
double cpu_time_used;


void *fn(void *threadid)
{
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used for pthread_create is %f ms\n", cpu_time_used*1000 );
	printf("In thread's startup function\n");
}


#ifdef FORK_EXECV_PROCESS
int main(int argc, char *argv[])
{
	pid_t pid;
	char *args[2];
  args[0] = "/bin/ls";     
  args[1] = NULL; 

  start = clock();
	if((pid = fork()) == 0){
		execvp( "./child", NULL );
	}	
	else if(pid == -1){
		printf("Fork was unsuccessful.\n");
		exit(1);
	}
	else{
		wait(NULL);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used for fork and exec is %f ms\n", cpu_time_used*1000 );
		printf("In parent process.\n");
	}

   return 0;
}
#endif


#ifdef PTHREAD_CREATE
int main(int argc, char *argv[]){
	pthread_t thread;
	int rc;
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	start = clock();
  rc = pthread_create (&thread , &attr , fn , ( void *) 0 );
	pthread_join ( thread , NULL );
	return 0;
}
#endif