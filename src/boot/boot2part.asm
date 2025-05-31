[org 0x7e00]
KERNEL_POINT equ 0x1000

[bits 16]
init:
    mov bx, BOOT2LOADER_HELLO_MESSAGE
    call print_with_new_line16

    mov cl, [480]
    mov [BOOT_DRIVE], cl

    call detect_low_memory ; detect memory volume in real mode

    call detect_high_memory

    call print_memory_map
    call print_full_size_memory
    call print_free_memory_size

    call read_drive_parameters ; get drive parameters

    %ifdef BOOT2PART_SIZE
        %define INITIAL_SECTOR_KERNEL BOOT2PART_SIZE+2
        mov cl, INITIAL_SECTOR_KERNEL
    %else
        mov cl, 4
    %endif
    mov bx, KERNEL_POINT ; Kernel address
    %ifdef KERNEL_SIZE
        mov dl, KERNEL_SIZE ; count of sectors
    %else 
        mov dl, 5
    %endif
    call disk_load
    ;call protected_mode_enable
    jmp $

[bits 32]
protected_mode_enabled:
    mov ebx, PROTECTED_MODE_MESSAGE
    call clear_screen86
    call print86
    jmp KERNEL_POINT
    jmp $

%include "src/boot/protected_mode.asm"
%include "src/boot/gdt.asm"
%include "src/boot/print16.asm"
%include "src/boot/disk_loader.asm"
%include "src/boot/disk.asm"
%include "src/boot/ram_detect.asm"

section .text
BOOT_DRIVE db 0
BOOT2LOADER_HELLO_MESSAGE db "Second part of bootloader loaded", 0
PROTECTED_MODE_MESSAGE db "Protected mode started", 0
times 2560-($-$$) db 's'