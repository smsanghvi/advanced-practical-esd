#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h> 

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
	        printf("Invalid numerical string\n");           //Generate error message if string does not have a number
        return 0;
        }
    }

    // Return result with sign
    return neg*number;
}


int main(void){
	int fd;
	char gpio_buffer[10];
	char choice[10];
	char data[50];
	char message[100];
 
	fd = open( "/dev/led_driver", O_RDWR );
 
	printf( "Value of fd is: %d", fd );
 	
	if( fd < 0 ){
		printf("Cannot open device \t");
		printf(" fd = %d \n",fd);
		return 0;
	}
 
	printf("\nPlease enter choice: \n");
	printf("------------------------------\n");
	printf("0 for LED control\n");
	printf("1 for setting frequency\n");
	printf("2 for setting duty cycle\n");
	printf("3 to exit\n");
	scanf( "%s", choice );
	while(my_atoi(choice) != 3){
		printf("Your choice is: %s \n", choice );

		//LED on/off
		if(my_atoi(choice)==0){
			memset(data, 0, sizeof(data));
			printf("\nEnter 0 to clear LED and 1 to set LED\n");
			scanf("%s", data);
			if(strlen(data)>2){
				printf("Invalid option.\n");
				continue;
			}
			sprintf(message, "%s %d %s", choice, strlen(data)+1, data);
			write(fd, message, strlen(message));
		}
		//setting frequency
		if(my_atoi(choice)==1){
			memset(data, 0, sizeof(data));
			printf("\nEnter the frequency (in Hz)\n");
			scanf("%s", data);
			if(strlen(data)>7){
				printf("Enter a frequency less than 500kHz\n");
				continue;
			}
			sprintf(message, "%s %d %s", choice, strlen(data)+1, data);
			write(fd, message, strlen(message));
		}	
		//setting duty cycle
		if(my_atoi(choice)==2){
			memset(data, 0, sizeof(data));
			printf("\nEnter the duty cycle (from 0-99%)\n");
			scanf("%s", data);
			if(strlen(data)>3){
				printf("Enter a duty cycle less than 100%\n");
				continue;
			}
			sprintf(message, "%s %d %s", choice, strlen(data)+1, data);
			write(fd, message, strlen(message));
		}		
		printf("\nPlease enter choice: \t");
		scanf( "%s", choice );	
	}

	read( fd, gpio_buffer, 2);
	printf("GPIO value is: %s \n", gpio_buffer );
 
	if( 0 != close(fd) ){
		printf("Could not close device\n");
	}
 
	return 0;
}
