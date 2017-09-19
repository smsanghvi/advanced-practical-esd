/****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
 *   This file makes use of CMocka licensed by Apache License 2.0
​ * ​ ​ Redistribution,​ ​ modification​ ​ or​ ​ use​ ​ of​ ​ this​ ​ software​ ​ in​ ​ source​ ​ or​ ​ binary ​ forms​ ​ is​ ​ permitted​ ​ as​ ​ long​ ​ as​ ​ the​ ​ files​ ​ maintain​ ​ this​ ​ copyright.​ ​ Users​ ​ are​ ​ permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for any​ ​ misuse​ ​ of​ ​ this​ ​ material.
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ test_doubly_linked_list.c
​ * ​ ​ @brief​ ​ A unit test file using CMocka to test all implemented functions in doubly linked list
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September 19​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "doubly_linked_list.h"


//test to add a node at the head
void test_add_node_head(void **state){
	struct Node *head = NULL;
	assert_int_equal(add_node(&head, 5,1), SUCCESS);
}


//test to add node at 3rd position given that 3 or more nodes exist
void test_add_node_middle(void **state){
	struct Node *head = NULL;
	add_node(&head, 5,1);
	add_node(&head, 6,2);
	add_node(&head, 9,3);
	add_node(&head, 2,4);	
	assert_int_equal(add_node(&head, 5, 3), SUCCESS);
}


//test to add node at tail
void test_add_node_tail_case1(void **state){
	struct Node *head = NULL;
	add_node(&head, 5,1);
	add_node(&head, 6,2);
	add_node(&head, 9,3);
	add_node(&head, 2,4);	
	assert_int_equal(add_node(&head, 5, 5), SUCCESS);
}


//test to add node at 5th position given that only 3 nodes exist
void test_add_node_tail_case2(void **state){
	struct Node *head = NULL;
	add_node(&head, 5,1);
	add_node(&head, 6,2);
	add_node(&head, 9,3);	
	assert_int_not_equal(add_node(&head, 5, 5), SUCCESS);
}


//test to remove node from 3rd position provided 3+ nodes exist
void test_remove_node(void **state){
	struct Node *head = NULL;
	uint32_t data;
	add_node(&head, 5,1);
	add_node(&head, 6,2);
	add_node(&head, 9,3);	
	add_node(&head, 11,4);
	assert_int_equal(remove_node(&head, 3, &data), SUCCESS);
}


//test to remove node from 3rd position provided only 2 nodes exist
void test_remove_node_empty_list(void **state){
	struct Node *head = NULL;
	uint32_t data;
	assert_int_equal(remove_node(&head, 1, &data), OUT_OF_BOUNDS);
}


//test to verify size of the linked list
//adding 3 nodes and checking if size is reported as 3
void test_size(void **state){
	struct Node *head = NULL;
	add_node(&head, 5,1);
	add_node(&head, 7,2);
	add_node(&head, 8,3);
	assert_int_equal(size(&head), 3);
}


//test to search if data exists -> positive case
//having elements 5,7,8 and searching for 7
void test_search_positive(void **state){
	struct Node *head = NULL;
	uint32_t pos;
	add_node(&head, 5,1);
	add_node(&head, 7,2);
	add_node(&head, 8,3);
	assert_int_equal(search(&head, 7, &pos), SUCCESS);
}


//test to search if data exists -> negative case
//having elements 5,7,8 and searching for 2
void test_search_negative(void **state){
	struct Node *head = NULL;
	uint32_t pos;
	add_node(&head, 5,1);
	add_node(&head, 7,2);
	add_node(&head, 8,3);
	assert_int_equal(search(&head, 2, &pos), NOT_IN_LIST);
}


//test to destroy the linked list
void test_destroy_linked_list(void **state){
	struct Node *head = NULL;
	add_node(&head, 5,1);
	add_node(&head, 7,2);
	add_node(&head, 8,3);
	assert_int_equal(destroy(&head), SUCCESS);
}



//main function
int main(int argc, char **argv)
{
	const struct CMUnitTest tests[] = {
	cmocka_unit_test(test_add_node_head),
	cmocka_unit_test(test_add_node_middle),
	cmocka_unit_test(test_add_node_tail_case1),
	cmocka_unit_test(test_add_node_tail_case2),  
	cmocka_unit_test(test_remove_node),
	cmocka_unit_test(test_remove_node_empty_list),
	cmocka_unit_test(test_size),
	cmocka_unit_test(test_search_positive),
	cmocka_unit_test(test_search_negative),
	cmocka_unit_test(test_destroy_linked_list),
};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
