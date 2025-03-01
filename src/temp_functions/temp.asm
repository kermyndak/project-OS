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
    add al, 48
    add ah, 48
    mov [edx], al
    mov [edx + 1], ah
    mov al, 0
    mov [edx + 2], al
    mov esp, ebp
    pop ebp
    ret
