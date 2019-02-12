

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "conversions.h"
#include "file_read.h"
#include "string.h"

//Defines zum Auslesen und Schreiben
#define STATUS_START_POSITION 9
#define _2_5v_VOLT_MEASUREMENT_START_POSITION 11
#define _4v_VOLT_MEASUREMENT_START_POISTION 15
#define ADC_SLOPE_ERROR_START_POSITION 19
#define ADC_OFFSET_ERROR_START_POSITION 23
#define ADC_OFFSET_ERROR_TEMP_START_POSITION 31
#define CHECK_SUM_START_POSITION 73

//Macros fuer Berechnungen
#define VOLTAGE_CALCULATION 1.1/1024*4.3
#define TEMPERATURE_CALCULATION 1.1/1024*77.57588-23
#define ADC_VALUE_FOR_23C 276

//Defines für Grenzen
#define ADC_SLOPE_ERROR_LOWER_BORDER 0
#define ADC_SLOPE_ERROR_UPPER_BORDER 10000
#define ADC_OFFSET_ERROR_LOWER_BORDER 0
#define ADC_OFFSET_ERROR_UPPER_BORDER 10000
#define ADC_OFFSET_ERROR_TEMP_LOWER_BORDER 0
#define ADC_OFFSET_ERROR_TEMP_UPPER_BORDER 10000

int main() {

    FILE *eeprom_datei;
    char pfad[500];
    bool check=false;

    //------------------Einlesen und Öffnen vom File---------------------

    printf("Bitte geben Sie den Pfad für die EEPROM Datei ein!");
    do {
        gets(pfad);

        eeprom_datei = fopen(pfad, "r+");
        if (eeprom_datei == NULL) {
            printf("Datei kann nicht geöffnet werden!");
        } else {
            printf("öffen hat funktioniert\n\n");
            check=true;
        }
    }while(check==false);

    //-------------------------------------------------------------------
    //-------------Auslesen des Fikes und Anzeigen der Werte-------------

    u_int8_t status_byte;
    u_int16_t adc_measurement_2_5v,adc_measurement_4v,adc_slope_error,adc_offset_temp_error,adc_slope_error_input;//adc_offset_temp_error_input;
    u_int32_t adc_offset_error,adc_offset_error_input;
    bool check_borders_violation=false,cd1=false,cd2=false,cd3=false,cd4=false;
    char user_input[3];
    u_int16_t adc_offset_temp_error_input=0;

    status_byte=read_byte_and_convert(eeprom_datei,STATUS_START_POSITION);
    adc_measurement_2_5v=read_two_byte_and_convert(eeprom_datei,_2_5v_VOLT_MEASUREMENT_START_POSITION);
    adc_measurement_4v=read_two_byte_and_convert(eeprom_datei,_4v_VOLT_MEASUREMENT_START_POISTION);
    adc_slope_error=read_two_byte_and_convert(eeprom_datei,ADC_SLOPE_ERROR_START_POSITION);
    adc_offset_error=read_two_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_START_POSITION);
    adc_offset_temp_error=read_two_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_TEMP_START_POSITION);

    printf("Folgende Werte wurden aus der EEPROM Datei gelesen:\n");
    printf("StatusByte: %d (%x)\n",status_byte,status_byte);
    printf("2,5v value: %.2fV (%d)\n",adc_measurement_2_5v*VOLTAGE_CALCULATION,adc_measurement_2_5v);
    printf("4v value: %.2fV (%d)\n",adc_measurement_4v*VOLTAGE_CALCULATION,adc_measurement_4v);
    printf("ADC slope error %d yV\n",adc_slope_error);
    printf("ADC offset error %zu\n",adc_offset_error);
    printf("ADC offset error %.4f°C (%d)\n",adc_offset_temp_error*TEMPERATURE_CALCULATION,adc_offset_temp_error/*-ADC_VALUE_FOR_23C*/);

    //-------------------------------------------------------------------
    //------Bestimmen ob die Werte in definierten Bereichen liegen-------

    if(!(ADC_SLOPE_ERROR_LOWER_BORDER<adc_slope_error<ADC_SLOPE_ERROR_UPPER_BORDER))
    {
        printf("Der adc slope error befindet sich außerhalb der Grenzen!\n");
        check_borders_violation=true;
    }
    if(!(ADC_OFFSET_ERROR_LOWER_BORDER<adc_offset_error<ADC_OFFSET_ERROR_UPPER_BORDER))
    {
        printf("Der adc offset error befindet sich außerhalb der Grenzen!\n");
        check_borders_violation=true;
    }
    if(!(ADC_OFFSET_ERROR_TEMP_LOWER_BORDER<adc_offset_temp_error<ADC_OFFSET_ERROR_TEMP_UPPER_BORDER))
    {
        printf("Der adc offset temp error befindet sich außerhalb der Grenzen!\n");
        check_borders_violation=true;
    }
    if(!check_borders_violation==true)
    {
        printf("\nDie Werte dürften alle in Ordnung sein!");
    }

    //-------------------------------------------------------------------
    //------------------Verändern der Daten wenn erwünscht---------------

    printf("\n\nWollen Sie irgendwelche Korekturen vornehmen?\nSchreiben Sie y (für Ja) oder n (für Nein)\n");
    char adc_slope_error_input_hex[3];

    do {
        fflush(stdin);
        scanf("%s",&user_input[0]);
        if (!strcmp(user_input, "y"))
        {
            printf("Sie können jetzt die von Ihnen gewünschten Werte eingeben.\nWenn Sie den Wert nicht verändern wollen geben sie 0 ein!\n");
            printf("adc slope value (in INT): ");
            do {
                fflush(stdin);
                scanf("%d",&adc_slope_error_input);
                if (adc_slope_error_input==0)
                {
                    cd2=true;
                } else if (!(ADC_SLOPE_ERROR_LOWER_BORDER<adc_slope_error_input<ADC_SLOPE_ERROR_UPPER_BORDER))
                {
                    printf("Eingabe befindet sich außerhalb der Grenzen!");
                } else
                {
                    //char adc_slope_error_input_hex[3];
                    sprintf(adc_slope_error_input_hex, "%x", adc_slope_error_input);
                    write_file(eeprom_datei,ADC_SLOPE_ERROR_START_POSITION,2,adc_slope_error_input_hex);
                    cd2=true;
                }
            }while (cd2==false);
            printf("adc offset error (in INT): ");
            do {
                fflush(stdin);
                scanf("%d",&adc_offset_error_input);
                if (adc_offset_error_input==0)
                {
                    cd3=true;
                } else if (!(ADC_OFFSET_ERROR_LOWER_BORDER<adc_offset_error_input<ADC_OFFSET_ERROR_UPPER_BORDER))
                {
                    printf("Eingabe befindet sich außerhalb der Grenzen!");
                } else
                {
                    //Wert umwandeln und in File Speichern
                    cd3=true;
                }
            }while (cd3==false);
            printf("adc offset temp error (in °C)");
            do {
                fflush(stdin);
                scanf("%d",&adc_offset_temp_error_input);
                if (adc_offset_temp_error_input==0)
                {
                    cd4=true;
                } else if (!(ADC_OFFSET_ERROR_TEMP_LOWER_BORDER<adc_offset_temp_error_input<ADC_OFFSET_ERROR_TEMP_UPPER_BORDER))
                {
                    printf("Eingabe befindet sich außerhalb der Grenzen!");
                } else
                {
                    adc_offset_temp_error_input = (adc_offset_temp_error_input+23)/77.57588/(1.1/1024);
                    char adc_offset_temp_error_input_hex[5];
                    sprintf(adc_offset_temp_error_input_hex, "%x", adc_offset_temp_error_input);
                    char adc_offset_temp_error_input_hex_help[5];
                    strcpy(adc_offset_temp_error_input_hex_help,adc_offset_temp_error_input_hex);

                    adc_offset_temp_error_input_hex[3]=adc_offset_temp_error_input_hex_help[0];
                    adc_offset_temp_error_input_hex[2]=0;
                    adc_offset_temp_error_input_hex[1]=adc_offset_temp_error_input_hex_help[2];
                    adc_offset_temp_error_input_hex[0]=adc_offset_temp_error_input_hex_help[1];

                    write_file(eeprom_datei,ADC_OFFSET_ERROR_TEMP_START_POSITION,2,adc_offset_temp_error_input_hex);
                    cd4=true;
                }
            }while (cd4==false);
            cd1=1;
        }
        else if (!strcmp(user_input, "n"))
        {
            cd1=1;
        }
        else
        {
            printf("Ungültige Eingabe!");
        }
    }while (cd1==0);

    //-------------------------------------------------------------------
    //-------------Berechnung und Schreiben der Checksumme---------------

    u_int16_t checksum = 43;
    u_int16_t read_file;
    u_int8_t read;
    int i,data_sum=0,position=1;
    char checksum_hex[3];


    for (i=0; i<36; i++)
    {
        read=read_byte_and_convert(eeprom_datei, position);
        data_sum = data_sum + read;
        position += 2;
    }

    checksum = data_sum&0x00ff;
    checksum = 0xff-checksum;
    checksum++;

    printf("Checksumme: %x",checksum);

    sprintf(checksum_hex, "%x", checksum);
    write_file(eeprom_datei,CHECK_SUM_START_POSITION,2,checksum_hex);

    //-------------------------------------------------------------------

    fclose(eeprom_datei);

    return 0;
}

