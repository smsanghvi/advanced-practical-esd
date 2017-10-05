/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
​ *   Users​ ​ are  permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded ​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ kernel_ll.c
​ * ​ ​ @brief​ ​ Source file for creating a simple kernel module that lists all processes
 *            from current process, backtracing to the inittask. Prints out all PIDs,
 *             process states and number of children for each process.
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ October ​ 2 ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */


#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/sched/signal.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Snehal");
MODULE_DESCRIPTION("Module to backtrace and list all processes");


//function that runs when module gets loaded
static int __init start_module(void)
{
   struct task_struct *task;
   struct list_head *list;
   int no_of_children = 0;
  
  printk("Loading kernel module.\n");

   for(task=current;task!=&init_task;task=task->parent){
      //to find total number of children
      list_for_each(list, &(task->children)){
        ++no_of_children;
      }
      printk("-----------------------------------------------");
      printk("Process name: %s\nPID: %d\nProcess state:%ld\nNo. of children:%d\n",\
        task->comm , task->pid, task->state, no_of_children);
      no_of_children=0;
   }

  return 0;
}


//function that runs when module is removed
static void __exit clean_module(void)
{
  printk("Kernel module unloaded.\n");
  return;
}


module_init(start_module);
module_exit(clean_module);
