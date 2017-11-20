obj-m+=led_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) gpio_user.c -o gpio_user

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm gpio_user
	
