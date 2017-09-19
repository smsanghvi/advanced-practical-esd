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
​ * ​ ​ @file​ ​ doubly_linked_list.c
​ * ​ ​ @brief​ ​ An implementation source code file having definitions for various doubly linked-list​ operations
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 6 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include "doubly_linked_list.h"


/* Function that adds a linked list data node at the given position
*  Inputs: reference to linked list, data to be added, position at which to add
*  Return: Status code enum indicating status of the add operation
*/
status_code add_node(struct Node **head, uint32_t data, uint32_t position){
	int size1 = size(head);
	if(position<1 || position>(size1+1))
		return OUT_OF_BOUNDS;
	if(*head == NULL){
		(*head) = (struct Node*)malloc(sizeof(struct Node));
		(*head)->data = data;
		(*head)->prev = NULL;
		(*head)->next = NULL;
		if(*head == NULL)
			return MEMORY_ERROR;
		return SUCCESS;
	}
	else{
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		temp->data = data;
		temp->prev = NULL;
		temp->next = NULL;
		if(position == 1){	
			temp->next = *head;
			(*head)->prev = temp;
			*head = temp;
		}
		else{
			struct Node *temp1 = *head;
			int index = 1;		
			while(index < position-1){
				temp1 = temp1->next;
				index++;
			}
			temp->next = temp1->next;
			temp1->next = temp;	
			temp->prev = temp1;		
		}
		return SUCCESS;
	}
}


/* Function that removes a linked list data node from given position
*  Inputs: reference to linked list, position from which to remove, pointer that stores the data context 
*  Return: Status code enumeration indicating status of the remove operation
*/
status_code remove_node(struct Node **head, uint32_t position, uint32_t *data_context){
	int index = 1;
	int size1 = size(head);
	struct Node *temp = *head;
	if(position<1 || position>size1)
		return OUT_OF_BOUNDS;
	else if(position==1){
		*head = temp->next;
		(temp->next)->prev = NULL;
		*data_context = temp->data;
		free(temp);
	}
	else{
		while(index < (position - 1)){
			temp = temp->next;
			index++;
		}
		struct Node *temp1 = temp->next;
		temp->next = temp1->next;
		(temp1->next)->prev = temp;
		*data_context = temp1->data;
		free(temp1); 
	}
	return SUCCESS;
}


/* Function that destroys linked list by deleting all data nodes
*  Inputs: reference to linked list 
*  Return: Status code enumeration indicating status of the destroy operation
*/
status_code destroy(struct Node **head){
	if(*head == NULL)
		return EMPTY_LIST;
	struct Node *current = *head;
	struct Node *next;
	while(current!=NULL){
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;	
	return SUCCESS;
}


/* Function that prints out value of all the data nodes
*  Inputs: reference to linked list 
*  Return: void
*/
void Print(struct Node **head){
	struct Node *temp = *head;
	while(temp!=NULL){
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}


/* Function that searches for first instance of particular data item
*  Inputs: reference to linked list, data item to be searched, pointer storing the index of the searched data 
*  Return: Status code enumeration indicating whether data was found or not
*/
status_code search(struct Node **head, uint32_t search_data, uint32_t *index){
	struct Node *temp = *head;
	uint32_t flag = 0;
	uint32_t position = 1;
	while(temp!=NULL){
		if(temp->data == search_data){
			flag = 1;
			*index = position;
			break;
		}
		temp = temp -> next;
		position++;
	}
	if(flag)
		return SUCCESS;	
	return NOT_IN_LIST;
}


/* Function that returns current size of the doubly linked list
*  Inputs: reference to linked list 
*  Return: Integer size of the linked list
*/
uint32_t size(struct Node **head){
	struct Node *temp = *head;
	uint32_t size = 0;
	while(temp != NULL){
		size++;
		temp = temp->next;
	}
	return size;
}

