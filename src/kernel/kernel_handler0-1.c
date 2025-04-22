#include "headers/kernel_handler.h"
#include "../cpu/cpu.h"
#include "../drivers/screen.h"
#include "../types/types.h"

void kmain(void){
	// clear screen
    clear_screen();
	cli();
	print_text_videomemory("some text\nsome text\nsome text", false);
	print_text_videomemory("some text\nsome text\nsome text", true);
    c_variant_hex_from_byte(228, main_buffer);
	print_text_videomemory(main_buffer, true);
	// int msr;
	// asm volatile ( "rdtsc\n\t"    // Returns the time in EDX:EAX.
    //     "shl $32, %%edx\n\t"  // Shift the upper bits left.
    //     "or %%edx, %0"        // 'Or' in the lower bits.
    //     : "=a" (msr)
    //     :
    //     : "edx");
	unsigned long var = read_cr0();
	unsigned long tem = 269484304;
	hex_from_extended_register(tem, main_buffer);
	print_text_videomemory(main_buffer, true);
	// c_variant_hex_from_byte(msr, main_buffer);
	// print_text_videomemory(main_buffer, true);

	// c_variant_hex_from_byte(msr, main_buffer);
	// print_text_videomemory(main_buffer, true);
	//strcpy(main_buffer, "qwerty");
    //print_text_videomemory(main_buffer, true);
	//c_variant_hex_from_byte(228, main_buffer);
	//print_text_videomemory(main_buffer, true);
	return;
}