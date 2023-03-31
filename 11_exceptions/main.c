#include <uart.h>

void get_currentEl()
{
    unsigned long x0;
    asm volatile ("mrs %0, CurrentEL" : "=r" (x0));
    
    puts("Current EL is: ");
    put_hex((x0>>2)&3);
    puts("\n");
}

void main()
{
	uart_init();
    
    puts("=====================\n");
    puts("Will Operating System\n");
    puts("=====================\n");
    
    get_currentEl();
}

