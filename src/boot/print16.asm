[bits 16]
print16: ; bx - address string
    pusha
    .start:
        mov al, [bx]
        cmp al, 0
        je .end
        mov ah, 0x0e
        int 0x10

        inc bx
        jmp .start
    .end:
        popa
        ret

print_new_line16:
    pusha
    mov ah, 0x0e
    mov al, 0x0a
    int 0x10
    mov al, 0x0d
    int 0x10
    popa
    ret

; print_with_new_line16: ; bx - address string
;     pusha
;     .start:
;         mov al, [bx]
;         cmp al, 0
;         je .end
;         mov ah, 0x0e
;         int 0x10

;         inc bx
;         jmp .start
;     .end:
;         mov ah, 0x0e
;         mov al, 0x0a
;         int 0x10
;         mov al, 0x0d
;         int 0x10
;         popa
;         ret

hex_from_register16: ; parameters: ax - target register, bx - target buffer
    pusha
    mov dl, 16
    div dl
    cmp al, 9
    jg .add_character_al
    jmp .add_digit_al

    .add_character_al:
        add al, 55
        mov [bx], al
        cmp ah, 9
        jg .add_character_ah
        jmp .add_digit_ah

    .add_digit_al:
        add al, 48
        mov [bx], al
        cmp ah, 9
        jg .add_character_ah
        jmp .add_digit_ah

    .add_character_ah:
        add ah, 55
        mov [bx+1], ah
        jmp .final

    .add_digit_ah:
        add ah, 48
        mov [bx+1], ah
        jmp .final

    .final:
        mov al, 0
        mov [bx + 2], al
        popa
        ret