#ifndef IDT_H
#define IDT_H

#define CODE_SEGMENT 0x08
#define IDT_LENGTH 256

struct InterruptDescriptor{
    unsigned short low_offset;      // offset bits 0..15
    unsigned short selector;        // a code segment selector in GDT or LDT
    unsigned char  zero;            // unused, set to 0
    unsigned char  type_attributes; // gate type, dpl, and p fields
    unsigned short high_offset;     // offset bits 16..31
};

struct InterruptDescriptorRegisterDescription{
    unsigned short limit;
    unsigned long base;
} IDTR;

struct IRQ_stack_values{ // And DS, for example see isr_handler in interrupts.asm
    unsigned long DS;
    unsigned long EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX; // from pusha
    unsigned long IRQ_number, IRQ_error_code; // from irq or isr point
    unsigned long EIP, CS, EFLAGS, useresp, SS; // from IRQ call
};

struct InterruptDescriptor IDT[IDT_LENGTH];

void set_idt(unsigned char descriptor_index, unsigned long irq_handler);
void load_idt();

#endif