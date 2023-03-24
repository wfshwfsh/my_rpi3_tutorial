
#include <io_regs.h>
#include "uart.h"





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


void uart1_putchar(char c)
{
    // check AUX_MU_LSR_REG: trans empty field
    while(!(io_read(AUX_MU_LSR_REG) & (1<<5)/*trans empty bit5*/)) ;
    
    // write to AUX_MU_IO_REG
    io_write(AUX_MU_IO_REG, c);
}

unsigned char uart1_getchar(void)
{
    // check AUX_MU_LSR_REG: data ready field
    while(!(io_read(AUX_MU_LSR_REG) & (1<<0)/*data ready bit0*/)) ;
    
    // read from AUX_MU_IO_REG
    return io_read(AUX_MU_IO_REG);
}



void uart0_init(void)
{
    *UART0_CR = 0;
    
    // set gpio alt function to uart
    io_write(GPFSEL1, (ALT_FUNC0) << 12);
    io_write(GPFSEL1, (ALT_FUNC0) << 15);
    
    //disable PULL-UP/DW by GPPUD, and set GPPUDCLKn 
    io_write(GPPUD, 0);
    delay(150);
    io_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    io_write(GPPUD, 0);
    io_write(GPPUDCLK0, 0);
    
    
    //3. dis intr (mask all uart0 intr)
    //*UART0_IMSC = 0x7ff;
    *UART0_ICR = 0x7ff;
    
    //UARTLCR_H[6:5] 11=>8bit, [4]: 1=>enable FIFO, [3] stop bit 0: stop bit=1
    //   [2]: parity-odd/even, [1]: 0=>dis parity
    *UART0_LCRH = (0b11<<5)|(1<<4);
    
    
    //6. set baurd rate
    *UART0_FBRD = 0xB;
    *UART0_IBRD = 2;
    
    // enable uart tx/rx
    //UARTCR [9]:RXE, [8]:TXE, [0]:Enable Uart
    *UART0_CR = (1<<9) | (1<<8) | (1<<0);
}

void uart0_putchar(char c)
{
    // check AUX_MU_LSR_REG: trans empty field
    while(!(io_read(UART0_FR) & (1<<7)/*trans empty bit5*/)) ;
    
    // write to UARTDR
    *UART0_DR = c;
}

unsigned char uart0_getchar(void)
{
    // check AUX_MU_LSR_REG: data ready field
    while(!(io_read(UART0_FR) & (1<<6)/*data ready bit0*/)) ;
    
    // read from UARTDR
    return io_read(UART0_DR);
}


#define uart_putchar uart0_putchar
#define uart_getchar uart0_getchar

void gets(char *s)
{
    char c;
    while(1)
    {
        char c = uart0_getchar();
        uart0_putchar(c);
        
        if(('\n' == c) || ('\r' == c)){
            break;
        }
        
        *s = c;
        s++;
    }
    
    uart0_putchar('\n');
    *s = 0;
}

void puts(char *s)
{
    //int i;
    //for(i=0; i<=strlen(s); i++)
    //{
    //    uart0_putchar(s[i]);
    //}
    
    while(*s){
        if(*s == '\n')
            uart0_putchar('\r');
        uart0_putchar(*s++);
    }
    //uart0_putchar('\n');
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
        
        uart0_putchar(n);
    }
}


