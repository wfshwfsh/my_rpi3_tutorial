.section ".text"

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

    //clean_bss
//    ldr x1, = __bss_start
//    ldr x2, = __bss_end
//    mov x3, #0

//clean:
//    str x3, [x1]
//    add x1, x1, #8
//    cmp x1, x2
//    bne clean

    
    //set sp to somewhere? thene call c code function
    //let sp use under this addr
    ldr     x1, =_start
    mov     sp, x1

    ldr w0, = __bss_start
    ldr w1, = __bss_end
    bl main //fix issue: b main => will restart main after end of process ?

    //should NOT enter here
4:
    wfe
    b 4b

    
