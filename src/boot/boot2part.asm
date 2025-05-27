[org 0x7e00]
KERNEL_POINT equ 0x1000

[bits 16]
init:
    mov bx, BOOT2LOADER_HELLO_MESSAGE
    call print_with_new_line16

    mov cl, [480]
    mov [BOOT_DRIVE], cl

    mov cl, 4
    mov bx, KERNEL_POINT
    mov dl, 20 ; count of sectors
    call disk_load
    call protected_mode_enable
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

BOOT_DRIVE db 0
BOOT2LOADER_HELLO_MESSAGE db "Second part of bootloader loaded", 0
PROTECTED_MODE_MESSAGE db "Protected mode started", 0
times 1024-($-$$) db 's'