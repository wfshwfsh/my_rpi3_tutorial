
void main()
{
    set_sysclock();
	uart0_init();
    
    puts("=====================\n");
    puts("Will Operating System\n");
    puts("=====================\n");
    
    get_board_revision();
}

