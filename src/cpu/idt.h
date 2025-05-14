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
} __attribute__((packed));

struct InterruptDescriptorRegisterDescription{
    unsigned short limit;
    unsigned long base;
} __attribute__((packed)) IDTR;

struct InterruptDescriptor IDT[IDT_LENGTH];

void set_idt(unsigned char descriptor_index, unsigned long irq_handler);
void load_idt();

void set_idt(unsigned char descriptor_index, unsigned long irq_handler){
    IDT[descriptor_index].low_offset = get_low_address(irq_handler);
    IDT[descriptor_index].selector = CODE_SEGMENT;
    IDT[descriptor_index].zero = 0;
    IDT[descriptor_index].type_attributes = 0x8E; // '0b1000_1110' Present bit (1), DPL (privilege level - 00), 0, Interrupt Gate (0b1110)
    IDT[descriptor_index].high_offset = get_high_address(irq_handler);
}

void load_idt(){
    IDTR.base = (unsigned long)&IDT;
    IDTR.limit = IDT_LENGTH * sizeof(struct InterruptDescriptor) - 1;
    asm volatile(
        "lidtl (%[IDT])\n\t"
        "sti" : : [IDT] "r"(&IDT)
    );
}

#endif