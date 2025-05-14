#include "../types/types.h"
#include "../types/types.h"

#ifndef TEST_H
#define TEST_H

// buffers
volatile unsigned char test_buffer[256];
unsigned long test_longs_buffer[16];

// declarations
bool equal_unsigned_chars(volatile const unsigned char* first, volatile const unsigned char* second, unsigned char length);
bool equal_unsigned_longs(volatile unsigned long* first, unsigned long* second, unsigned char length);
bool equal_c_strings(volatile const unsigned char* first, const unsigned char* second);

// implementations
bool equal_unsigned_chars(volatile const unsigned char* first, volatile const unsigned char* second, unsigned char length){
    for (unsigned char i = 0; i < length; i++){
        if (first[i] != second[i]) return false;
    }
    return true;
}

bool equal_unsigned_longs(volatile unsigned long* first, unsigned long* second, unsigned char length){
    for (unsigned char i = 0; i < length; i++){
        if (first[i] != second[i]) return false;
    }
    return true;
}

bool equal_c_strings(volatile const unsigned char* first, const unsigned char* second){
    for (unsigned char i = 0; first[i] != '\0' || second[i] != '\0'; i++){
        if (first[i] != second[i]) return false;
    }
    return true;
}

bool test(){
    unsigned char counter = '1';
    bool flag = true;
    unsigned long temp_long;
    // tests
    {
        strcpy(test_buffer, "some_text");
        if (equal_c_strings(test_buffer, "some_text")){
            print_text_videomemory_with_color("strcpy - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("strcpy - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        c_variant_hex_from_byte(228, test_buffer);
        if (equal_c_strings(test_buffer, "E4")){
            print_text_videomemory_with_color("c_variant_hex_from_byte - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("c_variant_hex_from_byte - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        test_buffer[0] = 228;
        test_buffer[1] = 236;
        test_buffer[2] = '\0';
        hex_from_bytes_array(test_buffer, test_buffer + 3);
        if (equal_c_strings(test_buffer + 3, "E4EC")){
            print_text_videomemory_with_color("hex_from_bytes_array - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("hex_from_bytes_array - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        temp_long = 170;
        hex_from_extended_register(temp_long, test_buffer);
        if (equal_c_strings(test_buffer, "000000AA")){
            print_text_videomemory_with_color("hex_from_extended_register - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("hex_from_extended_register - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        test_longs_buffer[0] = 170;
        test_longs_buffer[1] = 189;
        test_longs_buffer[2] = 111;
        hex_from_array_extended_registers(test_longs_buffer, test_buffer, 3);
        if (equal_c_strings(test_buffer, "000000AA000000BD0000006F")){
            print_text_videomemory_with_color("hex_from_array_extended_registers - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("hex_from_array_extended_registers - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        test_longs_buffer[0] = 170000;
        test_longs_buffer[1] = 187839;
        test_longs_buffer[2] = 114741;
        test_buffer[20] = 0;
        test_buffer[21] = 2;
        test_buffer[22] = 152;
        test_buffer[23] = 16;
        test_buffer[24] = 0;
        test_buffer[25] = 2;
        test_buffer[26] = 221;
        test_buffer[27] = 191;
        test_buffer[28] = 0;
        test_buffer[29] = 1;
        test_buffer[30] = 192;
        test_buffer[31] = 53;
        copy_from_array_extended_registers(test_longs_buffer, test_buffer, 3);
        if (equal_unsigned_chars(test_buffer, test_buffer + 20, 3)){
            print_text_videomemory_with_color("copy_from_array_extended_registers - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("copy_from_array_extended_registers - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        test_longs_buffer[0] = 0x00000000;
        test_longs_buffer[1] = 0x68747541;
        test_longs_buffer[2] = 0x69746e65;
        test_longs_buffer[3] = 0x444d4163;
        convert_array_extended_registers_to_string_about_proccessor(test_longs_buffer, test_buffer);
        if (equal_c_strings(test_buffer, "AuthenticAMD")){
            print_text_videomemory_with_color("convert_array_extended_registers_to_string_about_proccessor - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("convert_array_extended_registers_to_string_about_proccessor - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        test_longs_buffer[0] = 170;
        test_longs_buffer[1] = 189;
        test_longs_buffer[2] = 111;
        hex_from_array_extended_registers_with_separator(test_longs_buffer, test_buffer, 3, ':');
        if (equal_c_strings(test_buffer, "000000AA:000000BD:0000006F")){
            print_text_videomemory_with_color("hex_from_array_extended_registers_with_separator - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("hex_from_array_extended_registers_with_separator - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }

    {
        temp_long = 663;
        bits_with_indexes_from_extended_register(663, test_buffer, ZERO_FORMAT);
        strcpy(test_buffer + 100, "00000000000000000000001010010111\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n76543210765432107654321076543210");
        if (equal_unsigned_chars(test_buffer, test_buffer + 100, 99)){
            print_text_videomemory_with_color("bits_with_indexes_from_extended_register - ", false, 0x02);
            print_text_videomemory_with_color("OK", true, 0x02);
        } else {
            print_text_videomemory_with_color("bits_with_indexes_from_extended_register - ", false, 0x04);
            print_text_videomemory_with_color("FAIL", true, 0x04);
            flag = false;
        }
    }
    return flag;
}

#endif