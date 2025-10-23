#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

void send_byte_keyboard(unsigned char byte);
unsigned char recieve_byte_keyboard();
unsigned short recieve_word_keyboard();
unsigned char recieve_status_keyboard();
void keyboard_init();
void keyboard_handler();

void send_byte_keyboard(unsigned char byte){
    __asm__ volatile("out %%al, %%dx" : : "a"(byte), "d"(KEYBOARD_DATA_PORT));
}

unsigned char recieve_byte_keyboard(){
    unsigned char result_byte;
    __asm__("in %%dx, %%al" : "=a"(result_byte) : "d"(KEYBOARD_DATA_PORT));
    return result_byte;
}

unsigned short recieve_word_keyboard(){
    unsigned short result_word;
    __asm__("in %%dx, %%ax" : "=a"(result_word) : "d"(KEYBOARD_DATA_PORT));
    return result_word;
}

unsigned char recieve_status_keyboard(){
    unsigned char status;
    __asm__("in %%dx, %%al" : "=a"(status) : "d"(KEYBOARD_STATUS_PORT));
    return status;
}

void keyboard_init(){
    __asm__ volatile("out %%al, %%dx" : : "a"(0x21), "d"(0xFD));
}

void keyboard_handler(){
    unsigned char status;
    // after remap PIC
}

#endif