#ifndef ISR_H
#define ISR_H

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

void isr_install(){
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
}

#endif