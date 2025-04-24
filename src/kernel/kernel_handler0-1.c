#include "headers/kernel_handler.h"
#include "../cpu/cpu.h"
#include "../drivers/screen.h"
#include "../types/types.h"
#ifdef TEST_MODE
	#include "../test/test.h"
#endif

void kmain(void){
	// clear screen
    clear_screen();
	cli();
	// Identification proccessor
	print_text_videomemory("Identification proccessor...", true);
	cpuid(0, longs_buffer);
#ifdef DEBUG_MODE
	print_text_videomemory("EAX, EBX, EDX, ECX registers,\nwhere CPUID with code = 0: ", false);
	hex_from_array_extended_registers_with_separator(longs_buffer, main_buffer, 4, ':');
	print_text_videomemory(main_buffer, true);
	print_new_line();
#endif
	print_text_videomemory("\tProccessor: ", false);
	convert_array_extended_registers_to_string_about_proccessor(longs_buffer, main_buffer);
	print_text_videomemory(main_buffer, true);

#ifdef TEST_MODE
	print_new_line();
	if (test()){
		print_text_videomemory_with_color("Tests completed.", true, GREEN);
	} else {
		print_text_videomemory_with_color("Tests failed.", true, RED);
	}
	return;
#endif
	cpuid(1, longs_buffer);
	hex_from_array_extended_registers_with_separator(longs_buffer, main_buffer, 4, ':');
	print_text_videomemory(main_buffer, true);
	bits_with_indexes_from_extended_register(longs_buffer[0], main_buffer, ZERO_FORMAT);
	print_text_videomemory(main_buffer, true);
	// print_text_videomemory(main_buffer, true);
	// unsigned long var = read_cr0();
	// hex_from_extended_register(var, main_buffer);
	// print_text_videomemory(main_buffer, true);
	
	//c_variant_hex_from_byte(228, main_buffer);
	//print_text_videomemory(main_buffer, true);
	return;
}