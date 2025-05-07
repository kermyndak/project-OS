[bits 16]
print16: ; dx - address string
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