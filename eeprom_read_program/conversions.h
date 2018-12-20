//
// Created by Klemens Rameder on 2018-12-13.
//

#ifndef EEPROM_READ_PROGRAM_CONVERSIONS_H
#define EEPROM_READ_PROGRAM_CONVERSIONS_H

#include <ntsid.h>

//Funktionen um hex stellen in binaer umzuwandeln und high und low bytes zu vertauschen
u_int8_t hex_to_binaer(char char_high, char char_low);
u_int16_t two_byte_combining_swap(u_int8_t byte_high, u_int8_t byte_low);
u_int32_t four_byte_combining_swap(u_int8_t byte_hh,u_int8_t byte_h,u_int8_t byte_l,u_int8_t byte_ll);

//Funktionen um aus HEX File Daten zu lesen mit angabe der Startposition und in Binaer umzuwandeln
/*
u_int8_t
u_int16_t
u_int32_t
*/

#endif //EEPROM_READ_PROGRAM_CONVERSIONS_H

