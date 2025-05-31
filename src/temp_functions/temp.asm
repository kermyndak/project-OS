[bits 32]
section .text
global _checkPCI
global detect_memory
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