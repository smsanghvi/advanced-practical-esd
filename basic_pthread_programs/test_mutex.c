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
​ * ​ ​ @file​ ​ test_mutex.c
​ * ​ ​ @brief​ ​ An implementation source code file having function calls for various 
 *           pthread API functions like pthread_create, pthread_join, pthread_exit,
 *           pthread_self, pthread_attr_getstacksize, pthread_attr_setstacksize, 
 *           pthread_attr_getguardsize, pthread_attr_setguardsize, pthread_mutex_init,
 *           pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_trylock, 
 *           pthread_mutex_unlock  
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ October ​ 4 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <syslog.h>
#include <sys/param.h>

int ret;
int data;
pthread_mutex_t mutex;

void *function(void *arg)
{
  printf("Inside thread!\n");
  printf("pthread_self value is %ld\n", pthread_self());

  //trying to lock mutex before accessing shared global resource
  if(!pthread_mutex_trylock(&mutex)){
    printf("Mutex locked.\n");
    ret = 10;
    //unlock mutex
    printf("Updated return value.\n");
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
   size_t stack_size, new_stack_size;
   size_t  guardsize, new_guardsize;

   if(pthread_mutex_init(&mutex, NULL)){
      printf("Error in locking mutex.\n");  
      exit(1);
   }

   printf("Mutex initialized.\n");

   pthread_attr_init(&attr);

   //return code of 0 means success
   if(pthread_attr_getstacksize(&attr, &stack_size)){
      printf("Get stack size threw an error. Exiting...\n");
      exit(1);
   }

   printf("Default stack size is %ld bytes.\n", stack_size);

   if(pthread_attr_getguardsize (&attr, &guardsize)){
      printf("Failed to get guard size for threads.\nExiting...");
      exit(1);
   }

   printf("Get guardsize returned a guard size of %ld bytes.\n", guardsize);

   //changing stack size to 16MB
   new_stack_size = 16777216;
   new_guardsize = 8192;

   if(pthread_attr_setstacksize(&attr, new_stack_size)){
      printf("Setting stack size unsuccessful.\n");
      exit(1);
   }

   if(pthread_attr_setguardsize(&attr, new_guardsize)){
      printf("Could not redefine the guard size.\nExiting...");
      exit(1);
   }

   if ( pthread_create(&tid, &attr, function, NULL) )
   {     
      printf("Cannot create thread\n");
      exit(1);
   }     
  
   printf("Inside main!\n");

   //return code of 0 means success
   if(pthread_attr_getstacksize(&attr, &new_stack_size)){
      printf("Get stack size threw an error. Exiting...\n");
      exit(1);
   }

   printf("New stack size after using pthread_attr_setstacksize: %ld bytes.\n", new_stack_size);

   if(pthread_attr_getguardsize (&attr, &guardsize)){
      printf("Failed to get guard size for threads.\nExiting...");
      exit(1);
   }

   printf("New guard size after using pthread_attr_setguardsize: %ld bytes.\n", new_guardsize);

   pthread_join(tid, (void **)(&local_ret));
   if(!pthread_mutex_destroy(&mutex))
      printf("Mutex destroyed.\n");
   else
      printf("Mutex not destroyed.\n");
   printf("Return value of function is %d\n", *local_ret);
      
   exit(0);
}