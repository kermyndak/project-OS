[org 0x7c00]
KERNEL_POINT equ 0x1000

[bits 16]
before_load_kernel:
    mov	[BOOT_DRIVE], dl
	mov	bp, 0x9000
	mov	sp, bp
    mov bx, REAL_MODE_MESSAGE
    ; sub dl, 0x80
    ; add [REAL_MODE_MESSAGE+25], dl ; Set disk number in message
    ; call print16
    ; call print_new_line16

load_kernel:
    ;movzx ax, [BOOT_DRIVE]
    ;mov bx, DRIVE_MESSAGE
    ;call hex_from_register16
    ;call print16
    ;call print_new_line16

    mov dl, 20
    call disk_load
    mov bx, KERNEL_POINT
    call print16
    mov bx, REAL_MODE_MESSAGE
    ;call hex_from_register16
    ;mov bx, PROTECTED_MODE_MESSAGE
    call print16

    call protected_mode_enable
    jmp $

[bits 32]
protected_mode_enabled:
    mov ebx, PROTECTED_MODE_MESSAGE
    call clear_screen86
    call print86
    jmp KERNEL_POINT
    jmp $


%include "src/boot/print16.asm"
%include "src/boot/print32.asm"
%include "src/boot/protected_mode.asm"
%include "src/boot/gdt.asm"
%include "src/boot/kernel_loader.asm"

BOOT_DRIVE db 0
REAL_MODE_MESSAGE db "Started in real mode (HD 1)", 0
PROTECTED_MODE_MESSAGE db "Protected mode started", 0
times 510-($-$$) db 'k'
dw 0xAA55