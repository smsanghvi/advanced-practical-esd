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
​ * ​ ​ @file​ ​ test_cond.c
​ * ​ ​ @brief​ ​ An implementation source code file having function calls for various 
 *           pthread API functions involving conditional variables like pthread_cond_init,
 *           pthread_cond_wait, pthread_cond_signal, pthread_cond_destroy
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

int flag;
pthread_mutex_t mutex;
pthread_cond_t cond;


//starting function for child thread
void *function(void *args){
	printf("In child thread.\n");
	pthread_mutex_lock(&mutex);
	flag=1;
	pthread_cond_signal(&cond);
	printf("Signaling the sleeping thread to wake up.\n");
	pthread_mutex_unlock(&mutex);
}

//test function that main calls for demonstration purposes
void test_function(void){
	printf("Inside main's test function.\n");
	pthread_mutex_lock(&mutex);
	while(!flag){
		printf("Main's thread put to sleep.\n");
		pthread_cond_wait(&cond, &mutex);
	}
	printf("Main's thread wakes up.\n");
	pthread_mutex_unlock(&mutex);
}


int main(){

	pthread_t  tid;

	if(pthread_mutex_init(&mutex, NULL)){
		printf("Could not initialize mutex.\n");
		exit(1);
	}

	printf("Mutex initialized.\n");

	if(pthread_cond_init(&cond, NULL)){
		printf("Could not initialize condition variable.\n");
		exit(1);
	}
	printf("Condition variable initialized.\n");

	if(pthread_create(&tid, NULL, function, NULL)){
		printf("Could not create thread.\n");
		exit(1);
	}

	printf("In main thread.\n");

	test_function();

	printf("Back in main.\n");
	if(!pthread_cond_destroy(&cond))
		printf("Condition variable destroyed.\n");
	else
		printf("Unable to destroy condition variable.\n");

	return 0;

}