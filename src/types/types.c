#include "types.h"

// realizations
void strcpy(volatile unsigned char* dst, volatile unsigned const char* src){
	while (*dst++ = *src++);
	return;
}

void c_variant_hex_from_byte(unsigned char byte, volatile unsigned char* buffer){
	unsigned char temp = byte / 16;
	if (temp > 9) *buffer++ = temp + 55;
	else *buffer++ = temp + 48;
	temp = byte % 16;
	if (temp > 9) *buffer++ = temp + 55;
	else *buffer++ = temp + 48;
	*buffer = '\0';
	return;
}

void hex_from_bytes_array(volatile unsigned char* bytes, volatile unsigned char* buffer){ // must be with \0
	unsigned char temp;
	for (unsigned char i = 0; bytes[i] != '\0'; i++){
		temp = bytes[i] / 16;
		if (temp > 9) *buffer++ = temp + 55; // 55 = 'A'
		else *buffer++ = temp + 48; // 48 = '0'
		temp = bytes[i] % 16;
		if (temp > 9) *buffer++ = temp + 55;
		else *buffer++ = temp + 48;
	}
	*buffer = '\0';
	return;
}

static inline void hex_from_byte_inline(unsigned char byte, volatile unsigned char* buffer){
	unsigned char temp = byte / 16;
	if (temp > 9) *buffer++ = temp + 55;
	else *buffer++ = temp + 48;
	temp = byte % 16;
	if (temp > 9) *buffer++ = temp + 55;
	else *buffer++ = temp + 48;
	//*buffer = '\0';
}

void hex_from_extended_register(unsigned long reg, volatile unsigned char* buffer){
	unsigned char temp;
	temp = reg / 16777216;
	hex_from_byte_inline(temp, buffer);
	temp = (reg / 65536) % 256;
	hex_from_byte_inline(temp, buffer + 2);
	temp = (reg / 256) % 256;
	hex_from_byte_inline(temp, buffer + 4);
	temp = reg % 256;
	hex_from_byte_inline(temp, buffer + 6);
	buffer[8] = '\0';
	return;
}

void hex_from_array_extended_registers(unsigned long *reg_array, volatile unsigned char* buffer, unsigned char length){
	unsigned char temp, additional_index;
	for (unsigned char i = 0; i < length; i++){
		additional_index = 8 * i;
		temp = reg_array[i] / 16777216;
		hex_from_byte_inline(temp, buffer + additional_index);
		temp = (reg_array[i] / 65536) % 256;
		hex_from_byte_inline(temp, buffer + 2 + additional_index);
		temp = (reg_array[i] / 256) % 256;
		hex_from_byte_inline(temp, buffer + 4 + additional_index);
		temp = reg_array[i] % 256;
		hex_from_byte_inline(temp, buffer + 6 + additional_index);
	}
	buffer[8 + additional_index] = '\0';
	return;
}

void copy_from_array_extended_registers(unsigned long *reg_array, volatile unsigned char* buffer, unsigned char length){
	unsigned char temp, additional_index;
	for (unsigned char i = 0; i < length; i++){
		additional_index = 4 * i;
		temp = reg_array[i] / 16777216;
		buffer[additional_index++] = temp;
		temp = (reg_array[i] / 65536) % 256;
		buffer[additional_index++] = temp;
		temp = (reg_array[i] / 256) % 256;
		buffer[additional_index++] = temp;
		temp = reg_array[i] % 256;
		buffer[additional_index] = temp;
	}
	buffer[++additional_index] = '\0';
	return;
}

void convert_array_extended_registers_to_string_about_proccessor(unsigned long *reg_array, volatile unsigned char* buffer){
	unsigned char temp, additional_index;
	reg_array++; // Ignore eax
	for (unsigned char i = 0; i < 4; i++){
		additional_index = 4 * i;
		temp = reg_array[i] % 256;
		buffer[additional_index++] = temp;
		temp = (reg_array[i] / 256) % 256;
		buffer[additional_index++] = temp;
		temp = (reg_array[i] / 65536) % 256;
		buffer[additional_index++] = temp;
		temp = reg_array[i] / 16777216;
		buffer[additional_index] = temp;
	}
	buffer[++additional_index] = '\0';
	return;
}

void hex_from_array_extended_registers_with_separator(
	unsigned long *reg_array, 
	volatile unsigned char* buffer, 
	unsigned char length, 
	unsigned char separator
){
	unsigned char temp, additional_index;
	for (unsigned char i = 0; i < length; i++){
		additional_index = 9 * i;
		temp = reg_array[i] / 16777216;
		hex_from_byte_inline(temp, buffer + additional_index);
		temp = (reg_array[i] / 65536) % 256;
		hex_from_byte_inline(temp, buffer + 2 + additional_index);
		temp = (reg_array[i] / 256) % 256;
		hex_from_byte_inline(temp, buffer + 4 + additional_index);
		temp = reg_array[i] % 256;
		hex_from_byte_inline(temp, buffer + 6 + additional_index);
		buffer[8 + additional_index] = separator;
	}
	buffer[8 + additional_index] = '\0';
	return;
}

static inline void bits_from_byte_inline(unsigned char byte, volatile unsigned char* buffer){
	for (char i = 7, j = 0; i >= 0; i--, j++){ // can't 'unsigned char'
		if ((1 << i) & byte){
			buffer[j] = '1';
		} else buffer[j] = '0';
	}
}

void bits_with_indexes_from_extended_register(unsigned long reg, volatile unsigned char* buffer, begin_format format){
	unsigned char temp;
	temp = reg / 16777216;
	bits_from_byte_inline(temp, buffer);
	temp = (reg / 65536) % 256;
	bits_from_byte_inline(temp, buffer + 8);
	temp = (reg / 256) % 256;
	bits_from_byte_inline(temp, buffer + 16);
	temp = reg % 256;
	bits_from_byte_inline(temp, buffer + 24);
	strcpy(buffer + 32, "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	if (format == ZERO_FORMAT){
		strcpy(buffer + 66, "76543210765432107654321076543210");
	} else if(format == ONE_FORMAT){
		strcpy(buffer + 66, "87654321876543218765432187654321");
	} else {
		strcpy(buffer, "Error, bad format...");
	}
	return;
}

unsigned short get_low_address(unsigned long full_address){
	return full_address & 0xFFFF;
}

unsigned short get_high_address(unsigned long full_address){
	return (full_address >> 16) & 0xFFFF;
}