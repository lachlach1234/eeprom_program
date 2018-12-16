//
// Created by Klemens Rameder on 2018-12-13.
//

#include "file_read.h"
#include "stdio.h"
#include "conversions.h"

void read_file(FILE * datei, int start_position, int menge, struct read_write_array *daten)
{
    int read_check,i;
    u_int8_t read;
    for (i=0; i<menge; i++)
    {
        fseek(datei,start_position+i, SEEK_SET);
        read_check =  fread (&read, 1, 1, datei);
        daten->array[i]=read;
    }
}

void write_file(FILE * datei, int start_position, int menge, struct read_write_array *daten)
{
    int write_check,i;
    for (i=0; i<menge; i++)
    {
        fseek(datei,start_position+i, SEEK_SET);
        write_check=fwrite(daten->array[i],1,1,datei);
    }
}

u_int8_t read_byte_and_convert(FILE * datei, int start_position)
{
    u_int8_t result;
    struct read_write_array read;

    read_file(datei,start_position,2,&read);
    result = hex_to_binaer(read.array[0],read.array[1]);
    return result;
}

u_int16_t read_two_byte_and_convert(FILE * datei, int start_position)
{
    u_int8_t binaer[2];
    u_int16_t result;
    struct read_write_array read;
    read_file(datei,start_position,4,&read);
    binaer[0]=hex_to_binaer(read.array[0],read.array[1]);
    binaer[1]=hex_to_binaer(read.array[2],read.array[3]);
    result=two_byte_combining_swap(binaer[0],binaer[1]);
    return result;

}

u_int32_t read_four_byte_and_convert(FILE * datei, int start_position)
{
    u_int8_t binaer[4];
    u_int32_t result;
    struct read_write_array read;
    read_file(datei,start_position,8,&read);
    binaer[0]=hex_to_binaer(read.array[0],read.array[1]);
    binaer[1]=hex_to_binaer(read.array[2],read.array[3]);
    binaer[2]=hex_to_binaer(read.array[4],read.array[5]);
    binaer[3]=hex_to_binaer(read.array[6],read.array[7]);
    result=four_byte_combining_swap(binaer[0],binaer[1],binaer[2],binaer[3]);
    return result;

}

