#include <io_regs.h>
#include <Types.h>

unsigned int io_read(unsigned int *addr);
void io_write(unsigned int *addr, unsigned int val);
void io_put(const size_t addr, void *data);
void delay(int cycles);
