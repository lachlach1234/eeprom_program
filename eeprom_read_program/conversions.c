//
// Created by Klemens Rameder on 2018-12-13.
//

#include "conversions.h"

u_int8_t hex_to_binaer(char char_high, char char_low)
{
    u_int8_t result=0;
    switch(char_low)
    {
        case '1':result |= 0b00000001; break;
        case '2':result |= 0b00000010; break;
        case '3':result |= 0b00000011; break;
        case '4':result |= 0b00000100; break;
        case '5':result |= 0b00000101; break;
        case '6':result |= 0b00000110; break;
        case '7':result |= 0b00000111; break;
        case '8':result |= 0b00001000; break;
        case '9':result |= 0b00001001; break;
        case 'A':result |= 0b00001010; break;
        case 'B':result |= 0b00001011; break;
        case 'C':result |= 0b00001100; break;
        case 'D':result |= 0b00001101; break;
        case 'E':result |= 0b00001110; break;
        case 'F':result |= 0b00001111; break;
    }

    switch(char_high)
    {
        case '1':result |= 0b00010000; break;
        case '2':result |= 0b00100000; break;
        case '3':result |= 0b00110000; break;
        case '4':result |= 0b01000000; break;
        case '5':result |= 0b01010000; break;
        case '6':result |= 0b01100000; break;
        case '7':result |= 0b01110000; break;
        case '8':result |= 0b10000000; break;
        case '9':result |= 0b10010000; break;
        case 'A':result |= 0b10100000; break;
        case 'B':result |= 0b10110000; break;
        case 'C':result |= 0b11000000; break;
        case 'D':result |= 0b11010000; break;
        case 'E':result |= 0b11100000; break;
        case 'F':result |= 0b11110000; break;
    }
    return result;
}

u_int16_t two_byte_combining_swap(u_int8_t byte_high, u_int8_t byte_low)
{
    u_int16_t result=0;
    result |= byte_low;
    result = (result<<8);
    result |= byte_high;
    return result;
}

u_int32_t four_byte_combining_swap(u_int8_t byte_hh,u_int8_t byte_h,u_int8_t byte_l,u_int8_t byte_ll)
{
    u_int16_t result_high, result_low;
    u_int32_t result=0;

    result_low = two_byte_combining_swap(byte_l,byte_ll);
    result_high = two_byte_combining_swap(byte_hh,byte_h);

    result |= result_low;
    result = (result<<16);
    result |= result_high;
    return result;
}

