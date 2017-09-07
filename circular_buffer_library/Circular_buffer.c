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
​ * ​ ​ @file​ ​ Circular_buffer.c
​ * ​ ​ @brief​ ​ Source file having definitions for various features to be implemented for the circular buffer
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 6 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Circular_buffer.h"


/* Function that initializes and allocates dynamic memory for the circular buffer
*  Inputs: reference to circular buffer and number of data items to be added
*  Return: Status code enum indicating whether allocation was successful
*/
bufferStates allocate(struct CircBuf_t **bufferptr, uint32_t length){
	if(*bufferptr == NULL)
		return Buffer_Null;
	
	(*bufferptr) -> size = length;
	(*bufferptr) -> count = 0;
	(*bufferptr) -> buff = (uint32_t *)malloc((*bufferptr) -> size * sizeof(uint32_t));
	
	if((*bufferptr) -> buff == NULL)
		return Buffer_Null;
	(*bufferptr) -> head = (*bufferptr) -> buff;
	(*bufferptr) -> tail = (*bufferptr) -> buff;
	
	return Buffer_Initialized;
}


/* Function that returns whether the buffer is full or not
*  Inputs: reference to circular buffer
*  Return: Status code enum indicating whether buffer is full
*/
bufferStates Is_buffer_full(struct CircBuf_t **bufferptr){
	if((*bufferptr) -> count == (*bufferptr) -> size)
		return Buffer_Full;
	return Buffer_Ok;
}


/* Function that returns whether the buffer is empty or not
*  Inputs: reference to circular buffer
*  Return: Status code enum indicating whether buffer is empty
*/
bufferStates Is_buffer_empty(struct CircBuf_t **bufferptr){
	if((*bufferptr) -> count == 0)
		return Buffer_Empty;
	return Buffer_Ok;
}


/* Function that adds a data item to the circular buffer
*  Inputs: reference to circular buffer and data to be added
*  Return: Status code enum indicating whether add was successful
*/
bufferStates add_item(struct CircBuf_t **bufferptr, uint32_t data){
	if(Is_buffer_full(bufferptr) == Buffer_Full)
		return Buffer_Full_Error;
	(*bufferptr) -> count ++;
	if((*bufferptr) -> head == (*bufferptr) -> buff + (*bufferptr) -> size - 1)
		(*bufferptr) -> head = (*bufferptr) -> buff;
	else
		(*bufferptr) -> head ++; 		
	*((*bufferptr) -> head) = data;	
	return Buffer_Ok;
}


/* Function that removes data item from the circular buffer
*  Inputs: reference to circular buffer and data pointer to store popped result
*  Return: Status code enum indicating whether remove was successful
*/
bufferStates remove_item(struct CircBuf_t **bufferptr, uint32_t *data_ptr){
	if(Is_buffer_empty(bufferptr) == Buffer_Empty)
		return Buffer_Empty_Error;
	if((*bufferptr) -> tail == (*bufferptr) -> buff + (*bufferptr) -> size - 1)
		(*bufferptr) -> tail = (*bufferptr) -> buff;
	else
		(*bufferptr) -> tail ++; 
	(*bufferptr) -> count --;		
	*data_ptr = *((*bufferptr) -> tail);
	return Buffer_Ok;
}


/* Function that deallocates the circular buffer
*  Inputs: reference to circular buffer
*  Return: Status code enum indicating whether deallocation was successful
*/
bufferStates destroy_buffer(struct CircBuf_t **bufferptr){
	if(*bufferptr != NULL){
		free(*bufferptr);
		*bufferptr = NULL;
	}	
	return Buffer_Deallocated;
}


/* Function that prints out the data items stored in the buffer
*  Inputs: reference to circular buffer
*  Return: void
*/
void dump(struct CircBuf_t **bufferptr){
	int i;
	uint32_t *temp = (*bufferptr) -> tail;
	printf("Circular buffer sequence: ");
	for(i = 0; i < (*bufferptr) -> count ; i++){
		temp++;		
		printf("%d ", *temp);
	}
	printf("\n");
}


/* Function that returns size of the circular buffer
*  Inputs: reference to circular buffer
*  Return: size of the circular buffer
*/
uint32_t size(struct CircBuf_t **bufferptr){
	return (*bufferptr) -> count;
}

