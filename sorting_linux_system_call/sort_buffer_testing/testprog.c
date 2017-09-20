/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
​ *   Users​ ​ are  permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded ​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ testprog.c
​ * ​ ​ @brief​ ​ Source file calling the system call defined by giving it the user defined buffer to be sorted.
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 19 ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define INPUT_SIZE 10

int main(){

	int32_t j = 0;
	srand(time(NULL));
	int32_t user_buffer[INPUT_SIZE];
	for(j=0; j<INPUT_SIZE; j++){
		user_buffer[j] = rand()%INPUT_SIZE;
	}
	int32_t result[INPUT_SIZE];
	printf("Starting system call.\n");
	printf("Before sorting: \n");
	int32_t i = 0;
	for(i = 0; i<INPUT_SIZE; i++){
		printf("%d ",user_buffer[i]);
	}
	printf("\nAfter sorting: \n");

	//calling system call	
	syscall(333, user_buffer, INPUT_SIZE, result);
	for(i = 0; i<INPUT_SIZE; i++){
		printf("%d ",result[i]);
	}
	printf("\nSystem call run complete.\n");
	return 0;
}
	
