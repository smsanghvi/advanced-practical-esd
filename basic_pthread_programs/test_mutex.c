#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <syslog.h>
#include <sys/param.h>

#define _GNU_SOURCE   /* To get pthread_getattr_np() declaration */

int ret;
int data;
pthread_mutex_t mutex;

void *function(void *arg)
{
  printf("Inside thread!\n");
  printf("pthread_self value is %d\n", pthread_self());

  //trying to lock mutex before accessing shared global resource
  if(!pthread_mutex_trylock(&mutex)){
  	printf("Mutex locked.\n");
	ret = 10;
	//unlock mutex
	pthread_mutex_unlock(&mutex);
	printf("Mutex unlocked.\n");
	pthread_exit(&ret); 
  }
  printf("Could not lock mutex.\n");
  pthread_exit(NULL); 
}


int main(int argc, char *argv[])
{
   pthread_t  tid;
   pthread_attr_t attr;
   int *local_ret;

   if(pthread_mutex_init(&mutex, NULL)){
   		printf("Error in locking mutex.\n");	
   		exit(1);
   }

   printf("Mutex initialized.\n");

   pthread_attr_init(&attr);

   if ( pthread_create(&tid, &attr, function, NULL) )
   {	   
      printf("Cannot create thread\n");
      exit(1);
   }	   
 	
   printf("Inside main!\n");

   pthread_join(tid, (void **)(&local_ret));
   if(!pthread_mutex_destroy(&mutex))
   		printf("Mutex destroyed.\n");
   else
   		printf("Mutex not destroyed.\n");
   printf("Return value of function is %d\n", *local_ret);
 	    
   exit(0);
}