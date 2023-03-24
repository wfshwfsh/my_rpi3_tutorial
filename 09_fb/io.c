unsigned int io_read(unsigned int *addr)
{
    return *addr;
}

void io_write(unsigned int *addr, unsigned int val)
{
    *addr = val;
}

void delay(int cycles)
{
    while (cycles--) {
        asm volatile("nop");
    }
}