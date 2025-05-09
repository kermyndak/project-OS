[bits 32]
%ifndef DEFAULT_COLOR
%define DEFAULT_COLOR 0x02
%endif

VIDEO_MEMORY equ 0xb8000

print86:
    pusha
    mov ecx, [end_of_text86]
    mov edx, VIDEO_MEMORY
    add edx, ecx
    .start:
        mov al, byte[ebx]
        mov ah, DEFAULT_COLOR
        cmp al, 0
        je .end

        cmp al, 10
        je .new_line

        mov [edx], ax
        inc ebx
        add edx, 2
        jmp .start
    .new_line: ; ecx = 160 * counter_lines++ - 2
        push eax
        mov al, 160
        mul byte[counter_lines86]
        movzx ecx, ax
        mov al, [counter_lines86]
        inc al
        mov [counter_lines86], al
        pop eax
        mov edx, VIDEO_MEMORY
        add edx, ecx
        inc ebx
        jmp .start
    .end:
        sub edx, VIDEO_MEMORY
        mov [end_of_text86], edx
        popa
        ret

print_new_line86: ; end_of_text = 160 * counter_lines++;
    pusha
    mov al, 160
    mul byte[counter_lines86]
    movzx ecx, ax
    mov [end_of_text86], ecx
    mov al, [counter_lines86]
    inc al
    mov [counter_lines86], al
    popa
    ret

clear_screen86:
    pusha
    xor bx, bx
    mov ecx, 4000
    mov edx, VIDEO_MEMORY
    mov al, 32
    mov ah, DEFAULT_COLOR
    .loop:
        mov [edx], ax
        add edx, 2
        dec ecx
        loop .loop
    mov [end_of_text86], bx
    inc bx
    mov [counter_lines86], bx
    popa
    ret

hex_from_register16: ; parameters: ax - target register, bx - target buffer (Copied from print16.asm)
    pusha
    xor ah, ah
    mov dl, 16
    div dl
    cmp al, 9
    jg .add_character_al
    jmp .add_digit_al

    .add_character_al:
        add al, 55
        mov [ebx], al
        cmp ah, 9
        jg .add_character_ah
        jmp .add_digit_ah

    .add_digit_al:
        add al, 48
        mov [ebx], al
        cmp ah, 9
        jg .add_character_ah
        jmp .add_digit_ah

    .add_character_ah:
        add ah, 55
        mov [ebx+1], ah
        jmp .final

    .add_digit_ah:
        add ah, 48
        mov [ebx+1], ah
        jmp .final

    .final:
        mov al, 0
        mov [ebx+2], al
        popa
        ret

counter_lines86 db 2
end_of_text86 dq 160