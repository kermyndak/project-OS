; real mode
[bits 16]
read_drive_parameters:
    pusha
    xor bx, bx
    xor eax, eax
    mov ah, 0x08
    mov dl, [BOOT_DRIVE]
    mov es, bx ; to work around some buggy BIOS
    mov di, bx
    int 0x13
    jc .error
    .done:
        push bx
        mov bx, DISK_DRIVES_NUMBER_MESSAGE
        add [DISK_DRIVES_NUMBER_MESSAGE+28], dl
        call print16
        call print_new_line16
        pop bx
        jmp .exit
    .error:
        mov bx, ERROR_MESSAGE
        call print16
        call print_new_line16
    .exit:
        popa
        ret

BOOT_DRIVE db 0
DISK_DRIVES_NUMBER_MESSAGE db "Number of hard disk drives: 0", 0
ERROR_MESSAGE db "Error!", 0