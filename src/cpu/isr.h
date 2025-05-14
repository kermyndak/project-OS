#ifndef ISR_H
#define ISR_H

struct ISR_stack_values{ // And DS, for example see isr_handler in interrupts.asm
    unsigned long DS;
    unsigned long EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX; // from pusha
    unsigned long IRQ_number, IRQ_error_code; // from irq or isr point
    unsigned long EIP, CS, EFLAGS, useresp, SS; // from IRQ call
};

// Declarations extern functions
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// Declarations global functions
void c_isr_handler(struct ISR_stack_values stack_value);
void c_irq_handler(struct ISR_stack_values stack_value);

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

#endif