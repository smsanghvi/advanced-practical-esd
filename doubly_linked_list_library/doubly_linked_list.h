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
​ * ​ ​ @file​ ​ doubly_linked_list.h
​ * ​ ​ @brief​ ​ A header having declarations for various doubly linked-list​ operations
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 6 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

//Creating the doubly linked list structure
struct Node{
	uint32_t data;
	struct Node* prev;
	struct Node* next;
};

//Enumeration to show status codes
typedef enum{
	SUCCESS,
	MEMORY_ERROR,
	OUT_OF_BOUNDS,
	NOT_IN_LIST,
	EMPTY_LIST
}status_code;


/* Function that adds a linked list data node at the given position, position starting from 1
*  Inputs: reference to linked list, data to be added, position at which to add
*  Return: Status code enum indicating status of the add operation
*/
status_code add_node(struct Node **head, uint32_t data, uint32_t position);


/* Function that removes a linked list data node from given position
*  Inputs: reference to linked list, position from which to remove, pointer that stores the data context 
*  Return: Status code enumeration indicating status of the remove operation
*/
status_code remove_node(struct Node **head, uint32_t position, uint32_t *data_context);


/* Function that destroys linked list by deleting all data nodes
*  Inputs: reference to linked list 
*  Return: Status code enumeration indicating status of the destroy operation
*/
status_code destroy(struct Node **head);


/* Function that returns current size of the doubly linked list
*  Inputs: reference to linked list 
*  Return: Integer size of the linked list
*/
uint32_t size(struct Node **head);

//Function to return result of search
status_code search(struct Node **head, uint32_t search_data, uint32_t *index);


/* Function that prints out value of all the data nodes
*  Inputs: reference to linked list 
*  Return: void
*/
void Print(struct Node **head);

#endif
