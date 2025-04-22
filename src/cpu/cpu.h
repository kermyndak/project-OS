#ifndef CPU_H
#define CPU_H
#include "../kernel/headers/kernel_handler.h"

// declarations
static inline void cli();
static inline void sli();

void cpuid(unsigned long int * answer);

// realizations
static inline void cli(){
    asm("cli");
}

static inline void sli(){
    asm("sti");
}

void cpuid(unsigned long int * answer){
    unsigned long int *a, *b, *c;
    unsigned long int inp = 0;
    //asm volatile("cpuid" : "=a" (*a), "=d" (*b), "=c" (*c) : "0" (inp) : "ebx", "ecx", "ebx");
    answer = a;
}

unsigned long read_cr0(){
    unsigned long value;
    asm volatile("mov %0, %%cr0" : "=rm"(value));
    return value;
}

#endif