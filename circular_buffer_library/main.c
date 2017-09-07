/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
​ *
​ * ​ ​ Redistribution,​ ​ modification​ ​ or​ ​ use​ ​ of​ ​ this​ ​ software​ ​ in​ ​ source​ ​ or​ ​ binary
​ * ​ ​ forms​ ​ is​ ​ permitted​ ​ as​ ​ long​ ​ as​ ​ the​ ​ files​ ​ maintain​ ​ this​ ​ copyright.​ ​ Users​ ​ are
​ * ​ ​ permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded
​ * ​ ​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for
​ * ​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ main.c
​ * ​ ​ @brief​ ​ Main having function calls to test various features of the circular buffer.
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 6 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Circular_buffer.h"

int main(){

	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	uint32_t data_ptr = 0;
	if(allocate(&bufferptr, MAX_SIZE) == Buffer_Initialized)
		printf("Buffer initialization successful.\n");
	else
		printf("Buffer not initialized.\n");
	if(add_item(&bufferptr, 5) == Buffer_Ok)
		printf("Data item 5 added.\n"); 
	dump(&bufferptr);
	if(add_item(&bufferptr, 3) == Buffer_Ok)
		printf("Data item 3 added.\n"); 
	dump(&bufferptr);
	if(add_item(&bufferptr, 7) == Buffer_Ok)
		printf("Data item 7 added.\n"); 
	dump(&bufferptr);
	if(add_item(&bufferptr, 9) == Buffer_Ok)
		printf("Data item 9 added.\n"); 
	dump(&bufferptr);
	if(add_item(&bufferptr, 1) == Buffer_Ok)
		printf("Data item 1 added.\n"); 
	dump(&bufferptr);
	printf("Current size of circular buffer is %d\n", size(&bufferptr));
	remove_item(&bufferptr, &data_ptr);
	printf("Data popped is %d\n", data_ptr);
	dump(&bufferptr);
	remove_item(&bufferptr, &data_ptr);
	printf("Data popped is %d\n", data_ptr);
	dump(&bufferptr);
	if(add_item(&bufferptr, 4) == Buffer_Ok)
		printf("Data item 4 added.\n"); 
	dump(&bufferptr);
	if(destroy_buffer(&bufferptr) == Buffer_Deallocated)
		printf("Circular buffer deallocated.\n");

return 0;
}

