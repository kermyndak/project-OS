[org 0x7c00]
BOOT2LOADER equ 0x7e00

[bits 16]
before_load:
    mov	[BOOT_DRIVE], dl
	mov	bp, 0x9000
	mov	sp, bp
    mov bx, REAL_MODE_MESSAGE
    sub dl, 0x80
    add [REAL_MODE_MESSAGE+25], dl ; Set disk number in message
    call print_with_new_line16
    call read_drive_parameters

load_second_part_bootloader:
    ;mov es, 0
    mov cl, 2
    mov bx, BOOT2LOADER
    mov dl, 2 ; count of sectors
    call disk_load
    mov bx, [BOOT_DRIVE]
    mov [480], bx ; 480 - random number :)
    jmp BOOT2LOADER

    jmp $

%include "src/boot/print16.asm"
%include "src/boot/disk_loader.asm"
%include "src/boot/disk.asm"

BOOT_DRIVE db 0
REAL_MODE_MESSAGE db "Started in real mode (HD 1)", 0
times 510-($-$$) db 'k'
dw 0xAA55