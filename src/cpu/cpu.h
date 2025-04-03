#ifndef CPU_H
#define CPU_H

// declarations
static inline void cli();
static inline void sli();

// realizations
static inline void cli(){
    asm("cli");
}

static inline void sli(){
    asm("sti");
}

#endif