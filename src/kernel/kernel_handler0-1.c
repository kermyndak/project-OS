#include "headers/kernel_handler.h"
#include "../cpu/cpu.h"
#include "../drivers/screen.h"
#include "../types/types.h"

void kmain(void){
	// clear screen
    clear_screen();
	//_checkPCI();
	// __asm__("pusha\n\tpopa");
	cli();
	print_text_videomemory("some text\nsome text\nsome text", true);
	print_text_videomemory("some text\nsome text\nsome text", true);
    hex_from_byte(228, main_buffer);
	//strcpy(main_buffer, "qwerty");
    //print_text_videomemory(main_buffer, true);
	//c_variant_hex_from_byte(228, main_buffer);
	//print_text_videomemory(main_buffer, true);
    //_checkPCI();
	return;
}