/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
​ *   Users​ ​ are  permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded ​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ kernel_profiling.c
​ * ​ ​ @brief​ ​ Source file for creating a simple kernel module that computes the execution time 
 *           of the kthread_create (or kthread_run) function and makes use of 
 *           do_gettimeofday to compute the execution time.
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ October 2 ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */


#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/time.h>       // for using jiffies 
#include <linux/timer.h>
#include <linux/sched/signal.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Snehal");
MODULE_DESCRIPTION("Module to profile kernel thread");

static struct task_struct *thread1;
struct timeval now1, now2;

int fn(void *args){
  do_gettimeofday(&now2);
  printk("clock gettime start is: %ld us\n", now1.tv_usec);
  printk("clock gettime end is: %ld us\n", now2.tv_usec);
  printk("Time to create kthread is %ld us\n", (now2.tv_usec - now1.tv_usec));

  while(!kthread_should_stop()){
    schedule();
  }

  return 0;
}

//function that runs when module gets loaded
static int __init start_module(void)
{
  printk("Entering the kernel module.\n");
  do_gettimeofday(&now1);
  thread1 = kthread_run(&fn, NULL,"thread1"); 
  return 0;
}


//function that runs when module is removed
static void __exit clean_module(void)
{
  kthread_stop(thread1);
  printk("Kernel module unloaded.\n");
  return;
}


module_init(start_module);
module_exit(clean_module);
