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
​ * ​ ​ @brief​ ​ Main.c to execute all the features defined in the doubly linked list source code
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 6 ​ ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "doubly_linked_list.h"


int main(){
	struct Node *head = NULL;
	uint32_t *index;
	uint32_t data_context;
	if(add_node(&head, 5,1) == SUCCESS)
		printf("Successully added node 5 at position 1. Data sequence is :");
	Print(&head);
	if(add_node(&head, 7,2) == SUCCESS)
		printf("Successully added node 7 at position 2. Data sequence is :");
	Print(&head);
	if(add_node(&head, 9,1) == SUCCESS)
		printf("Successully added node 9 at position 1. Data sequence is :");
	Print(&head);
	if(add_node(&head, 2,3) == SUCCESS)
		printf("Successully added node 2 at position 3. Data sequence is :");
	Print(&head);
	if(add_node(&head, 6,2) == SUCCESS)
		printf("Successully added node 6 at position 2. Data sequence is :");
	Print(&head);
	if(remove_node(&head, 1, &data_context) == SUCCESS)
		printf("Successfully removed node from position 1. Data sequence is :");
	Print(&head);
	printf("Data removed is %d\n",data_context);
	if(remove_node(&head, 2, &data_context) == SUCCESS)
		printf("Successfully removed node from position 2. Data sequence is :");
	Print(&head);
	printf("Data removed is %d\n",data_context);
	if(add_node(&head, 21,1) == SUCCESS)
		printf("Successully added node 21 at position 1. Data sequence is :");
	Print(&head);
	if(remove_node(&head, 3, &data_context) == SUCCESS)
		printf("Successfully removed node from position 3. Data sequence is :");
	Print(&head);	
	printf("Data removed is %d\n",data_context);

	printf("Current size of doubly linked list is %d\n",size(&head));

	if(search(&head, 6, index) == SUCCESS)
		printf("Element 6 present at index %d.\n", *index);
	else
		printf("Element 6 not present.\n");

	if(destroy(&head) == SUCCESS)
		printf("Deleting linked list successful.\n");
	else if(destroy(&head) == EMPTY_LIST)
		printf("Linked list already empty.\n");
	else
		printf("Error in deleting linked list.\n");
	return 0;
}
