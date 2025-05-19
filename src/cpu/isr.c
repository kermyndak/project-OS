#include "isr.h"
#include "../types/types.h"

void isr_install(){
    // set exceptions
    set_idt(0, (unsigned long)isr0);
    set_idt(1, (unsigned long)isr1);
    set_idt(2, (unsigned long)isr2);
    set_idt(3, (unsigned long)isr3);
    set_idt(4, (unsigned long)isr4);
    set_idt(5, (unsigned long)isr5);
    set_idt(6, (unsigned long)isr6);
    set_idt(7, (unsigned long)isr7);
    set_idt(8, (unsigned long)isr8);
    set_idt(9, (unsigned long)isr9);
    set_idt(10, (unsigned long)isr10);
    set_idt(11, (unsigned long)isr11);
    set_idt(12, (unsigned long)isr12);
    set_idt(13, (unsigned long)isr13);
    set_idt(14, (unsigned long)isr14);
    set_idt(15, (unsigned long)isr15);
    set_idt(16, (unsigned long)isr16);
    set_idt(17, (unsigned long)isr17);
    set_idt(18, (unsigned long)isr18);
    set_idt(19, (unsigned long)isr19);
    set_idt(20, (unsigned long)isr20);
    set_idt(21, (unsigned long)isr21);
    set_idt(22, (unsigned long)isr22);
    set_idt(23, (unsigned long)isr23);
    set_idt(24, (unsigned long)isr24);
    set_idt(25, (unsigned long)isr25);
    set_idt(26, (unsigned long)isr26);
    set_idt(27, (unsigned long)isr27);
    set_idt(28, (unsigned long)isr28);
    set_idt(29, (unsigned long)isr29);
    set_idt(30, (unsigned long)isr30);
    set_idt(31, (unsigned long)isr31);

    // set IRQ's
    set_idt(32, (unsigned long)irq0);
    set_idt(33, (unsigned long)irq1);
    set_idt(34, (unsigned long)irq2);
    set_idt(35, (unsigned long)irq3);
    set_idt(36, (unsigned long)irq4);
    set_idt(37, (unsigned long)irq5);
    set_idt(38, (unsigned long)irq6);
    set_idt(39, (unsigned long)irq7);
    set_idt(40, (unsigned long)irq8);
    set_idt(41, (unsigned long)irq9);
    set_idt(42, (unsigned long)irq10);
    set_idt(43, (unsigned long)irq11);
    set_idt(44, (unsigned long)irq12);
    set_idt(45, (unsigned long)irq13);
    set_idt(46, (unsigned long)irq14);
    set_idt(47, (unsigned long)irq15);
}

void c_isr_handler(struct ISR_stack_values stack_value){
    print_text_videomemory("isr called", false);
}

void c_irq_handler(struct ISR_stack_values stack_value){
    print_text_videomemory("irq called", false);
}