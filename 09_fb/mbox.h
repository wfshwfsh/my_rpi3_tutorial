
#define MAILBOX_BASE        (MMIO_BASE + 0xb880)

#define MAILBOX_READ        ((volatile unsigned int*)MAILBOX_BASE)
#define MAILBOX_STATUS      ((volatile unsigned int*)(MAILBOX_BASE + 0x18))
#define MAILBOX_WRITE       ((volatile unsigned int*)(MAILBOX_BASE + 0x20))

#define MAILBOX_EMPTY       0x40000000
#define MAILBOX_FULL        0x80000000

#define MAILBOX_REQUEST     0
#define REQUEST_CODE        0x00000000
#define REQUEST_SUCCEED     0x80000000
#define REQUEST_FAILED      0x80000001
#define TAG_REQUEST_CODE    0x00000000
#define END_TAG             0x00000000

#define MBOX_RESPONSE       0x80000000

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


/* channels */
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

/* tags */
#define MBOX_TAG_GETSERIAL          0x10004
#define MBOX_TAG_SETCLKRATE         0x38002
#define MBOX_TAG_GET_BOARD_REVISION 0x00010002


#define MBOX_TAG_ALLCT_BUFFER       0x00040001
#define MBOX_TAG_PHY_DISP_INFO      0x00048003
#define MBOX_TAG_VIRT_DISP_INFO     0x00048004
#define MBOX_TAG_VIRT_DISP_OFF      0x00048009


#define MBOX_TAG_GET_DEPTH          0x00040005
#define MBOX_TAG_GET_PIXEL_ORDER    0x00040006
#define MBOX_TAG_SET_DEPTH          0x00048005
#define MBOX_TAG_SET_PIXEL_ORDER    0x00048006
#define MBOX_TAG_GET_PITCH          0x00040008

#define MBOX_CODE_TAG_REQ MAILBOX_REQUEST

#define MBOX_CODE_BUF_REQ MAILBOX_REQUEST














