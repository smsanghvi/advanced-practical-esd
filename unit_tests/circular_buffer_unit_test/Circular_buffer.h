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
​ * ​ ​ @file​ ​ Circular_buffer.h
​ * ​ ​ @brief​ ​ A header having declarations for various circular buffer​ operations
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 6 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */


#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#define MAX_SIZE 5

//declaring the structure and its fields
struct CircBuf_t
{   
    uint32_t *buff; // original memory location of buffer
    uint32_t *head; 
    uint32_t *tail;
    uint32_t size;  // size of the memory buffer 'buff'
    uint32_t count; //number of active elements in the buffer
};


//declaring an enum to encode buffer states
typedef enum {
	Buffer_Empty, 
	Buffer_Full, 
	Buffer_Ok, 
	Buffer_Full_Error, 
	Buffer_Empty_Error,
	Buffer_Null,
	Buffer_Initialized,
	Buffer_Deallocated
}bufferStates;   


/* Function that returns whether the buffer is empty or not
*  Inputs: reference to circular buffer
*  Return: Status code enum indicating whether buffer is empty
*/
bufferStates Is_buffer_empty(struct CircBuf_t **bufferptr);


/* Function that returns whether the buffer is full or not
*  Inputs: reference to circular buffer
*  Return: Status code enum indicating whether buffer is full
*/
bufferStates Is_buffer_full(struct CircBuf_t **bufferptr);


/* Function that adds a data item to the circular buffer
*  Inputs: reference to circular buffer and data to be added
*  Return: Status code enum indicating whether add was successful
*/
bufferStates add_item(struct CircBuf_t **circ_ptr, uint32_t data);


/* Function that removes data item from the circular buffer
*  Inputs: reference to circular buffer and data pointer to store popped result
*  Return: Status code enum indicating whether remove was successful
*/
bufferStates remove_item(struct CircBuf_t **bufferptr, uint32_t *data_ptr);


/* Function that initializes and allocates dynamic memory for the circular buffer
*  Inputs: reference to circular buffer and number of data items to be added
*  Return: Status code enum indicating whether allocation was successful
*/
bufferStates allocate(struct CircBuf_t **circ_ptr, uint32_t length);


/* Function that prints out the data items stored in the buffer
*  Inputs: reference to circular buffer
*  Return: void
*/
void dump(struct CircBuf_t **bufferptr);


/* Function that deallocates the circular buffer
*  Inputs: reference to circular buffer
*  Return: Status code enum indicating whether deallocation was successful
*/
bufferStates destroy_buffer(struct CircBuf_t **bufferptr);


/* Function that returns size of the circular buffer
*  Inputs: reference to circular buffer
*  Return: size of the circular buffer
*/
uint32_t size(struct CircBuf_t **bufferptr);

#endif
