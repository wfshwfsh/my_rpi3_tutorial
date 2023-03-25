
#include <io_regs.h>
#include <mbox.h>
#include <uart.h>
#include <homer.h>

#define WEIGHT      1024
#define HEIGHT      768


extern volatile unsigned int  __attribute__((aligned(16))) mbox[36];

unsigned char *fb;

unsigned int width, height, pitch, isrgb;

void set_framebuffer()
{
	int i=1;
	mbox[i++] = MAILBOX_REQUEST;
    
	//1. Allocate buffer: 2-6
	mbox[i++] = MBOX_TAG_ALLCT_BUFFER;
	mbox[i++] = 8;//buffer_sz
	mbox[i++] = 4;//data_sz
	mbox[i++] = 4096;//alignment
	mbox[i++] = 0; //???
    
	//2. Physical (display) width/height: 7-11
	mbox[i++] = MBOX_TAG_PHY_DISP_INFO;
	mbox[i++] = 8;//buffer_sz
	mbox[i++] = 8;//data_sz
	mbox[i++] = WEIGHT;//weight
    mbox[i++] = HEIGHT;//height
    
	
	//3. Virtual (buffer) width/height: 12-16
	mbox[i++] = MBOX_TAG_VIRT_DISP_INFO;
	mbox[i++] = 8;//buffer_sz
	mbox[i++] = 8;//data_sz
	mbox[i++] = WEIGHT;//weight
    mbox[i++] = HEIGHT;//height
    
	//4. Virtual (buffer) offset: 17-21
	mbox[i++] = MBOX_TAG_VIRT_DISP_OFF;
	mbox[i++] = 8;//buffer_sz
	mbox[i++] = 8;//data_sz
	mbox[i++] = 0;//X in pixels
    mbox[i++] = 0;//Y in pixels
	
	//5. Set Depth: 22-25
	mbox[i++] = MBOX_TAG_SET_DEPTH;
	mbox[i++] = 4;//buffer_sz
	mbox[i++] = 4;//data_sz
	mbox[i++] = 32;//depth: bits per pixel
	
	//6. Set Pixel order: 26-29
	mbox[i++] = MBOX_TAG_SET_PIXEL_ORDER;
	mbox[i++] = 4;//buffer_sz
    mbox[i++] = 4;//data_sz
	mbox[i++] = 1;//1:RGB, 0:BGR
	
	//7. Get pitch: 30-33
	mbox[i++] = MBOX_TAG_GET_PITCH;
	mbox[i++] = 4;//buffer_sz
	mbox[i++] = 0;//data_sz
	mbox[i++] = 0;//pitch: bytes per line
    
	mbox[i++] = END_TAG;
	mbox[0] = 35*4;//total len = mbox_num * 4(bytes)
	
    mbox_call(MBOX_CH_PROP);
    
    if (mbox[25] == 32 && mbox[5] != 0) {
        mbox[5] &= 0x3FFFFFFF;   // convert GPU address to ARM address
        width = mbox[10];        // get actual physical width
        height = mbox[11];       // get actual physical height
        pitch = mbox[33];        // get number of bytes per line
        isrgb = mbox[29];        // get the actual channel order
        
        fb = (void *)((unsigned long)mbox[5]);
        
        puts("width = "); put_hex(width); puts("\n");
        puts("height = "); put_hex(height); puts("\n");
        puts("pitch = "); put_hex(pitch); puts("\n");
        puts("isrgb = "); put_hex(isrgb); puts("\n");
        puts("fb = "); put_hex(fb); puts("\n");
    }
    else {
        puts("Unable to set screen resolution to 720x480x32\n");
    }
    
}

void fb_init()
{
    for(int delay=10000000;delay>0;delay--) ;
        
    set_framebuffer();
    
}

void fb_splash() {
    int x, y;
    unsigned char *ptr = fb;
    
#if 0
    unsigned int white = 255 << 16 | 255 << 8 | 255;  // A B G R
    unsigned int black = 0;
    unsigned int current, start = black, spacing = 40;
    
    for (y = 0; y < height; y++) {
        if (y % spacing == 0 && y != 0) {
            start = (start == white) ? black : white;
        }
        current = start;
        for (x = 0; x < width; x++) {
            if (x % spacing == 0 && x != 0) {
                current = (current == white) ? black : white;
            }
            *((unsigned int *)ptr) = current;
            ptr += 4;
        }
    }
#else
    
    char *data=homer_data, pixel[4];

    ptr += (height-homer_height)/2*pitch + (width-homer_width)*2;
    for(y=0;y<homer_height;y++) {
        for(x=0;x<homer_width;x++) {
            HEADER_PIXEL(data, pixel);
            // the image is in RGB. So if we have an RGB framebuffer, we can copy the pixels
            // directly, but for BGR we must swap R (pixel[0]) and B (pixel[2]) channels.
            *((unsigned int*)ptr)=isrgb ? *((unsigned int *)&pixel) : (unsigned int)(pixel[0]<<16 | pixel[1]<<8 | pixel[2]);
            ptr+=4;
        }
        ptr+=pitch-homer_width*4;
    }
#endif
}




