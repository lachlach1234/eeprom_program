cmake_minimum_required(VERSION 3.12)
project(eeprom_read_program C)

set(CMAKE_C_STANDARD 99)

add_executable(eeprom_read_program main.c conversions.c conversions.h file_read.c file_read.h)