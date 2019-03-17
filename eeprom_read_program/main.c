

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
#define CHECK_SUM_START_POSITION 73 //41 für .eep 73 für .hex

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

    //------------------Einlesen und Öffnen vom File---------------------

    FILE *eeprom_datei;
    char pfad[500]= {0};
    bool check=false;

    printf("Bitte geben Sie den Pfad für die EEPROM Datei ein!");
    do {
        gets(pfad);

        /*int i=1;

        do{

        }while(i==0);*/

        eeprom_datei = fopen(pfad, "r+");
        if (eeprom_datei == NULL) {
            printf("Datei kann nicht geöffnet werden!");
        } else {
            printf("öffen hat funktioniert\n\n");
            check=true;
        }
    }while(check==false);

    int border_for_cheksum,checksum_start_position;
    bool check1=false;
    char input;
    printf("Geben Sie an ob es sich um eine .epp(1) oder .hex(2) Datei handelt");
    do {
        fflush(stdin);
        //gets(input);
        scanf("%c", &input);
        if (input == '1')
        {
            check1=1;
            border_for_cheksum=20;
            checksum_start_position=41;

        }
        else if (input == '2')
        {
            check1=1;
            border_for_cheksum=36;
            checksum_start_position=73;

        } else
        {
            printf("Ungültige Eingabe!");
        }
    }while(check1==0);

    //-------------------------------------------------------------------
    //-------------Auslesen des Fikes und Anzeigen der Werte-------------

    u_int8_t status_byte;
    u_int16_t adc_measurement_2_5v,adc_measurement_4v,adc_slope_error,adc_offset_temp_error,adc_slope_error_input,adc_offset_temp_error_input=0;
    u_int32_t adc_offset_error,adc_offset_error_input;
    bool check_borders_violation=false,cd1=false,cd2=false,cd3=false,cd4=false;
    char user_input[3];
    int input_temp_error;

    status_byte=read_byte_and_convert(eeprom_datei,STATUS_START_POSITION);
    adc_measurement_2_5v=read_two_byte_and_convert(eeprom_datei,_2_5v_VOLT_MEASUREMENT_START_POSITION);
    adc_measurement_4v=read_two_byte_and_convert(eeprom_datei,_4v_VOLT_MEASUREMENT_START_POISTION);
    adc_slope_error=read_two_byte_and_convert(eeprom_datei,ADC_SLOPE_ERROR_START_POSITION);
    adc_offset_error=read_two_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_START_POSITION);
    adc_offset_temp_error=read_two_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_TEMP_START_POSITION);

    printf("\nFolgende Werte wurden aus der EEPROM Datei gelesen:\n");
    printf("StatusByte: %d (%x)\n",status_byte,status_byte);
    printf("2,5v value: %.2fV (%d)\n",adc_measurement_2_5v*VOLTAGE_CALCULATION,adc_measurement_2_5v);
    printf("4v value: %.2fV (%d)\n",adc_measurement_4v*VOLTAGE_CALCULATION,adc_measurement_4v);
    printf("ADC slope error %dyV = %dmV\n",adc_slope_error,adc_slope_error/1000);
    printf("ADC offset error %dyV\n",adc_offset_error);
    printf("ADC offset temp error %.1f°C (%d)\n",adc_offset_temp_error*TEMPERATURE_CALCULATION,adc_offset_temp_error-ADC_VALUE_FOR_23C);

    //-------------------------------------------------------------------
    //------Bestimmen ob die Werte in definierten Bereichen liegen-------

    if(!(ADC_SLOPE_ERROR_LOWER_BORDER<adc_slope_error && adc_slope_error<ADC_SLOPE_ERROR_UPPER_BORDER))
    {
        printf("Der adc slope error befindet sich außerhalb der Grenzen!\n");
        check_borders_violation=true;
    }
    if(!(ADC_OFFSET_ERROR_LOWER_BORDER<adc_offset_error && adc_offset_error<ADC_OFFSET_ERROR_UPPER_BORDER))
    {
        printf("Der adc offset error befindet sich außerhalb der Grenzen!\n");
        check_borders_violation=true;
    }
    if(!(ADC_OFFSET_ERROR_TEMP_LOWER_BORDER<adc_offset_temp_error && adc_offset_temp_error<ADC_OFFSET_ERROR_TEMP_UPPER_BORDER))
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
    //char adc_slope_error_input_hex[3];e

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
                } else if (!(ADC_SLOPE_ERROR_LOWER_BORDER<adc_slope_error_input && adc_slope_error_input<ADC_SLOPE_ERROR_UPPER_BORDER))
                {
                    printf("Eingabe befindet sich außerhalb der Grenzen!");
                } else
                {
                    char adc_slope_error_input_hex[5];
                    sprintf(adc_slope_error_input_hex, "%X", adc_slope_error_input);
                    char adc_slope_error_input_hex_help[5];
                    strcpy(adc_slope_error_input_hex_help,adc_slope_error_input_hex);

                    if(adc_slope_error_input >= 256 && adc_slope_error_input <= 4095)
                    {
                        adc_slope_error_input_hex[3]=adc_slope_error_input_hex_help[0];
                        adc_slope_error_input_hex[2]=48;
                        adc_slope_error_input_hex[1]=adc_slope_error_input_hex_help[2];
                        adc_slope_error_input_hex[0]=adc_slope_error_input_hex_help[1];
                    }else if(adc_slope_error_input >= 4096)
                    {
                        adc_slope_error_input_hex[3]=adc_slope_error_input_hex_help[1];
                        adc_slope_error_input_hex[2]=adc_slope_error_input_hex_help[0];
                        adc_slope_error_input_hex[1]=adc_slope_error_input_hex_help[3];
                        adc_slope_error_input_hex[0]=adc_slope_error_input_hex_help[2];
                    }
                    else
                    {
                        adc_slope_error_input_hex[3]=48;
                        adc_slope_error_input_hex[2]=48;
                    }
                    write_file(eeprom_datei,ADC_SLOPE_ERROR_START_POSITION,4,adc_slope_error_input_hex);
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
                } else if (!(ADC_OFFSET_ERROR_LOWER_BORDER<adc_offset_error_input && adc_offset_error_input<ADC_OFFSET_ERROR_UPPER_BORDER))
                {
                    printf("Eingabe befindet sich außerhalb der Grenzen!");
                } else
                {
                    char adc_offset_error_input_hex[5];
                    sprintf(adc_offset_error_input_hex, "%X", adc_offset_error_input);
                    char adc_offset_error_input_hex_help[5];
                    strcpy(adc_offset_error_input_hex_help,adc_offset_error_input_hex);

                    if(adc_offset_error_input >= 256)
                    {
                        adc_offset_error_input_hex[3]=adc_offset_error_input_hex_help[0];
                        adc_offset_error_input_hex[2]='0';
                        adc_offset_error_input_hex[1]=adc_offset_error_input_hex_help[2];
                        adc_offset_error_input_hex[0]=adc_offset_error_input_hex_help[1];
                    }
                    else
                    {
                        adc_offset_error_input_hex[3]='0';
                        adc_offset_error_input_hex[2]='0';
                    }

                    write_file(eeprom_datei,ADC_OFFSET_ERROR_START_POSITION,4,adc_offset_error_input_hex);
                    cd3=true;
                }
            }while (cd3==false);
            printf("adc offset temp error (in °C)");
            do {
                fflush(stdin);
                scanf("%d",&input_temp_error);
                if (input_temp_error==0)
                {
                    cd4=true;
                } else if (!(ADC_OFFSET_ERROR_TEMP_LOWER_BORDER<input_temp_error && input_temp_error<ADC_OFFSET_ERROR_TEMP_UPPER_BORDER))
                {
                    printf("Eingabe befindet sich außerhalb der Grenzen!");
                } else
                {
                    adc_offset_temp_error_input = (input_temp_error+23)/77.57588/(1.1/1024);
                    char adc_offset_temp_error_input_hex[5];
                    sprintf(adc_offset_temp_error_input_hex, "%X", adc_offset_temp_error_input);
                    char adc_offset_temp_error_input_hex_help[5];
                    strcpy(adc_offset_temp_error_input_hex_help,adc_offset_temp_error_input_hex);

                    if(adc_offset_temp_error_input >= 256)
                    {
                        adc_offset_temp_error_input_hex[3]=adc_offset_temp_error_input_hex_help[0];
                        adc_offset_temp_error_input_hex[2]='0';
                        adc_offset_temp_error_input_hex[1]=adc_offset_temp_error_input_hex_help[2];
                        adc_offset_temp_error_input_hex[0]=adc_offset_temp_error_input_hex_help[1];
                    }
                    else
                    {
                        adc_offset_temp_error_input_hex[3]='0';
                        adc_offset_temp_error_input_hex[2]='0';
                    }

                    write_file(eeprom_datei,ADC_OFFSET_ERROR_TEMP_START_POSITION,4,adc_offset_temp_error_input_hex);
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


    for (i=0; i<border_for_cheksum; i++) //20 für .eep    36 für .hex
    {
        read=read_byte_and_convert(eeprom_datei, position);
        data_sum = data_sum + read;
        position += 2;
    }

    checksum = data_sum&0x00ff;
    checksum = 0xff-checksum;
    checksum++;
    sprintf(checksum_hex, "%X", checksum);

    if(checksum >= 16)
    {
        printf("Checksumme: 0x%X",checksum);
        write_file(eeprom_datei,checksum_start_position,2,checksum_hex); //41 für .eep
    }
    else
    {
        char a[] = {48};
        printf("Checksumme: 0x0%X",checksum);
        write_file(eeprom_datei,checksum_start_position,1,a);
        write_file(eeprom_datei,checksum_start_position+1,1,checksum_hex);
    }

    //-------------------------------------------------------------------

    fclose(eeprom_datei);

    return 0;
}

