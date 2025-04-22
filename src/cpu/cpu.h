#ifndef CPU_H
#define CPU_H
#include "../kernel/headers/kernel_handler.h"

// declarations
static inline void cli();
static inline void sli();

void cpuid(unsigned long code, unsigned long* buffer);
unsigned long read_cr0();

// realizations
static inline void cli(){
    asm("cli");
}

static inline void sli(){
    asm("sti");
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
    asm volatile(
        "cpuid" 
        : "=a"(*buffer), "=b"(*(buffer+1)), "=d"(*(buffer+2)), "=c"(*(buffer + 3)) 
        : "a"(code)
    );
}

unsigned long read_cr0(){
    unsigned long value;
    asm volatile("mov %0, %%cr0" : "=r"(value));
    return value;
}

#endif