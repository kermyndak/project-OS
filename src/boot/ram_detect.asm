[bits 16]
detect_low_memory:
    pusha
    mov bx, DETECT_MEMORY_MESSAGE
    call print_with_new_line16
    clc
    int 0x12
    jc .error
    .done:
        mov bx, SUCCESS_DETECT_LOW_MEMORY_MESSAGE
        call print16
        add ax, 1 ; add current 1 KB
        call print_int_from_byte
        mov bx, KB_MESSAGE
        call print16
        call print_new_line16
        jmp .exit
    .error:
        mov bx, ERROR_MESSAGE
        call print16
        jmp .panic_loop
    .panic_loop:
        jmp $
    .exit:
        popa
        ret

DETECT_MEMORY_MESSAGE db "- - Detect memory - -", 0
SUCCESS_DETECT_LOW_MEMORY_MESSAGE db "Detect memory volume: ", 0
KB_MESSAGE db "KB", 0