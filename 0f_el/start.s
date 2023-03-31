.section ".text.boot"

_start:
    //check_mpid
    mrs x1, MPIDR_EL1
    and x1, x1, #3
    cbz x1, 2f

    // if cpu_id != 0, then stop
1:
    wfe
    b 1b
    
    // only core-0 do the following
2:
    // set sp to somewhere? thene call c code function
    // let sp use under this addr
    ldr     x1, =_start
    
    
    // get_el
    mrs     x0, CurrentEL
    and     x0, x0, #12    //clear reserve bits
    
    // check el
    cmp     x0, #12
    bne     3f
    //...
    
3:  cmp     x0, #4
    beq     3f
    msr     sp_el1, x1
    // enable CNTP for EL1
    mrs     x0, cnthctl_el2
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr
    // enable AArch64 in EL1
    mov     x0, #(1 << 31)      // AArch64
    orr     x0, x0, #(1 << 1)   // SWIO hardwired on Pi3
    msr     hcr_el2, x0
    mrs     x0, hcr_el2
    // change execution level to EL1
    mov     x2, #0x3c4
    msr     spsr_el2, x2
    adr     x2, 5f
    msr     elr_el2, x2
    eret
    
    

3:  mov     sp, x1
    //clean_bss
    ldr x1, = __bss_start
    ldr w2, = __bss_size
4:
    cbz     w2, 5f
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 4b

5:
    bl main //fix issue: b main => will restart main after end of process ?

    //should NOT enter here
6:
    wfe
    b 6b

    
