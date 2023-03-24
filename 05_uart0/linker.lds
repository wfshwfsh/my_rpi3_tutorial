SECTIONS
{
    . = 0x80000;
    . = ALIGN(4);
    .text : { *(.text.boot) }

    . = ALIGN(4);
    .rodata : { *(.rodata) }

    . = ALIGN(4);
    .data : { *(.data) }

    . = ALIGN(4);
    __bss_start = .;
    .bss : { *(.bss) }
    __bss_end = .;

}
__bss_size = (__bss_end - __bss_start)>>3;

