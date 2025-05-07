gdt_start:

null_descriptor:
    dd 0
    dd 0

code_descriptor: ; defines of code segment
    dw 0xffff ; define limit
    dw 0
    db 0 ; define base
    db 10011010
    db 11001111
    db 0

data_descriptor:
    dw 0xffff
    dw 0
    db 0
    db 10010010
    db 11001111
    db 0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ code_descriptor - gdt_start
DATA_SEG equ data_descriptor - gdt_start