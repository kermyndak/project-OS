#include "headers/kernel_handler.h"

void kmain(void){
	// clear screen
	print_text()

	clear_screen();

	return;
}

/* Values for colors
	0 - Black, 1 - Blue, 2 - Green, 3 - Cyan, 4 - Red, 5 - Magenta, 
	6 - Brown, 7 - Light Grey, 8 - Dark Grey, 9 - Light Blue, 
	10/a - Light Green, 11/b - Light Cyan, 12/c - Light Red, 
	13/d - Light Magenta, 14/e - Light Brown, 15/f – White.

	Uses 2 bytes, first for value, second for color*/
void print_text(const char * buffer){
	for (int i = 0, j = 0; str[j] != '\0'; j++, i += 2){
		video_memory[i] = str[j];
		video_memory[i+1] = 0x02;
	}
	return;
}

void clear_screen(){
	for (int i = 0, j = 0; j < 80 * 25 * 2; j += 2){
		video_memory[j] = ' ';
		video_memory[j+1] = 0x02;
	}
	return;
}