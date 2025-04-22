#include "headers/kernel_handler.h"
#include "../cpu/cpu.h"
#include "../drivers/screen.h"
#include "../types/types.h"

void kmain(void){
	// clear screen
    clear_screen();
	cli();
	print_text_videomemory("Identification proccessor...", true);
	cpuid(0, longs_buffer);
#ifdef DEBUG_MODE
	print_text_videomemory("EAX, EBX, EDX, ECX registers: ", false);
	hex_from_array_extended_registers(longs_buffer, main_buffer, 4);
	print_text_videomemory(main_buffer, true);
#endif
	print_text_videomemory("Proccessor: ", false);
	convert_array_extended_registers_to_string_about_proccessor(longs_buffer, main_buffer);
	print_text_videomemory(main_buffer, true);
	// print_text_videomemory("some text\nsome text\nsome text", false);
	// print_text_videomemory("some text\nsome text\nsome text", true);
    // c_variant_hex_from_byte(228, main_buffer);
	// print_text_videomemory(main_buffer, true);
	// unsigned long var = read_cr0();
	// hex_from_extended_register(var, main_buffer);
	// print_text_videomemory(main_buffer, true);
	
	//c_variant_hex_from_byte(228, main_buffer);
	//print_text_videomemory(main_buffer, true);
	return;
}