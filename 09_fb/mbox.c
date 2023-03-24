
#include <io_regs.h>
#include <mbox.h>


//unsigned int mbox[16];
volatile unsigned int  __attribute__((aligned(16))) mbox[36];

int mbox_call(unsigned char ch)
{
    unsigned int stat;
    unsigned long a = ( (((unsigned long)&mbox)&~0xF) | (ch&0xF) );
    unsigned int r = (unsigned int)a;

#if 1
    //write 
    do {
        stat = *MAILBOX_STATUS;
    }while (stat & MAILBOX_FULL);
    *MAILBOX_WRITE = r;
    
    //read
    do {
        stat = *MAILBOX_STATUS;
    }while (stat & MAILBOX_EMPTY);
    r = *MAILBOX_READ;
#else
    do{asm volatile("nop");}while(*MAILBOX_STATUS & MAILBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    *MAILBOX_WRITE = r;
    /* now wait for the response */
    while(1) {
        /* is there a response? */
        do{asm volatile("nop");}while(*MAILBOX_STATUS & MAILBOX_EMPTY);
        /* is it a response to our message? */
        if(r == *MAILBOX_READ)
            /* is it a valid successful response? */
            return mbox[1]==MBOX_RESPONSE;
    }
#endif
    return 0;
}

void get_board_revision()
{
    mbox[0] = 7 * 4; // buffer size in bytes
    mbox[1] = REQUEST_CODE;
    
    // tags begin
    mbox[2] = MBOX_TAG_GET_BOARD_REVISION; // tag identifier
    mbox[3] = 4; // maximum of request and response value buffer's length.
    mbox[4] = TAG_REQUEST_CODE;
    mbox[5] = 0; // value buffer
    // tags end
    mbox[6] = END_TAG;

    mbox_call(MBOX_CH_PROP); // message passing procedure call, you should implement it following the 6 steps provided above.
    puts("board revision: ");
    put_hex(mbox[5]);
    puts("\n");
}

void set_sysclock()
{
    /* set up clock for consistent divisor values */
    mbox[0] = 9*4;
    mbox[1] = MAILBOX_REQUEST;
    mbox[2] = MBOX_TAG_SETCLKRATE; // set clock rate
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2;           // UART clock
    mbox[6] = 4000000;     // 4Mhz
    mbox[7] = 0;           // clear turbo
    mbox[8] = END_TAG;
    mbox_call(MBOX_CH_PROP);

}

void set_framebuffer
{
	int i=2;
	
	//1. Allocate buffer:
	mbox[i++] = MBOX_TAG_ALLCT_BUFFER;
	mbox[i++] = 
	mbox[i++] = 
	mbox[i++] = 
	
	//2. Physical (display) width/height:
	
	
	//3. Virtual (buffer) width/height:
	
	
	//4. Virtual (buffer) offset: 
	
	
	//5. Depth: 
	
	
	//6. Pixel order: 
	
	
	//7. Get pitch:
	
	
	
	mbox[0] = total_len?;
	mbox[1] = MAILBOX_REQUEST;
}
