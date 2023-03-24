

// Quoting from BCM2837-ARM-Peripherals.pdf (pg. 6)
// ------------------------------------------------
// Physical addresses range from 0x3F000000 to 0x3FFFFFFF for peripherals.
// The bus addresses for peripherals are set up to map onto the peripheral
// bus address range starting at 0x7E000000. Thus a peripheral advertised here
// at bus address 0x7Ennnnnn is available at physical address 0x3Fnnnnnn.


#define MMIO_BASE       0x3F000000

#define GPFSEL0         (MMIO_BASE+0x200000)
#define GPFSEL1         (MMIO_BASE+0x200004)
#define GPFSEL2         (MMIO_BASE+0x200008)
//...

#define GPPUD           (MMIO_BASE+0x200094)
#define GPPUDCLK0       (MMIO_BASE+0x200098)


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







