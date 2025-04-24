#include "../types/types.h"

#ifndef SCREEN_H
#define SCREEN_H

//declarations

/* Values for colors
	0 - Black, 1 - Blue, 2 - Green, 3 - Cyan, 4 - Red, 5 - Magenta, 
	6 - Brown, 7 - Light Grey, 8 - Dark Grey, 9 - Light Blue, 
	10/a - Light Green, 11/b - Light Cyan, 12/c - Light Red, 
	13/d - Light Magenta, 14/e - Light Brown, 15/f – White.

	Uses 2 bytes, first for value, second for color
*/
void print_text_videomemory(volatile const unsigned char* buffer, bool new_string);
void print_char_videomemory(unsigned char byte);
void print_text_videomemory_with_color(volatile const unsigned char* buffer, bool new_string, char color);
void print_char_videomemory_with_color(unsigned char byte, char color);
void print_error_text_videomemory(volatile const unsigned char* buffer, bool new_string);
void print_new_line();
void clear_screen();

// Video memory address
volatile char* video_memory = (volatile char*)0xb8000;

// For control video buffer
static char counter_lines = 1;
static int end_of_text = 0;

//realizations 
void print_text_videomemory(volatile const unsigned char * buffer, bool new_string){
	for (int i = end_of_text, j = 0; buffer[j] != '\0'; j++, end_of_text = i += 2){
        if (buffer[j] == '\n'){
            i = 160 * counter_lines++ - 2; // -2 for next iteration
            continue;
        }
		video_memory[i] = buffer[j];
		video_memory[i+1] = 0x02;
	}
	if (new_string){
		end_of_text = 160 * counter_lines++;
	}
	return;
}

void print_char_videomemory(unsigned char byte){
	if (byte == '\n'){
		end_of_text = 160 * counter_lines++;
		return;
	}
    video_memory[0] = byte;
    video_memory[1] = 0x02;
    return;
}

void print_text_videomemory_with_color(
	volatile const unsigned char* buffer, 
	bool new_string, 
	char color
){
	for (int i = end_of_text, j = 0; buffer[j] != '\0'; j++, end_of_text = i += 2){
        if (buffer[j] == '\n'){
            i = 160 * counter_lines++ - 2; // -2 for next iteration
            continue;
        }
		video_memory[i] = buffer[j];
		video_memory[i+1] = color;
	}
	if (new_string){
		end_of_text = 160 * counter_lines++;
	}
	return;
}

void print_char_videomemory_with_color(unsigned char byte, char color){
	if (byte == '\n'){
		end_of_text = 160 * counter_lines++;
		return;
	}
    video_memory[0] = byte;
    video_memory[1] = color;
    return;
}

void print_error_text_videomemory(volatile const unsigned char* buffer, bool new_string){
	for (int i = end_of_text, j = 0; buffer[j] != '\0'; j++, end_of_text = i += 2){
        if (buffer[j] == '\n'){
            i = 160 * counter_lines++ - 2; // -2 for next iteration
            continue;
        }
		video_memory[i] = buffer[j];
		video_memory[i+1] = 0x04;
	}
	if (new_string){
		end_of_text = 160 * counter_lines++;
	}
	return;
}

void print_new_line(){
	end_of_text = 160 * counter_lines++;
	return;
}

void clear_screen(){
	for (int i = 0, j = 0; j < 80 * 25 * 2; j += 2){
		video_memory[j] = ' ';
		video_memory[j+1] = 0x02;
	}
	counter_lines = 1;
	end_of_text = 0;
	return;
}

#endif