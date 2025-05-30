#ifndef TYPES_H
#define TYPES_H

// custom types
typedef enum { false, true } bool;
typedef enum { ZERO_FORMAT, ONE_FORMAT } begin_format; // for function 'bits_with_indexes_from_extended_register'

// declarations
void strcpy(volatile unsigned char* dst, volatile unsigned const char* src);
void c_variant_hex_from_byte(unsigned char byte, volatile unsigned char* buffer);
void hex_from_bytes_array(volatile unsigned char* bytes, volatile unsigned char* buffer);
static inline void hex_from_byte_inline(unsigned char byte, volatile unsigned char* buffer);
void hex_from_extended_register(unsigned long reg, volatile unsigned char* buffer);
void hex_from_array_extended_registers(unsigned long *reg_array, volatile unsigned char* buffer, unsigned char length);
void copy_from_array_extended_registers(unsigned long *reg_array, volatile unsigned char* buffer, unsigned char length);
void convert_array_extended_registers_to_string_about_proccessor(unsigned long *reg_array, volatile unsigned char* buffer);
void hex_from_array_extended_registers_with_separator(unsigned long *reg_array, volatile unsigned char* buffer, unsigned char length, unsigned char separator);
static inline void bits_from_byte_inline(unsigned char byte, volatile unsigned char* buffer);
void bits_with_indexes_from_extended_register(unsigned long reg, volatile unsigned char* buffer, begin_format format);
unsigned short get_low_address(unsigned long full_address);
unsigned short get_high_address(unsigned long full_address);
void uint_from_byte(unsigned char byte, volatile unsigned char* buffer);
void int_from_byte(char byte, volatile unsigned char* buffer);
void uint_from_word(unsigned short word, volatile unsigned char* buffer); // word - 2 bytes
void int_from_word(short word, volatile unsigned char* buffer);
void uint_from_dword(unsigned long dword, volatile unsigned char* buffer); // dword - 4 bytes
void int_from_dword(long dword, volatile unsigned char* buffer);
void shex_from_byte(char byte, volatile unsigned char* buffer); // for unsigned used 'c_variant_hex_from_byte'
void uhex_from_word(unsigned short word, volatile unsigned char* buffer);
void hex_from_word(short word, volatile unsigned char* buffer);
void hex_from_dword(long dword, volatile unsigned char* buffer); // for unsigned used 'hex_from_extended_register'

#endif