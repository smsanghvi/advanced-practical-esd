/****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
 *   This file makes use of CMocka licensed by Apache License 2.0
​ * ​ ​ Redistribution,​ ​ modification​ ​ or​ ​ use​ ​ of​ ​ this​ ​ software​ ​ in​ ​ source​ ​ or​ ​ binary ​ forms​ ​ is​ ​ permitted​ ​ as​ ​ long​ ​ as​ ​ the​ ​ files​ ​ maintain​ ​ this​ ​ copyright.​ ​ Users​ ​ are​ ​ permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for any​ ​ misuse​ ​ of​ ​ this​ ​ material.
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ test_circular_buffer.c
​ * ​ ​ @brief​ ​ A unit test file using CMocka to test all implemented functions in circular buffer
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
#include "Circular_buffer.h"


//test to check memory allocation and initialization
void test_memory_allocation(void **state){
	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	assert_int_equal(allocate(&bufferptr, MAX_SIZE), Buffer_Initialized) ;
}


//test to check empty buffer condition
void test_empty_buffer(void **state){
	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	assert_int_equal(Is_buffer_empty(&bufferptr), Buffer_Empty);
}


//test to check full buffer condition
void test_full_buffer(void **state){
	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	assert_int_equal(Is_buffer_full(&bufferptr), Buffer_Full);
}


//test to add item to circular buffer
void test_add_item(void **state){
	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	assert_int_equal(add_item(&bufferptr, 3), Buffer_Ok);
}


//test to add items beyond max size of circular buffer, checking corner add case
void test_add_buffer_full(void **state){
	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	assert_int_equal(add_item(&bufferptr, 3), Buffer_Full_Error);
}


//test to remove an item from circular buffer
void test_remove_item(void **state){
	struct CircBuf_t *bufferptr = NULL;
	uint32_t data;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 5);
	assert_int_equal(remove_item(&bufferptr, &data), Buffer_Ok);
}


//test to remove an item from empty circular buffer
void test_remove_item_buffer_empty(void **state){
	struct CircBuf_t *bufferptr = NULL;
	uint32_t data;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	assert_int_equal(remove_item(&bufferptr, &data), Buffer_Empty_Error);
}


//test to check back to back adds and removes and check the final size
void test_back_to_back_adds_removes(void **state){
	struct CircBuf_t *bufferptr = NULL;
	uint32_t data;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 3);
	remove_item(&bufferptr, &data);
	add_item(&bufferptr, 3);
	remove_item(&bufferptr, &data);
	assert_int_equal(size(&bufferptr), 1);
}


//test to confirm size returned by buffer, adding 3 items, should show size as 3
void test_check_size(void **state){
	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 5);
	add_item(&bufferptr, 7);
	assert_int_equal(size(&bufferptr), 3);
}


//test to destroy circular buffer structure
void test_destroy_buffer(void **state){
	struct CircBuf_t *bufferptr = NULL;
	bufferptr = (struct CircBuf_t *)malloc(sizeof(struct CircBuf_t));
	allocate(&bufferptr, MAX_SIZE);
	add_item(&bufferptr, 3);
	add_item(&bufferptr, 5);
	add_item(&bufferptr, 7);
	assert_int_equal(destroy_buffer(&bufferptr), Buffer_Deallocated);
}


//main function
int main(int argc, char **argv)
{
	const struct CMUnitTest tests[] = {
	cmocka_unit_test(test_memory_allocation),
	cmocka_unit_test(test_empty_buffer),
	cmocka_unit_test(test_full_buffer),
	cmocka_unit_test(test_add_item),
	cmocka_unit_test(test_add_buffer_full),
	cmocka_unit_test(test_remove_item),
	cmocka_unit_test(test_remove_item_buffer_empty),
	cmocka_unit_test(test_back_to_back_adds_removes),
	cmocka_unit_test(test_check_size),
	cmocka_unit_test(test_destroy_buffer),
};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
