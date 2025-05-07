[bits 32]
VIDEO_MEMORY equ 0xb8000
COLOR equ 0x0f

print32:
    pusha
    mov edx, VIDEO_MEMORY
    .start:
    mov al, byte[ebx]
    mov ah, COLOR
    cmp al, 0
    je .end

    mov [edx], ax
    inc ebx
    add edx, 2 
    jmp .start
    .end:
        popa
        ret

print_new_line32:
    pusha
    mov edx, VIDEO_MEMORY
    mov al, 0x0a
    mov ah, COLOR
    mov [edx], ax
    add edx, 2
    mov al, 0x0d
    mov [edx], ax
    popa
    ret