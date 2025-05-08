[bits 16]
get_key:
    mov ah, 0x00
    int 0x16
    