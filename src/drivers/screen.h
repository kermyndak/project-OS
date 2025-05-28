#ifndef SCREEN_H
#define SCREEN_H

typedef enum { 
	BLACK, BLUE, GREEN,
	CYAN, RED, MAGENTA,
	BROWN, LIGHT_GREY,
	DARK_GREY, LIGHT_BLUE,
	LIGHT_GREEN, LIGHT_CYAN,
	LIGHT_RED, LIGHT_MAGENTA,
	LIGHT_BROWN, WHITE
} colors;

typedef enum { TWO_SPACES=2, FOUR_SPACES=4 } tab_size;

#ifndef DEFAULT_COLOR
#define DEFAULT_COLOR GREEN
#endif

#ifndef DEFAULT_TAB_SIZE
#define DEFAULT_TAB_SIZE FOUR_SPACES
#endif

//declarations

/* 
	Uses 2 bytes, first for value, second for color
*/
void print_text_videomemory(volatile const unsigned char* buffer, bool new_string);
void print_char_videomemory(unsigned char byte);
void print_text_videomemory_with_color(volatile const unsigned char* buffer, bool new_string, colors color);
void print_char_videomemory_with_color(unsigned char byte, colors color);
void print_error_text_videomemory(volatile const unsigned char* buffer, bool new_string);
// void print_uint8_videomemory(unsigned char value);
// void print_int8_videomemory(char value);
// void print_uint16_videomemory(unsigned short value);
// void print_int16_videomemory(short value);
// void print_uint32_videomemory(unsigned long value);
// void print_int32_videomemory(long value);
// void print_uhex8_vidememory(unsigned char value);
// void print_hex8_videomemory(char value);
// void print_uhex16_videomemory(unsigned short value);
// void print_hex16_videomemory(short value);
// void print_uhex32_videomemory(unsigned long value);
// void print_hex32_videomemory(long value);
void print_new_line();
void clear_screen();

// Video memory address
volatile char* video_memory = (volatile char*)0xb8000;

// Buffer for internal tasks
unsigned char video_memory_buffer[256];

// For control video buffer
static char counter_lines = 1;
static int end_of_text = 0;

#endif