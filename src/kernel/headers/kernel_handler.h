#ifndef KERNEL_HANDLER_HEADER
#define KERNEL_HANDLER_HEADER

// extern declarations
extern void _checkPCI();
extern void hex_from_byte(unsigned char byte, volatile char* buffer);

// buffers
volatile unsigned char main_buffer[1024];

#endif