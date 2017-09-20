/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Snehal Sanghvi
​ *   Users​ ​ are  permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded ​ software.​ ​ Snehal Sanghvi​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ timer_module.c
​ * ​ ​ @brief​ ​ Source file for creating a simple kernel module that has a kernel timer pinging every 0.5s
​​ * ​ ​ @author​ ​ Snehal Sanghvi
​ * ​ ​ @date​ ​ September ​ 19 ​ 2017
​ * ​ ​ @version​ ​ 1.0
​ *   @compiler used to process code: GCC compiler
​ */


#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Snehal");
MODULE_DESCRIPTION("A Simple timer module");

static struct timer_list my_timer;
static int count = 0;

//callback function when timer expires
void my_timer_callback( unsigned long data )
{
	count++;  
	printk( "The count is %d\n", count );
	mod_timer( &my_timer, jiffies + msecs_to_jiffies(500) );	
}


//function that runs when module gets loaded
static int __init start_module(void)
{
  int ret;
 
  printk("Loaded kernel timer module.\n");

  setup_timer( &my_timer, my_timer_callback, 0 );
  
  ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(500) );
  
  // Non-zero return means that the module couldn't be loaded.
  if (ret) printk("Error in mod_timer\n");
    return 0;
}


//function that runs when module is removed
static void __exit clean_module(void)
{
  int ret;
 
  ret = del_timer( &my_timer );
  if (ret) 
      printk("The timer is still in use...\n");
 
  printk("Timer module unloaded.\n");
 
  return;
}


module_init(start_module);
module_exit(clean_module);
