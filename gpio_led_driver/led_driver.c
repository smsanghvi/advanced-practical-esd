#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/string.h>
 
static unsigned int gpioLED = 53;
MODULE_AUTHOR("Snehal");
MODULE_LICENSE("GPL");
 
static int init_result;
static int freq = 1;
static struct timer_list my_timer;
static bool ledStatus = true;
static int count = 0;
static int duty = 50;
static int flag;
static int flag1;
static int flag2;
static int flag3;
static int flag4;


//callback function when timer expires
void my_timer_callback( unsigned long data )
{
	if(!flag){
	}
	else{
		count++;

		if(count%2){
			ledStatus = !ledStatus;          // Invert the LED state
  			gpio_set_value(gpioLED, ledStatus); 
			mod_timer( &my_timer, jiffies + usecs_to_jiffies(500000*(100-duty)/(100*freq)) );			
		}
		else{
			ledStatus = !ledStatus;          // Invert the LED state
  			gpio_set_value(gpioLED, ledStatus); 
			mod_timer( &my_timer, jiffies + usecs_to_jiffies(500000*duty/(100*freq)) );	
		}
	}
}


//atoi function
static int my_atoi(char *str){
    if (*str == '\0')          //If the string is empty, return integer is '0'
       return 0;

    int number = 0;  // Initialize the output number
    int neg = 1;  // For negative values, setting it as positive by default
    //uint8_t i = 0;  // Initialize index of first digit

    // If number is negative, then update sign
    if (*str == '-'){
        neg = -1;
        str++;
    }

    // Calculating and adding each digit of the string.
    while(*str != '\0')
    {
        if (*str >= '0' && *str <= '9')
            number = number*10 + *str++ - '0';
        else {
	        printk(KERN_INFO "Invalid numerical string\n");           //Generate error message if string does not have a number
        	return 0;
        }
    }

    // Return result with sign
    return neg*number;
}


static ssize_t gpio_read( struct file* F, char *buf, size_t count, loff_t *f_pos ){
	char buffer[100];	
	memset(buffer, 0, sizeof(buffer));
	if(flag1){
		sprintf( buffer, "%d %d %d" , ledStatus, freq, duty);
		flag1 = 0;
	}
	if(flag2){
		sprintf( buffer, "%d" , ledStatus);
		flag2 = 0;
	} 
	if(flag3){
		sprintf( buffer, "%d" , freq);
		flag3 = 0;
	}
	if(flag4){
		sprintf( buffer, "%d" , duty);
		flag4 = 0;
	}	

	count = sizeof( buffer );
 
	if( copy_to_user( buf, buffer, count ) ){
		return -EFAULT;
	}

	return 0;
}


static ssize_t gpio_write( struct file* F, const char *buf, size_t count, loff_t *f_pos ){ 
	printk(KERN_INFO "Executing WRITE.\n");
	int n1, ret;
	char kern_buffer[100];
	char *kern_ptr;
	char *dup_str;
	char *options;
	char *length;
	char *data;

	memset(kern_buffer, 0, sizeof(kern_buffer));

	n1 = copy_from_user(kern_buffer, buf, count);
	if(n1 == 0)
		printk(KERN_INFO "Success in copying\n");
	else
		printk(KERN_INFO "Failed in copying\n");		
	int number1;
	printk(KERN_INFO "Message is %s", kern_buffer);

	number1 = kern_buffer[0];	
	kern_ptr = kern_buffer;

	printk(KERN_INFO "number1 is %d", number1);

	flag = 0;
	flag1 = 0;

	//for LED control case
	if(number1 == 48){		
		flag = 0;
		printk(KERN_INFO " In LED control mode\n");
		options = strsep(&kern_ptr, " ");
		printk(KERN_INFO "options is %s", options);
		length = strsep(&kern_ptr, " ");
		printk(KERN_INFO "length is %d", my_atoi(length));
		data = strsep(&kern_ptr, " \n");
		printk(KERN_INFO "data is %s", data);	
		int data_led;
		data_led = data[0] - 48;
		printk(KERN_INFO "data led is %d", data_led);
		ledStatus = data_led;
		if(my_atoi(length)==2){
			gpio_set_value(gpioLED, data_led);
		}	
		else{
			gpio_set_value(gpioLED, 0);
			printk(KERN_INFO "Invalid input sent by user.");
		}
	}
	//for changing frequency
	if(number1 == 49){		
		printk(KERN_INFO " In frequency setup mode\n");
		options = strsep(&kern_ptr, " ");
		printk(KERN_INFO "options is %s", options);
		length = strsep(&kern_ptr, " ");
		printk(KERN_INFO "length is %d", my_atoi(length));
		data = strsep(&kern_ptr, " \n");
		printk(KERN_INFO "data is %s", data);
		freq = my_atoi(data);
		printk(KERN_INFO "atoi of data is %d", freq);
		//printk(KERN_INFO "Time")
		flag = 1;
		ret = mod_timer( &my_timer, jiffies + usecs_to_jiffies(500000*duty/(100*freq)) );	
	}	
	//for changing duty cycle
	if(number1 == 50){		
		printk(KERN_INFO " In duty cycle mode\n");
		options = strsep(&kern_ptr, " ");
		printk(KERN_INFO "options is %s", options);
		length = strsep(&kern_ptr, " ");
		printk(KERN_INFO "length is %d", my_atoi(length));
		data = strsep(&kern_ptr, " \n");
		printk(KERN_INFO "data is %s", data);
		duty = my_atoi(data);
		flag = 0;
		printk(KERN_INFO "atoi of duty is %d", duty);
	}	
	//reading all state variables
	else if(number1 == 51){		
		printk(KERN_INFO "Reading all state variables.\n");
		flag1 = 1;
	}	
	//reading LED status
	else if(number1 == 52){		
		printk(KERN_INFO "Reading LED status.\n");
		flag2 = 1;
	}	
	//reading frequency value
	else if(number1 == 53){		
		printk(KERN_INFO "Reading frequency value.\n");
		flag3 = 1;
	}	
	//for changing duty cycle
	else if(number1 == 54){		
		printk(KERN_INFO "Reading duty cycle value.\n");
		flag4 = 1;
	}	
			
	return count;
}
 

static int gpio_open( struct inode *inode, struct file *file ){
	printk("Did gpio open.\n");
	return 0;
}
 

//did gpio close
static int gpio_close( struct inode *inode, struct file *file ){
	printk("Did gpio close.\n");
	return 0;
}

 
static struct file_operations FileOps =
{
.open         = gpio_open,
.read         = gpio_read,
.write         = gpio_write,
.release     = gpio_close,
};


//initialization function 
static int init_gpio(void){
	init_result = register_chrdev( 0, "led_driver", &FileOps );
	if( 0 > init_result ){
		printk(KERN_ALERT "Device Registration failed\n");
		return -1;
	}
	else{
		printk(KERN_ALERT "Major number is: %d Snehal\n",init_result);
		flag = 0;
		setup_timer( &my_timer, my_timer_callback, 0 );
		//printk(KERN_INFO "Time")
		int ret = mod_timer( &my_timer, jiffies + usecs_to_jiffies(500000) );
		return 0;
	}
}
 

//cleanup function on calling rmmod 
void cleanup_gpio(void)
{
	//OFF the led
	gpio_set_value(gpioLED, 0); 
	unregister_chrdev( init_result, "led_driver" );
	int ret = del_timer( &my_timer );
	printk(KERN_ALERT "Device unregistered Snehal %d\n", init_result);
}

 
module_init(init_gpio);
module_exit(cleanup_gpio);
