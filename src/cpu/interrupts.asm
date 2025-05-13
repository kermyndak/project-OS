[bits 32]
section .text

; define macro for ISR
%macro isr_point 1
isr%1:
    cli
%if !(%1 == 4 || (%1 >= 10 && %1 <= 14) || %1 == 17 || %1 == 21 || %1 == 29 || %1 == 30)
    push byte 0
%endif
    push byte %1
    jmp isr_handler
%endmacro

; define macro for IRQ
%macro irq_point 1
irq%1:
    cli
    push byte 0
    push byte %1
    jmp irq_handler
%endmacro

; ISR's
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; IRQ's
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
global irq16

extern c_isr_handler
extern c_irq_handler

; define 32 ISR
%assign i 0
%rep 32
    isr_point i
%assign i i+1
%endrep

; define 16 IRQ
%assign i 0
%rep 16
    irq_point i
%assign i i+1
%endrep

isr_handler:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10 ; load data segment 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call c_isr_handler
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    sti
    iret


irq_handler:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call c_irq_handler
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    sti
    iret
