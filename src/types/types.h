#ifndef TYPES_H
#define TYPES_H

// custom types
typedef enum { false, true } bool;

// declarations
void strcpy(volatile const unsigned char* src, volatile unsigned char* dst);
void c_variant_hex_from_byte(unsigned char byte, volatile unsigned char* buffer);


// realizations
void strcpy(volatile const unsigned char* src, volatile unsigned char* dst){
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

#endif