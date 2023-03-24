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

    //clean_bss
    ldr x1, = __bss_start
    ldr w2, = __bss_size

3:  
    cbz     w2, 4f
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b

4:
    //set sp to somewhere? thene call c code function
    //let sp use under this addr
    ldr     x1, =_start
    mov     sp, x1

    bl main //fix issue: b main => will restart main after end of process ?

    //should NOT enter here
5:
    wfe
    b 5b

    
