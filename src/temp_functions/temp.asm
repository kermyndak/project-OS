bits 32
section .text
global _checkPCI
global hex_from_byte
extern print_text_videomemory

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

    movzx eax, byte[esp + 4]
    mov edx, [esp + 8]
    ;
    pusha
    sub esp, 8
    mov ebx, buffer_temp
    mov [esp], ebx
    mov ebx, [buffer_temp]
    mov [esp + 4], ebx
    call print_text_videomemory
    popa
    ;
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
        ;
        pusha
        mov [buffer_temp], eax
        mov [buffer_temp + 4], ebx
        mov [buffer_temp + 8], ecx
        mov [buffer_temp + 12], edx
        sub esp, 16
        mov ebx, buffer_temp
        mov [esp], ebx
        mov ebx, [buffer_temp]
        mov [esp + 4], ebx
        call print_text_videomemory
        popa
        ;
        ret

section .bss
    resb 150
section .data
    buffer_temp dd 65, 0, 0, 0, 0, 0, 0