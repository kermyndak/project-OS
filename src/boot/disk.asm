; real mode
[bits 16]
read_drive_parameters:
    pusha
    mov bx, READ_DRIVE_PARAMETERS_MESSAGE
    call print_with_new_line16
    xor bx, bx
    xor eax, eax
    mov ah, 0x08
    mov dl, [BOOT_DRIVE]
    mov es, bx ; to work around some buggy BIOS
    mov di, bx
    int 0x13
    jc .error
    .done:
        mov bx, DISK_DRIVES_NUMBER_MESSAGE
        add [DISK_DRIVES_NUMBER_MESSAGE+28], dl
        call print16
        call print_new_line16

        mov al, dh
        mov bx, MAX_VALUE_HEAD+29
        call hex_from_register16
        mov bx, MAX_VALUE_HEAD
        call print_with_new_line16

        mov al, ch
        mov bx, LOW_BITS_OF_MAXIMUM_CYLINDER_NUMBER+57
        call hex_from_register16
        mov bx, LOW_BITS_OF_MAXIMUM_CYLINDER_NUMBER
        call print_with_new_line16

        push cx
        shr cl, 5 ; CL >> 5
        mov al, cl
        mov bx, HIGH_TWO_BITS_OF_MAXIMUM_CYLINDER_NUMBER+65
        call hex_from_register16
        mov bx, HIGH_TWO_BITS_OF_MAXIMUM_CYLINDER_NUMBER
        call print_with_new_line16
        pop cx

        and cl, 31 ; and 00011111
        mov al, cl
        mov bx, MAXIMUM_SECTOR_NUMBER+46
        call hex_from_register16
        mov bx, MAXIMUM_SECTOR_NUMBER
        call print_with_new_line16
        jmp .exit
    .error:
        mov bx, ERROR_MESSAGE
        call print16
        jmp .return_code
    .return_code:
        mov al, ah
        mov bx, RETURN_CODE+6 ; define in disk_loader.asm
        call hex_from_register16
        mov bx, RETURN_CODE
        call print_with_new_line16
    .panic_loop:
        jmp $
    .exit:
        popa
        ret

READ_DRIVE_PARAMETERS_MESSAGE db "- - Drive parameters - - ", 0
DISK_DRIVES_NUMBER_MESSAGE db "Number of hard disk drives: 0", 0
MAX_SIZE_MESSAGE db "Maximum size of registers for read sectors", 0
MAX_VALUE_HEAD db "Logical last index of heads: 00", 0
LOW_BITS_OF_MAXIMUM_CYLINDER_NUMBER db "Low eight bits of maximum cylinder number (register CH): 00", 0
HIGH_TWO_BITS_OF_MAXIMUM_CYLINDER_NUMBER db "High two bits of maximum cylinder number (bits 7-6) register CL: 00", 0
MAXIMUM_SECTOR_NUMBER db "Maximum sector number (bits 5-0) register CL: 00", 0
ERROR_MESSAGE db "Error!", 0