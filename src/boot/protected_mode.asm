[bits 16]
protected_mode_enable:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:protected_mode_init

[bits 32]
protected_mode_init:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp
    call protected_mode_enabled

; Part for output information about enable protected mode
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
    popa
    ret