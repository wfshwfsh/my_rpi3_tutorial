#include <io_regs.h>
#include <Types.h>


#define MAILBOX_BASE        (MMIO_BASE + 0xb880)

#define MAILBOX_READ        ((volatile unsigned int*)(MAILBOX_BASE))
#define MAILBOX_STATUS      ((volatile unsigned int*)(MAILBOX_BASE + 0x18))
#define MAILBOX_WRITE       ((volatile unsigned int*)(MAILBOX_BASE + 0x20))

#define MAILBOX_EMPTY       0x40000000
#define MAILBOX_FULL        0x80000000
#define MAILBOX_RESPONSE    0x80000000

#define GET_BOARD_REVISION  0x00010002
#define REQUEST_CODE        0x00000000
#define REQUEST_SUCCEED     0x80000000
#define REQUEST_FAILED      0x80000001
#define TAG_REQUEST_CODE    0x00000000
#define END_TAG             0x00000000


//      0       4       8      12      16      20      24      28      32
//      +-------+-------------------------------------------------------+
// 0x00 |rd chn |                     read data                         |
//      +-------+-------------------------------------------------------+
// 0x04 |                             Unused                            |
// ...  \\                                                             \\
// 0x14 |                             Unused                            |
//      +-----------------------------------------------------------+-+-+
// 0x18 |      status reserved                                      |E|F|
//      +-----------------------------------------------------------+-+-+
// 0x1C |                             Unused                            |
//      +-----------------------------------------------------------+-+-+
// 0x20 |wt chn |                    write data                         |
//      +-----------------------------------------------------------+-+-+


#define VALUE_BUF_SIZE 3

typedef struct {
    uint8_t channel: 4;
    uint32_t data: 28;
} mailbox_msg_t;

typedef struct {
    uint32_t reserved: 30;
    uint8_t empty: 1;
    uint8_t full:1;
} mailbox_status_t;

typedef struct {
    uint32_t buf_size;                   // buffer size (in bytes)
    uint32_t buf_req_resp_code;          // request/response code
    uint32_t tag_identifier;             // tag identifier
    uint32_t max_value_buffer_size;      // maximum of request/response value buffer's size
    uint32_t tag_req_resp_code;                
    uint32_t value_buf[VALUE_BUF_SIZE];  // value buffer
}mailbox_buf_t;



