//
// Created by Klemens Rameder on 2018-12-13.
//

#ifndef EEPROM_READ_PROGRAM_FILE_READ_H
#define EEPROM_READ_PROGRAM_FILE_READ_H

#include <ntsid.h>
#include <stdio.h>

struct read_write_array
{
    u_int8_t array[8];
};

//Funktion um maximal acht digits aus einer Datei zu lesen mit angabe der start position
void read_file(FILE * , int start_position, int menge, struct read_write_array * read);

//Funktion um maximal acht digits in eine Datei zu  schreiben mit angabe der start position
void write_file(FILE *, int start_position, int menge,char []);

//Funktion um 1/2/4 byte aus HEX Datei zu lesen und zu binaer umzuwandeln
u_int8_t read_byte_and_convert(FILE * , int start_position);
u_int16_t read_two_byte_and_convert(FILE * , int start_position);
//u_int32_t read_four_byte_and_convert(FILE * , int start_position);

#endif //EEPROM_READ_PROGRAM_FILE_READ_H

