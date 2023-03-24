

// Quoting from BCM2837-ARM-Peripherals.pdf (pg. 6)
// ------------------------------------------------
// Physical addresses range from 0x3F000000 to 0x3FFFFFFF for peripherals.
// The bus addresses for peripherals are set up to map onto the peripheral
// bus address range starting at 0x7E000000. Thus a peripheral advertised here
// at bus address 0x7Ennnnnn is available at physical address 0x3Fnnnnnn.

#define ALT_GPIO_IN     0b000
#define ALT_GPIO_OUT    0b001
#define ALT_FUNC0       0b100
#define ALT_FUNC1       0b101
#define ALT_FUNC2       0b110
#define ALT_FUNC3       0b111
#define ALT_FUNC4       0b011
#define ALT_FUNC5       0b010


#define MMIO_BASE       0x3F000000

#define GPFSEL0         (MMIO_BASE+0x200000)
#define GPFSEL1         (MMIO_BASE+0x200004)
#define GPFSEL2         (MMIO_BASE+0x200008)
//...

#define GPPUD           (MMIO_BASE+0x200094)
#define GPPUDCLK0       (MMIO_BASE+0x200098)

#define UART0_BASE      (MMIO_BASE+0x201000)


//uart1
#define AUXENB          (MMIO_BASE+0x215004)
#define AUX_MU_CNTL_REG (MMIO_BASE+0x215060)
#define AUX_MU_IER_REG  (MMIO_BASE+0x215044)
#define AUX_MU_LCR_REG  (MMIO_BASE+0x21504C)
#define AUX_MU_MCR_REG  (MMIO_BASE+0x215050)
#define AUX_MU_LSR_REG  (MMIO_BASE+0x215054)
#define AUX_MU_MSR_REG  (MMIO_BASE+0x215058)
#define AUX_MU_BAUD     (MMIO_BASE+0x215068)
#define AUX_MU_IIR_REG  (MMIO_BASE+0x215048)

#define AUX_MU_IO_REG   (MMIO_BASE+0x215040)


//uart0: 
//https://developer.arm.com/documentation/ddi0183/g/programmers-model/summary-of-registers?lang=en

#define UART0_BASE      (MMIO_BASE+0x201000)
/* PL011 UART registers */
#define UART0_DR        ((volatile unsigned int*)(UART0_BASE+0x00))
#define UART0_FR        ((volatile unsigned int*)(UART0_BASE+0x18))
#define UART0_IBRD      ((volatile unsigned int*)(UART0_BASE+0x24))
#define UART0_FBRD      ((volatile unsigned int*)(UART0_BASE+0x28))
#define UART0_LCRH      ((volatile unsigned int*)(UART0_BASE+0x2C))
#define UART0_CR        ((volatile unsigned int*)(UART0_BASE+0x30))
#define UART0_IMSC      ((volatile unsigned int*)(UART0_BASE+0x38))
#define UART0_ICR       ((volatile unsigned int*)(UART0_BASE+0x44))








