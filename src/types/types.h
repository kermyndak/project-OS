#ifndef TYPES_H
#define TYPES_H

// custom types
typedef enum { false, true } bool;

// declarations
void strcpy(volatile unsigned char* dst, volatile unsigned const char* src);
void c_variant_hex_from_byte(unsigned char byte, volatile unsigned char* buffer);
void hex_from_bytes_array(volatile unsigned char* bytes, volatile unsigned char* buffer);
static inline void hex_from_byte_inline(unsigned char byte, volatile unsigned char* buffer);
void hex_from_extended_register(unsigned long reg, volatile unsigned char* buffer);

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

void hex_from_bytes_array(volatile unsigned char* bytes, volatile unsigned char* buffer){
	unsigned char temp;
	for (unsigned char i = 0; bytes[i] != '\0'; i++){
		temp = bytes[i] / 16;
		if (temp > 9) *buffer++ = temp + 55;
		else *buffer++ = temp + 48;
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
	*buffer = '\0';
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
}

#endif