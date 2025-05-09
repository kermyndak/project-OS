[bits 32]
; section .data
; GDTbase EQU 00001000H
; IDTbase EQU 00000400H
section .text
    ; ;multiboot spec
    ; align 4
    ; dd 0x1BADB002            ;magic
    ; dd 0x00                  ;flags
    ; dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
extern kmain        ;kmain is defined in the c file

start:
    mov esp, stack_space	;set stack pointer
    mov ebx, TEST_MESSAGE
    call print86
    call kmain
    hlt		 	;halt the CPU

%include "src/boot/print32.asm"

TEST_MESSAGE db "Test message", 0

section .bss
resb 8192		;8KB for stack
stack_space:
