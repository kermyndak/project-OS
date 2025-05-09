[bits 32]
%ifndef DEFAULT_COLOR
%define DEFAULT_COLOR 0x02
%endif

VIDEO_MEMORY equ 0xb8000

print86:
    pusha
    mov edx, VIDEO_MEMORY
    .start:
    mov al, byte[ebx]
    mov ah, DEFAULT_COLOR
    cmp al, 0
    je .end

    mov [edx], ax
    inc ebx
    add edx, 2 
    jmp .start
    .end:
        popa
        ret

print_new_line86:
    pusha
    mov edx, VIDEO_MEMORY
    mov al, 0x0a
    mov ah, DEFAULT_COLOR
    mov [edx], ax
    add edx, 2
    mov al, 0x0d
    mov [edx], ax
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

counter_lines86 db 1
end_of_text86 dq 0