[bits 16]
; parameter dl - number of sectors
disk_load: ; 'Read Sectors From Drive' function from BIOS int 13h
    pusha
    push dx
    mov ah, 0x02
    mov al, dl ; number of sectors will read
    mov ch, 0 ; cylinder number
    mov cl, 2 ; the sector number 2 - second sector (starts from 1, not 0)
    mov dh, 0 ; head of sector
    mov dl, [BOOT_DRIVE]
    xor bx, bx
    mov es, bx
    mov bx, KERNEL_POINT
    int 0x13

    pop dx
    jc .error
    cmp al, dl
    jne .incorrect_number_sectors
    .done:
        jmp .exit
    .incorrect_number_sectors:
        mov bx, INCORRECT_NUMBER_SECTORS_MESSAGE
        call print16
        jmp .exit
    .error:
        mov bx, READ_DISK_ERROR_MESSAGE
        call print16
    .exit:
        mov ah, 0
        mov bx, RETURN_CODE+6
        call hex_from_register16
        mov bx, RETURN_CODE
        call print16
        call print_new_line16
        popa
        ret

READ_DISK_ERROR_MESSAGE db "Disk read error... ", 0
INCORRECT_NUMBER_SECTORS_MESSAGE db "Incorrect number of sectors read ", 0
RETURN_CODE db "code: 000"