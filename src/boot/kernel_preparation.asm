;;kernel.asm
bits 32 ; for 32 bits operations

section .data
GDTbase EQU 00001000H
IDTbase EQU 00000400H
section .text
    ;multiboot spec
    align 4
    dd 0x1BADB002            ;magic
    dd 0x00                  ;flags
    dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
extern kmain	        ;kmain is defined in the c file

start:
    cli 			;block interrupts
    ;lgdt GDTbase
    ;mov eax, cr0 
    ;or al, 1       ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    ;mov cr0, eax
    mov esp, stack_space	;set stack pointer
    call kmain
    hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space:
