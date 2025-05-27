[bits 16]
; parameter dl - number of sectors, es:bx - address in RAM, cl - the sector number 2 - second sector (starts from 1, not 0)
disk_load: ; 'Read Sectors From Drive' function from BIOS int 13h
    pusha
    push dx
    push bx
    mov ah, 0x02
    mov al, dl ; number of sectors will read
    mov ch, 0 ; cylinder number
    mov dh, 0 ; head of sector
    mov dl, [BOOT_DRIVE]
    xor bx, bx
    mov es, bx
    pop bx
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
        jmp .return_code
    .error:
        mov bx, READ_DISK_ERROR_MESSAGE
        call print16
        jmp .return_code
    .return_code:
        mov al, 0
        mov bx, RETURN_CODE+6
        call hex_from_register16
        mov bx, RETURN_CODE
        call print_with_new_line16
    .panic_loop:
        jmp $
    .exit:
        ; add [LOADED_SECTORS_MESSAGE+16], al
        mov bx, LOADED_SECTORS_MESSAGE
        call print16
        xor ah, ah
        call print_int_from_byte
        call print_new_line16
        popa
        ret

READ_DISK_ERROR_MESSAGE db "Disk read error... ", 0
INCORRECT_NUMBER_SECTORS_MESSAGE db "Incorrect number of sectors readed ", 0
RETURN_CODE db "code: 000"
LOADED_SECTORS_MESSAGE db "Loaded sectors: ", 0