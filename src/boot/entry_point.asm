[org 0x7c00]
KERNEL_POINT equ 0x1000

[bits 16]
load_kernel:
    mov	[BOOT_DRIVE], dl
	mov	bp, 0x9000
	mov	sp, bp
    mov bx, REAL_MODE_MESSAGE
    call print16
    call print_new_line16

    mov bx, TRY_PROTECTED_MODE_MESSAGE
    call print16
    call print_new_line16
    call protected_mode_enable
    ;call KERNEL_POINT
    jmp $

[bits 32]
protected_mode_enabled:
    mov ebx, PROTECTED_MODE_MESSAGE
    call print32
    jmp $


%include "src/boot/print16.asm"
%include "src/boot/print32.asm"
%include "src/boot/protected_mode.asm"
%include "src/boot/gdt.asm"

BOOT_DRIVE db 0
REAL_MODE_MESSAGE db "Started in real mode", 0
TRY_PROTECTED_MODE_MESSAGE db "Try enable protected mode", 0
PROTECTED_MODE_MESSAGE db "Protected mode started", 0
times 510-($-$$) db 'k'
dw 0xAA55