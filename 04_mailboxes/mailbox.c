#include <mailbox.h>

mailbox_msg_t mbox;

int mbox_call(unsigned char ch)
{
    unsigned int r = (((unsigned int)((unsigned long)&mbox)&~0xF) | (ch&0xF));
    /* wait until we can write to the mailbox */
    do{asm volatile("nop");}while(*MAILBOX_STATUS & MAILBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    *MAILBOX_WRITE = r;
    /* now wait for the response */
    while(1) {
        /* is there a response? */
        do{asm volatile("nop");}while(*MAILBOX_STATUS & MAILBOX_EMPTY);
        /* is it a response to our message? */
        if(r == *MAILBOX_READ)
            /* is it a valid successful response? */
            return mbox.tag_req_resp_code==MAILBOX_RESPONSE;
    }
    return 0;
}



void get_board_revision()
{
    
    mailbox_buf_t data;
    
    mbox.buf_size = 7 * 4; // buffer size in bytes
    mbox.buf_req_resp_code = REQUEST_CODE;
    
    // tags begin
    mbox.tag_identifier = GET_BOARD_REVISION; // tag identifier
    mbox.max_value_buffer_size = 4; // maximum of request and response value buffer's length.
    mbox.tag_req_resp_code = TAG_REQUEST_CODE;
    mbox.value_buf[0] = 0; // value buffer
    // tags end
    mbox.value_buf[1] = END_TAG;
    
    
    
    mbox_call(8);
    
    //return msg.data value_buf[0];
    //printf("0x%x\n", mailbox[5]); // it should be 0xa020d3 for rpi3 b+
}





