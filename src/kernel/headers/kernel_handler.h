#ifndef KERNEL_HANDLER_HEADER
#define KERNEL_HANDLER_HEADER

// extern declarations
extern void _checkPCI();
extern void hex_from_byte(char byte, char* buffer);

// declarations

/* Values for colors
	0 - Black, 1 - Blue, 2 - Green, 3 - Cyan, 4 - Red, 5 - Magenta, 
	6 - Brown, 7 - Light Grey, 8 - Dark Grey, 9 - Light Blue, 
	10/a - Light Green, 11/b - Light Cyan, 12/c - Light Red, 
	13/d - Light Magenta, 14/e - Light Brown, 15/f – White.

	Uses 2 bytes, first for value, second for color*/
void print_text_videomemory(const char * buffer);
void print_char_videomemory(char byte);
void clear_screen();
//void hex_from_byte(char byte, char * buffer);

// hardware addresses
char *video_memory = (char*)0xb8000;

// buffers
char main_buffer[1024];

#endif