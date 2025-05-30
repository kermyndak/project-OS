[bits 32]
; section .data
section .text
    ; ;multiboot spec
    align 4
    dd 0x1BADB002            ;magic
    dd 0x00                  ;flags
    dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
extern kmain        ;kmain is defined in the c file

start:
    mov ebp, stack_space	;set stack pointer
    mov esp, ebp ; not necessary
    mov ebx, KERNEL_STARTED_MESSAGE
    call print86

    ;mov ebx, DISK_PARAMETER_MESSAGE
    ;call print86

    ;movzx ax, BYTE[480]
    ;mov [BOOT_DRIVE], al
    ;mov ebx, KERNEL_STARTED_MESSAGE
    ;call hex_from_register16
    ;call print86
    ;call print_new_line86

    call kmain
    jmp $
    hlt		 	;halt the CPU

%include "src/boot/print32.asm"

KERNEL_STARTED_MESSAGE db "Kernel Started!", 10, 0
DISK_PARAMETER_MESSAGE db "Disk parameter ", 0

section .bss
resb 8192		;8KB for stack
stack_space:
