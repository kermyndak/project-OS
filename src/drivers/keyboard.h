#ifndef KEYBOARD_H
#define KEYBOARD_H

void send_byte_keyboard(){
    asm("out x60, ");
}

unsigned char recieve_byte_keyboard(){
    
}

#endif