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

detect_high_memory:
    pusha
    mov di, result
    xor bp, bp
    xor ebx, ebx
    mov edx, 0x0534D4150
    mov eax, 0xe820
    mov [es:di + 20], dword 1
    mov ecx, 24
    int 0x15
    jc .dont_supported
    mov edx, 0x0534D4150
    cmp eax, edx
    jne .error
    test ebx, ebx
    je .error
    jmp .jmpin
    .cycle:
        mov eax, 0xe820
        mov [es:di + 20], dword 1
        mov ecx, 24
        int 0x15
        jc .e820f
	    mov edx, 0x0534D4150
    .jmpin:
        jcxz .skipent		; skip any 0 length entries
        cmp cl, 20		; got a 24 byte ACPI 3.X response?
        jbe .notext
        test byte [es:di + 20], 1	; if so: is the "ignore this data" bit clear?
        je .skipent
    .notext:
        mov ecx, [es:di + 8]
        or ecx, [es:di + 12]
        jz .skipent
        inc bp
        add di, 24
    .skipent:
        test ebx, ebx		; if ebx resets to 0, list is complete
        jne .cycle
    .e820f:
        mov [number_entries], bp
        clc
        mov bx, COUNT_ENTRIES_MESSAGE
        call print16
        mov ax, bp
        call print_int_from_byte
        call print_new_line16
        jmp .exit
    .dont_supported:
        mov bx, DONT_SUPPORTED_DETECT_MEMORY_MESSAGE
        call print_with_new_line16
        jmp .exit
    .error:
        mov bx, ERROR_DETECT_MEMORY_MESSAGE
        call print_with_new_line16
        jmp .panic_loop
    .panic_loop:
        jmp $
    .exit:
        popa
        ret

print_memory_map:
    pusha
    mov bx, MEMORY_MAP_MESSAGE
    call print_with_new_line16
    mov bx, MEMORY_MAP_HEADER
    call print_with_new_line16
    mov cx, word[number_entries]
    xor dx, dx
    .main_cycle:
        push cx
        push dx
        mov cx, 8
        .base_address_cycle:
            mov bx, cx
            dec bx
            add bx, dx
            mov al, byte[result+bx]
            .print_record:
                mov bx, DETECT_MEMORY_MESSAGE
                call hex_from_register16
                call print16
                loop .base_address_cycle
        mov bx, SEPARATOR
        call print16

        mov cx, 8
        .length_cycle:
            mov bx, cx
            dec bx
            add bx, 8
            add bx, dx
            mov al, byte[result+bx]
            .print_record2:
                mov bx, DETECT_MEMORY_MESSAGE
                call hex_from_register16
                call print16
                loop .length_cycle
        mov bx, SEPARATOR
        call print16
        
        xor bx, bx
        add bx, dx
        add bx, 16
        mov al, byte[result+bx]
        cmp al, 1
        je .print_free_memory
        jmp .print_reserved_memory
        .print_free_memory:
            mov bx, FREE_MEMORY_MESSAGE
            call print16
            jmp .print_volume
        .print_reserved_memory:
            mov bx, RESERVED_MEMORY_MESSAGE
            call print16
            jmp .print_volume
        
        .print_volume:
            mov bx, SEPARATOR
            call print16
            call get_volume_memory
        .cycle_preparation:
            pop dx
            pop cx
            add dx, 24
            loop .main_cycle
    .exit:
        popa
        ret

get_volume_memory: ; parameter dx - start of record
    pusha
    mov cx, dx
    mov bx, dx
    add bx, 8
    mov eax, dword[result+bx]
    mov edx, dword[result+bx+4]
    
    mov ebx, 1024
    div ebx

    mov bx, cx ; save volume in KB in 4 part of record 8 + 8 + 4
    add bx, 20
    mov dword[result+bx], eax

    cmp eax, 1024
    jge .print_megabytes
    
    call print_int_from_byte
    mov bx, KB_MESSAGE
    call print_with_new_line16
    
    jmp .exit
    .print_megabytes:
        mov ebx, 1024
        div ebx
        cmp eax, 1024
        jge .print_gigabytes
        call print_int_from_byte
        mov bx, MB_MESSAGE
        call print_with_new_line16
        jmp .exit
    .print_gigabytes:
        mov ebx, 1024
        div ebx
        call print_int_from_byte
        mov bx, GB_MESSAGE
        call print_with_new_line16
        jmp .exit
    .exit:
        popa
        ret

print_full_size_memory:
    pusha
    mov cx, word[number_entries]
    xor dx, dx
    xor eax, eax
    .full_memory_size:
        push dx
        mov bx, dx
        add bx, 20
        mov edx, dword[result+bx]
        add eax, edx
        add dword[result+44], edx ; for correct result
        pop dx
        add dx, 24
        dec cx
        cmp cx, 0
        jne .full_memory_size
    mov bx, FULL_SIZE_MEMORY_MESSAGE
    call print16

    mov eax, dword[result+44]
    xor edx, edx ; for correct divide
    mov ebx, 1024 ; get megabytes
    div ebx
    cmp eax, 1024
    jge .print_gigabytes
    call print_int_from_byte
    mov bx, MB_MESSAGE
    call print_with_new_line16
    jmp .exit
    .print_gigabytes:
        mov ebx, 1024
        div ebx
        call print_int_from_byte
        mov bx, GB_MESSAGE
        call print_with_new_line16
        jmp .exit
    .exit:
        popa
        ret

print_free_memory_size:
    pusha
    mov cx, word[number_entries]
    xor dx, dx
    xor eax, eax
    .free_memory_size:
        push dx
        mov bx, dx
        add bx, 16
        mov dl, byte[result+bx]
        cmp dl, 1
        jne .free_memory_size_preparation
        add bx, 4
        mov edx, dword[result+bx]
        add eax, edx
        .free_memory_size_preparation:
            pop dx
            add dx, 24
            dec cx
            cmp cx, 0
            jne .free_memory_size
    mov bx, FREE_MEMORY_SIZE_MESSAGE
    call print16

    cmp eax, 1024
    jl .print_kb
    xor edx, edx ; for correct divide
    mov ebx, 1024 ; get megabytes
    div ebx
    cmp eax, 1024
    jge .print_gigabytes
    call print_int_from_byte
    mov bx, MB_MESSAGE
    call print_with_new_line16
    jmp .exit
    .print_gigabytes:
        mov ebx, 1024
        xor edx, edx
        div ebx
        call print_int_from_byte
        mov bx, GB_MESSAGE
        call print_with_new_line16
        jmp .exit
    .print_kb:
        call print_int_from_byte
        mov bx, KB_MESSAGE
        call print_with_new_line16
        jmp .exit
    .exit:
        popa
        ret


DETECT_MEMORY_MESSAGE db "- - Detect memory - -", 0
SUCCESS_DETECT_LOW_MEMORY_MESSAGE db "Detect memory volume (Real Mode): ", 0
KB_MESSAGE db "KB", 0
MB_MESSAGE db "MB", 0
GB_MESSAGE db "GB", 0
DONT_SUPPORTED_DETECT_MEMORY_MESSAGE db "BIOS interrupt INT15h with parameter EAX=E820 don't supported", 0
ERROR_DETECT_MEMORY_MESSAGE db "Detect message error", 0
COUNT_ENTRIES_MESSAGE db "Getted entries memory map: ", 0
MEMORY_MAP_MESSAGE db "- - Memory Map - -", 0
MEMORY_MAP_HEADER db "Base address     | Length           | Type                | Volume", 0
SEPARATOR db ' | ', 0
FREE_MEMORY_MESSAGE db "Free Memory (1)    ", 0
RESERVED_MEMORY_MESSAGE db "Reserved Memory (2)", 0
FULL_SIZE_MEMORY_MESSAGE db "Full size memory: ", 0
FREE_MEMORY_SIZE_MESSAGE db "Free memory size: ", 0

section .bss
number_entries: resb 2
result: resb 168 ; for 7 records