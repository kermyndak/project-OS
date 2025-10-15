#ifndef CPU_H
#define CPU_H

// declarations
static inline void cli();
static inline void sli();

void cpuid(unsigned long code, unsigned long* buffer);
unsigned long read_cr0();
void port_byte_out(unsigned short port, unsigned char byte);
unsigned char port_byte_get(unsigned short port);
void port_word_out(unsigned short port, unsigned short word);
unsigned short port_word_get(unsigned short port);

// implementations
static inline void cli(){
    __asm__("cli");
}

static inline void sli(){
    __asm__("sti");
}

// Example
// asm volatile(
//         "mov %%eax, %[InputCode]\n\t"
//         "cpuid\n\t"
//         "mov %0, %%ebx\n\t"
//         "mov %1, %%edx\n\t"
//         "mov %2, %%ecx\n\t"
//         : "=rm"(*buffer), "=rm"(*(buffer + 1)), "=rm"(*(buffer + 2))
//         : [InputCode] "0"(code)
//         : "ebx", "ecx", "edx"
//     );
void cpuid(unsigned long code, unsigned long* buffer){
    __asm__ volatile(
        "cpuid" 
        : "=a"(*buffer), "=b"(*(buffer+1)), "=d"(*(buffer+2)), "=c"(*(buffer + 3)) 
        : "a"(code)
    );
}

unsigned long read_cr0(){
    unsigned long value;
    __asm__ volatile("mov %0, %%cr0" : "=r"(value));
    return value;
}

void port_byte_out(unsigned short port, unsigned char byte){
    __asm__ volatile("out %%al, %%dx" : : "a"(byte), "d"(port));
}

unsigned char port_byte_get(unsigned short port){
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

void port_word_out(unsigned short port, unsigned short word){
    __asm__ volatile("out %%ax, %%dx" : : "a"(word), "d"(port));
}

unsigned short port_word_get(unsigned short port){
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));
    return result;
}

#endif