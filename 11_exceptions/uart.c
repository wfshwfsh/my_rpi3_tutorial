
#include <io_regs.h>
#include "uart.h"


#define ALT_FUNC5       0b010


void uart_init(void)
{
    // set gpio alt function to uart
    io_write(GPFSEL1, (ALT_FUNC5) << 12);
    io_write(GPFSEL1, (ALT_FUNC5) << 15);
    
    
    //disable PULL-UP/DW by GPPUD, and set GPPUDCLKn 
    io_write(GPPUD, 0);
    delay(150);
    io_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    io_write(GPPUD, 0);
    io_write(GPPUDCLK0, 0);
    
    // 1. Set AUXENB register to enable mini UART,
    //    and then mini UART register can be accessed.
    io_write(AUXENB, 1);
    
    // 2. Set AUX_MU_CNTL_REG to 0,
    //    which disables transmitter and receiver during configuration.
    io_write(AUX_MU_CNTL_REG, 0);
    
    // 3. Set AUX_MU_IER_REG to 0,
    //    which disables interrupts because currently you don’t need interrupt.
    io_write(AUX_MU_IER_REG, 0);
    
    // 4. Set AUX_MU_LCR_REG to 3, which sets the data size to 8 bit.
    io_write(AUX_MU_LCR_REG, 3);
    
    // 5. Set AUX_MU_MCR_REG to 0, because we don’t need auto flow control.
    io_write(AUX_MU_MCR_REG, 0);
    
    // 6. Set AUX_MU_BAUD to 270, which sets baud rate to 115200
    io_write(AUX_MU_BAUD, 270);
    
    // 7. Set AUX_MU_IIR_REG to 6. No FIFO.
    io_write(AUX_MU_IIR_REG, 6);
    
    // 8. Set AUX_MU_CNTL_REG to 3. Enable the transmitter and receiver.
    io_write(AUX_MU_CNTL_REG, 3);
}


void uart_putchar(char c)
{
    // check AUX_MU_LSR_REG: trans empty field
    while(!(io_read(AUX_MU_LSR_REG) & (1<<5)/*trans empty bit5*/)) ;
    
    // write to AUX_MU_IO_REG
    io_write(AUX_MU_IO_REG, c);
}

unsigned char uart_getchar(void)
{
    // check AUX_MU_LSR_REG: data ready field
    while(!(io_read(AUX_MU_LSR_REG) & (1<<0)/*data ready bit0*/)) ;
    
    // read from AUX_MU_IO_REG
    return io_read(AUX_MU_IO_REG);
}

void gets(char *s)
{
    char c;
    while(1)
    {
        char c = uart_getchar();
        uart_putchar(c);
        
        if(('\n' == c) || ('\r' == c)){
            break;
        }
        
        *s = c;
        s++;
    }
    
    uart_putchar('\n');
    *s = 0;
}

void puts(char *s)
{
    int i;
    //for(i=0; i<=strlen(s); i++)
    //{
    //    uart_putchar(s[i]);
    //}
    
    while(*s){
        if(*s == '\n')
            uart_putchar('\r');
        uart_putchar(*s++);
    }
    //uart_putchar('\n');
}

void put_hex(unsigned int d)
{
    int ascii_char_a = 97;
    int ascii_char_0 = 48;
    
    unsigned int n;
    for(int c=28;c>=0;c-=4)
    {
        n = (d>>c) & 0xf;
        int off = (n>9)?(ascii_char_a-10):ascii_char_0;
        n = n + off;
        
        uart_putchar(n);
    }
}


