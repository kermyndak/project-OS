#include "headers/kernel_handler.h"

void kmain(void){
	// clear screen
    clear_screen();

	print_text_videomemory("some text");
    hex_from_byte(0, main_buffer);
    print_text_videomemory(main_buffer);
    //_checkPCI();
	return;
}

void print_text_videomemory(const char * buffer){
	for (int i = 0, j = 0; buffer[j] != '\0'; j++, i += 2){
		video_memory[i] = buffer[j];
		video_memory[i+1] = 0x02;
	}
	return;
}

void print_char_videomemory(char byte){
    video_memory[0] = byte;
    video_memory[1] = 0x02;
    return;
}

void clear_screen(){
	for (int i = 0, j = 0; j < 80 * 25 * 2; j += 2){
		video_memory[j] = ' ';
		video_memory[j+1] = 0x02;
	}
	return;
}

// void hex_from_byte(char byte, char * buffer){

// }

