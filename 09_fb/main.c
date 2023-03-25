
void main()
{
    set_sysclock();
	//uart0_init();
    fb_init();
    
    puts("=====================\n");
    puts("Will Operating System\n");
    puts("=====================\n");
    
    
    fb_splash();
    
    get_board_revision();
}

