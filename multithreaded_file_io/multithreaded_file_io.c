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
​ * ​ ​ @file​ ​ multithreaded_file_io.c
​ * ​ ​ @brief​ ​ An implementation source code file having 3 threads executing within
 *			 a process to implement the feature of multithreaded file io using signals.
 *			 This program makes use of a producer-consumer model wherein the parent thread
 *			 accepts file data from the user at command line and on receving a user signal
 *			 spawns a new thread to process the user data to generate number of characters,
 *			 words and lines. On receiving another signal from the user, the statistics are
 *			 printed out to the console window.  
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
#include <math.h>
#include <sys/param.h>
#include <string.h>
#include <stdint.h>

#define MAXLINE 10000

pthread_t thread2, thread3;
pthread_attr_t thread2_attr;
pthread_attr_t thread3_attr;
char buffer[MAXLINE];
char name[MAXLINE];
struct sigaction sig1, sig2, sig3;
sigset_t block_mask, block_mask1, block_mask2;
volatile int flag = 0;
volatile int flag1 = 0;
pthread_mutex_t mutex, mutex1;
pthread_cond_t cond, cond1;
int rc, rc1;
FILE *fp;
volatile int file_open = 0;


typedef struct{
	uint32_t words;
	uint32_t lines;
	uint32_t characters;
}data; 

data *data_ptr;


//signal handler for SIGUSR1
void sig1_handler (int sig)
{
 	pthread_mutex_lock(&mutex);
 	flag=1;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
}


//signal handler for SIGUSR2
void sig2_handler (int sig)
{
 	pthread_mutex_lock(&mutex1);
 	flag1=1;
	pthread_cond_signal(&cond1);
	pthread_mutex_unlock(&mutex1);
}


//signal handler for graceful process exit
void sigint_handler (int sig)
{
	//freeing up dynamic memory allocated for structure
	free(data_ptr);
	//checking flag to see if file is open
	if(file_open)
		fclose(fp);
	printf("\nCleanup successful! \nExiting...\n");
	exit(0);
}


void *thread3_fn(void *threadid){
	pthread_mutex_lock(&mutex1);
	while(!flag1)
		pthread_cond_wait(&cond1, &mutex1);
	pthread_mutex_unlock(&mutex1);

	printf("\nStatistics\n------------------------\n");
	pthread_mutex_lock(&mutex1);
	printf("No. of words is %d\n", data_ptr -> words);
	printf("No. of lines is %d\n", data_ptr -> lines);
	printf("No. of characters is %d\n", data_ptr -> characters);
	pthread_mutex_unlock(&mutex1);

}


void *thread2_fn(void *threadid){
	pthread_mutex_lock(&mutex);
	while(!flag)
		pthread_cond_wait(&cond, &mutex);
	pthread_mutex_unlock(&mutex);

	data_ptr = (data *)malloc(sizeof(data));

	printf("Processing the data...\n\n");
	data_ptr->lines = 0;
	data_ptr->characters = 0;
	data_ptr->words = 0;

	int line_count = 0;
	int word_count = 0;
	int character_count = 0;
	char c, old_c;

	fp = fopen(name, "r");
	if(fp!=NULL){
		file_open = 1;
		while((c=getc(fp))!=EOF){
			//incrementing the characters
			if(c!=' ' && c!='\n')
				++character_count;
			//incrementing the words and not counting spaces twice 
			if((c==' ' || c=='\n') && (c!=old_c))
				++word_count;
			//incrementing the line count
			if(c=='\n')
				++line_count;
			
			old_c = c;
		}
	}
	fclose(fp);
	file_open = 0;

	pthread_mutex_lock(&mutex);
	data_ptr -> words = word_count;
	data_ptr -> lines = line_count;
	data_ptr -> characters = character_count;
	pthread_mutex_unlock(&mutex);

	rc1 = pthread_create (& thread3 , & thread3_attr , thread3_fn , ( void *) 0 );
	if (rc1)
	{
    	printf("ERROR in creating thread1; pthread_create() rc is %d\n", rc); 
    	perror(NULL); 
    	exit(-1);
	}

	printf("Waiting for signal 2 from user...\n");

}


int main (int argc, char *argv[]){
	pthread_attr_init (&thread2_attr);	
	pthread_attr_init (&thread3_attr);	

	//initializing mutex
	if(pthread_mutex_init(&mutex, NULL)){
		printf("Could not initialize mutex.\n");
		exit(1);
	}

	//initializing condition variable
	if(pthread_cond_init(&cond, NULL)){
		printf("Could not initialize condition variable.\n");
		exit(1);
	}

	//initializing mutex
	if(pthread_mutex_init(&mutex1, NULL)){
		printf("Could not initialize mutex.\n");
		exit(1);
	}

	//initializing condition variable
	if(pthread_cond_init(&cond1, NULL)){
		printf("Could not initialize condition variable.\n");
		exit(1);
	}

	printf("Enter file name to open: ");
	fgets(name, MAXLINE, stdin);
	fp = fopen(name, "w"); 
	memset(buffer, 0, MAXLINE);

	if(fp == NULL){
		printf("Requested file does not exist.\n\n");
	}

	else{
		file_open = 1;
		printf("Opened %s\n", name);
		printf("Enter the file contents (press Ctrl+D when done):\n");
		while(fgets(buffer, MAXLINE, stdin) != NULL){
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
		}
		fclose(fp);
		file_open = 0;
		rc = pthread_create (& thread2 , & thread2_attr , thread2_fn , ( void *) 0 );
		if (rc)
		{
    		printf("ERROR in creating thread1; pthread_create() rc is %d\n", rc); 
    		perror(NULL); 
    		exit(-1);
		}

		/* Registering the signal handler. */
  		sigfillset (&block_mask);
  		sig1.sa_handler = sig1_handler;
  		sig1.sa_mask = block_mask;
  		sig1.sa_flags = 0;
  		sigaction (SIGUSR1, &sig1, NULL);

  		printf("\nWaiting for signal 1 from user...\n");

  		/* Registering the signal handler. */
  		sigfillset (&block_mask1);
  		sig2.sa_handler = sig2_handler;
  		sig2.sa_mask = block_mask1;
  		sig2.sa_flags = 0;
  		sigaction (SIGUSR2, &sig2, NULL);	

  		/*registering the cleanup handler for SIGINT for graceful exit*/ 
  		sig3.sa_handler = sigint_handler;
  		sig3.sa_flags = 0;
  		sigaction (SIGINT, &sig3, NULL);	
	}

	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	free(data_ptr);

	if(pthread_cond_destroy(&cond))
		printf("Condition variable 1 not destroyed.\n");
	if(pthread_cond_destroy(&cond1))
		printf("Condition variable 2 not destroyed.\n");	
   if(pthread_mutex_destroy(&mutex))
   		printf("Mutex 1 not destroyed.\n");
   if(pthread_mutex_destroy(&mutex1))
   		printf("Mutex 2 not destroyed.\n");

	return 0;
}