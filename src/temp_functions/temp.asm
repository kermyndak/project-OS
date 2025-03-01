bits 32
section .text
global _checkPCI
global hex_from_byte

_checkPCI:
    push ebp
    mov ebp, esp
    movzx eax, bl
    shl eax, 16

    movzx esi, bh
    shl esi, 11
    or eax, esi

    ;call

    mov esp, ebp
    pop ebp
    ret
  
hex_from_byte:
    push ebp
    mov ebp, esp

    mov eax, [ecx]
    mov bl, 16
    div bl
    cmp al, 9
    jg .add_character_al
    jmp .add_digit_al

    .add_character_al:
        add al, 55
        mov [edx], al
        cmp ah, 9
        jg .add_character_ah
        jmp .add_digit_ah

    .add_digit_al:
        add al, 48
        mov [edx], al
        cmp ah, 9
        jg .add_character_ah
        jmp .add_digit_ah

    .add_character_ah:
        add ah, 55
        mov [edx+1], ah
        jmp .final

    .add_digit_ah:
        add ah, 48
        mov [edx+1], ah
        jmp .final

    .final:
        mov al, 0
        mov [edx + 2], al

        mov esp, ebp
        pop ebp
        ret
