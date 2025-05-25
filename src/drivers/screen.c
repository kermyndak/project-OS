#include "../types/types.h"
#include "screen.h"

// implementations
void print_text_videomemory(volatile const unsigned char * buffer, bool new_string){
	for (int i = end_of_text, j = 0; buffer[j] != '\0'; j++, end_of_text = i += 2){
        if (buffer[j] == '\n'){
            i = 160 * counter_lines++ - 2; // -2 for next iteration, ever exist '\0'
            continue;
        }
		if (buffer[j] == '\t'){
			video_memory[i] = ' ';
			video_memory[i + 1] = DEFAULT_COLOR;
			video_memory[i + 2] = ' ';
			video_memory[i + 3] = DEFAULT_COLOR;
#if DEFAULT_TAB_SIZE == FOUR_SPACES
			video_memory[i + 4] = ' ';
			video_memory[i + 5] = DEFAULT_COLOR;
			video_memory[i + 6] = ' ';
			video_memory[i + 7] = DEFAULT_COLOR;
			i += 6; // -2 for next iteration
			continue;
#endif
			i += 2;
			continue;
		}
		video_memory[i] = buffer[j];
		video_memory[i+1] = DEFAULT_COLOR;
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
	if (byte == '\t'){
		video_memory[end_of_text + 0] = ' ';
		video_memory[end_of_text + 1] = DEFAULT_COLOR;
		video_memory[end_of_text + 2] = ' ';
		video_memory[end_of_text + 3] = DEFAULT_COLOR;
#if DEFAULT_TAB_SIZE == FOUR_SPACES
		video_memory[end_of_text + 4] = ' ';
		video_memory[end_of_text + 5] = DEFAULT_COLOR;
		video_memory[end_of_text + 6] = ' ';
		video_memory[end_of_text + 7] = DEFAULT_COLOR;
		end_of_text += 8;
		return;
#endif
		end_of_text += 4;
		return;
	}
    video_memory[end_of_text] = byte;
    video_memory[end_of_text + 1] = DEFAULT_COLOR;
	end_of_text += 2;
    return;
}

void print_text_videomemory_with_color(
	volatile const unsigned char* buffer, 
	bool new_string, 
	colors color
){
	for (int i = end_of_text, j = 0; buffer[j] != '\0'; j++, end_of_text = i += 2){
        if (buffer[j] == '\n'){
            i = 160 * counter_lines++ - 2; // -2 for next iteration
            continue;
        }
		if (buffer[j] == '\t'){
			video_memory[i] = ' ';
			video_memory[i + 1] = DEFAULT_COLOR;
			video_memory[i + 2] = ' ';
			video_memory[i + 3] = DEFAULT_COLOR;
#if DEFAULT_TAB_SIZE == FOUR_SPACES
			video_memory[i + 4] = ' ';
			video_memory[i + 5] = DEFAULT_COLOR;
			video_memory[i + 6] = ' ';
			video_memory[i + 7] = DEFAULT_COLOR;
			i += 6; // -2 for next iteration
			continue;
#endif
			i += 2;
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

void print_char_videomemory_with_color(unsigned char byte, colors color){
	if (byte == '\n'){
		end_of_text = 160 * counter_lines++;
		return;
	}
    if (byte == '\t'){
		video_memory[end_of_text + 0] = ' ';
		video_memory[end_of_text + 1] = DEFAULT_COLOR;
		video_memory[end_of_text + 2] = ' ';
		video_memory[end_of_text + 3] = DEFAULT_COLOR;
#if DEFAULT_TAB_SIZE == FOUR_SPACES
		video_memory[end_of_text + 4] = ' ';
		video_memory[end_of_text + 5] = DEFAULT_COLOR;
		video_memory[end_of_text + 6] = ' ';
		video_memory[end_of_text + 7] = DEFAULT_COLOR;
		end_of_text += 8;
		return;
#endif
		end_of_text += 4;
		return;
	}
    video_memory[end_of_text] = byte;
    video_memory[end_of_text + 1] = color;
	end_of_text += 2;
    return;
}

void print_error_text_videomemory(volatile const unsigned char* buffer, bool new_string){
	for (int i = end_of_text, j = 0; buffer[j] != '\0'; j++, end_of_text = i += 2){
        if (buffer[j] == '\n'){
            i = 160 * counter_lines++ - 2; // -2 for next iteration
            continue;
        }
		if (buffer[j] == '\t'){
			video_memory[i] = ' ';
			video_memory[i + 1] = DEFAULT_COLOR;
			video_memory[i + 2] = ' ';
			video_memory[i + 3] = DEFAULT_COLOR;
#if DEFAULT_TAB_SIZE == FOUR_SPACES
			video_memory[i + 4] = ' ';
			video_memory[i + 5] = DEFAULT_COLOR;
			video_memory[i + 6] = ' ';
			video_memory[i + 7] = DEFAULT_COLOR;
			i += 6; // -2 for next iteration
			continue;
#endif
			i += 2;
			continue;
		}
		video_memory[i] = buffer[j];
		video_memory[i+1] = RED;
	}
	if (new_string){
		end_of_text = 160 * counter_lines++;
	}
	return;
}

void print_uint8_videomemory(unsigned char value){
	uint_from_byte(value, video_memory_buffer);
	print_text_videomemory(video_memory_buffer, false);
}

void print_int8_videomemory(char value){
	int_from_byte(value, video_memory_buffer);
	print_text_videomemory(video_memory_buffer, false);
}

void print_uint16_videomemory(unsigned short value){
	uint_from_word(value, video_memory_buffer);
	print_text_videomemory(video_memory_buffer, false);
}

void print_int16_videomemory(short value){
	int_from_word(value, video_memory_buffer);
	print_text_videomemory(video_memory_buffer, false);
}

void print_uint32_videomemory(unsigned long value){
	uint_from_dword(value, video_memory_buffer);
	print_text_videomemory(video_memory_buffer, false);
}

void print_int32_videomemory(long value){
	int_from_dword(value, video_memory_buffer);
	print_text_videomemory(video_memory_buffer, false);
}

void print_new_line(){
	end_of_text = 160 * counter_lines++;
	return;
}

void clear_screen(){
	for (int i = 0, j = 0; j < 80 * 25 * 2; j += 2){
		video_memory[j] = ' ';
		video_memory[j+1] = DEFAULT_COLOR;
	}
	counter_lines = 1;
	end_of_text = 0;
	return;
}