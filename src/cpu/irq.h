#ifndef IRQ_H
#define IRQ_H

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

void irq_install(){
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