#include "headers/kernel_handler.h"

void kmain(void){
	// clear screen
    clear_screen();

	print_text_videomemory("some text\nsome text\nsome text", true);
	print_text_videomemory("some text\nsome text\nsome text", true);
    //hex_from_byte(228, main_buffer);
	strcpy(main_buffer, "qwerty");
    print_text_videomemory(main_buffer, true);
	c_variant_hex_from_byte(228, main_buffer);
	print_text_videomemory(main_buffer, true);
    //_checkPCI();
	return;
}

void print_text_videomemory(volatile const unsigned char * buffer, bool new_string){
    static char counter_lines = 1;
	static int end_of_text = 0;
	for (int i = end_of_text, j = 0; buffer[j] != '\0'; j++, end_of_text = i += 2){
        if (buffer[j] == '\n'){
            i = 160 * counter_lines++ - 2;
            continue;
        }
		video_memory[i] = buffer[j];
		video_memory[i+1] = 0x02;
	}
	if (new_string) end_of_text = 160 * counter_lines++;
	return;
}

void print_char_videomemory(unsigned char byte){
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

void strcpy(volatile unsigned char* src, volatile const unsigned char* dst){
	while (*src++ = *dst++);
	return;
}

void c_variant_hex_from_byte(unsigned char byte, volatile unsigned char* buffer){
	unsigned char temp = byte / 16;
	if (temp > 9) *buffer++ = temp + 55;
	else *buffer++ = temp + 48;
	temp = byte % 16;
	if (temp > 9) *buffer++ = temp + 55;
	else *buffer++ = temp + 48;
	*buffer++ = '\0';
	return;
}