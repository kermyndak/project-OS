#include "idt.h"

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