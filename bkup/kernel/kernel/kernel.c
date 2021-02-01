#include <stdio.h>
#include <kernel/tty.h>
/* #include <stdlib.h> */


void kernel_main(void) {
	terminal_initialize();
	printf("Welcome to ZephyrOS\n");
}
