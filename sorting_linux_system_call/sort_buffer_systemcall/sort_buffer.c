/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
​ *   Users​ ​ are  permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded
​ * ​ ​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ sort_buffer.c
​ * ​ ​ @brief​ ​ Source file having implementation of a system call that accepts a buffer of int32_t items from the user side, sorts in kernel space and returns the sorted buffer back to the user side.
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 19 ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(sort_buffer, __s32*, user_buffer, __s32, len, __s32*, result){

	__s32 *kern_buffer;

	__s32 n1, n2;
	__s32 i, j, temp;
	printk(KERN_ALERT "Entering system call.\n");
	
	//check if the user buffer has some value or is it not assigned, if not return a bad address
	if(user_buffer == NULL){
		printk(KERN_ALERT "Error(%d), user buffer must be initialized.\n", EFAULT);
		return EFAULT;
	}

	//should have an input length of atleast 256 data items
	if(len < 256){
		printk(KERN_ALERT "Error(%d), array should have atleast 256 data items.\n", EINVAL);
		return EINVAL;
	}

	kern_buffer = (__s32 *)kmalloc(len*sizeof(__s32), GFP_KERNEL);
	n1 = copy_from_user(kern_buffer, user_buffer, len * sizeof (__s32));

	printk(KERN_ALERT "Size of kernel buffer is %d elements\n", len);
	
	//begin sorting
	printk(KERN_ALERT "Begin sorting.\n");
	for(i=0; i<len; i++){
		for(j=i+1; j<len; j++){
			if(*(kern_buffer + j) < *(kern_buffer + i)){
				temp = *(kern_buffer + j);
				*(kern_buffer + j) = *(kern_buffer + i);
				*(kern_buffer + i) = temp;
			}
		}
	}	
	printk(KERN_ALERT "Sorting completed.\n");
	
	//copy to user space
	n2 = copy_to_user(result, kern_buffer, len * sizeof(__s32));
	if(!n2)
		printk(KERN_ALERT "All the data copied back to user space.\n");
	else{
		//checking to see if all the bytes from kernel buffer are copied to the result buffer which is to be displayed
		printk(KERN_ALERT "Error(%d). Not able to copy all the data to result buffer.\n", EINVAL);
		return EINVAL;
	}

	printk(KERN_ALERT "Exiting system call.\n");
	
	kfree(kern_buffer);
	return 0;
}
