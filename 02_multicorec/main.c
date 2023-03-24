#include <uart.h>
#include <mailbox.h>


void main(unsigned int *bss_start, unsigned int *bss_end)
{
	//clear_bss
	memset(bss_start, 0, (bss_end-bss_start));
    
    uart_init();
    
    puts("=====================\n");
    puts("Will Operating System\n");
    puts("=====================\n");
    
    
    get_board_revision();
}
