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

print_with_new_line16: ; bx - address string
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
        mov ah, 0x0e
        mov al, 0x0a
        int 0x10
        mov al, 0x0d
        int 0x10
        popa
        ret

hex_from_register16: ; parameters: ax - target register, bx - target buffer
    pusha
    xor ah, ah
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

print_int_from_byte: ; ax - number
    pusha
    mov bx, 10000
    .cycle:
        cmp bx, 10
        jl .last_symbol
        push ax
        xor dx, dx
        mov cl, 48
        div bx
        cmp ax, 0
        je .cycle_preparation
        mov dl, 10
        div dl
        add cl, ah
        .print_symbol:
            mov al, cl
            mov ah, 0x0e
            int 0x10
        .cycle_preparation:
            mov ax, bx
            xor dx, dx
            mov bx, 10
            div bx
            mov bx, ax
            pop ax
            jmp .cycle
    .last_symbol:
        mov cl, '0'
        mov dl, 10
        div dl
        add cl, ah
        mov al, cl
        mov ah, 0x0e
        int 0x10
    popa
    ret