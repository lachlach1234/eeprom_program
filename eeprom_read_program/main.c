

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "file_read.h"

#define STATUS_START_POSITION 9
#define _2_5v_VOLT_MEASUREMENT_START_POSITION 11
#define _4v_VOLT_MEASUREMENT_START_POISTION 15
#define ADC_SLOPE_ERROR_START_POSITION 19
#define ADC_OFFSET_ERROR_START_POSITION 23
#define ADC_OFFSET_ERROR_TEMP_START_POSITION 31

#define VOLTAGE_CALCULATION 1.1/1024*4.3
#define TEMPERATURE_CALCULATION 1.1/1024*77.5757588-23
#define ADC_VALUE_FOR_23C 276

#define ADC_SLOPE_ERROR_LOWER_BORDER 1
#define ADC_SLOPE_ERROR_UPPER_BORDER 1
#define ADC_OFFSET_ERROR_LOWER_BORDER 1
#define ADC_OFFSET_ERROR_UPPER_BORDER 1
#define ADC_OFFSET_ERROR_TEMP_LOWER_BORDER 1
#define ADC_OFFSET_ERROR_TEMP_UPPER_BORDER 1

int main() {

    FILE *eeprom_datei;
    char pfad[500];

    printf("Bitte geben Sie den Pfad für die EEPROM Datei ein!");
    gets(pfad);
    //fflush(stdin);
    //scanf("%100s",&pfad[0]);

    eeprom_datei=fopen(pfad,"r+");
    if (eeprom_datei==NULL)
    {
        printf("Datei kann nicht geöffnet werden!");
    }
    else
    {
        printf("öffen hat funktioniert\n\n");
    }

    printf("Folgende Werte wurden aus der EEPROM Datei gelesen:\n");

    u_int8_t status_byte;
    u_int16_t adc_measurement_2_5v,adc_measurement_4v,adc_slope_error,adc_offset_temp_error,adc_slope_error_input,adc_offset_temp_error_input;
    u_int32_t adc_offset_error,adc_offset_error_input;
    int check_borders=0,x=0;
    char user_input[3];

    status_byte=read_byte_and_convert(eeprom_datei,STATUS_START_POSITION);
    adc_measurement_2_5v=read_two_byte_and_convert(eeprom_datei,_2_5v_VOLT_MEASUREMENT_START_POSITION);
    adc_measurement_4v=read_two_byte_and_convert(eeprom_datei,_4v_VOLT_MEASUREMENT_START_POISTION);
    adc_slope_error=read_two_byte_and_convert(eeprom_datei,ADC_SLOPE_ERROR_START_POSITION);
    adc_offset_error=read_two_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_START_POSITION);
    adc_offset_temp_error=read_two_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_TEMP_START_POSITION);

    printf("StatusByte: %d (%x)\n",status_byte,status_byte);
    printf("2,5v value: %.2fV (%d)\n",adc_measurement_2_5v*VOLTAGE_CALCULATION,adc_measurement_2_5v);
    printf("4v value: %.2fV (%d)\n",adc_measurement_4v*VOLTAGE_CALCULATION,adc_measurement_4v);
    printf("ADC slope error %d yV\n",adc_slope_error);
    printf("ADC offset error %zu\n",adc_offset_error);
    printf("ADC offset error %2.f°C (%d)\n",adc_offset_temp_error*TEMPERATURE_CALCULATION,adc_offset_temp_error-ADC_VALUE_FOR_23C);

    /*
    if(!(ADC_SLOPE_ERROR_LOWER_BORDER<adc_slope_error<ADC_SLOPE_ERROR_UPPER_BORDER)
    {
        printf("Der adc slope error befindet sich außerhalb der Grenzen!");
        check_borders=1;
    }
    if(!(ADC_OFFSET_ERROR_LOWER_BORDER<adc_offset_error<ADC_OFFSET_ERROR_UPPER_BORDER))
    {
        printf("Der adc offset error befindet sich außerhalb der Grenzen!");
        check_borders=1;
    }
    if(!(ADC_OFFSET_ERROR_TEMP_LOWER_BORDER<adc_offset_error<ADC_OFFSET_ERROR_TEMP_UPPER_BORDER))
    {
        printf("Der adc offset temp error befindet sich außerhalb der Grenzen!");
        check=1;
    }
    if(!check_borders==1)
    {
        printf("Die Werte dürften alle in Ordnung sein!");
    }
    */
    /*
    printf("\nWollen Sie irgendwelche Korekturen vornehmen?\nSchreiben Sie JA oder NEIN\n");

    do {
        fflush(stdin);
        scanf("%s",&user_input[0]);
        if (!strcmp(user_input, "JA"))
        {
            printf("Sie können jetzt die von Ihnen gewünschten Werte eingeben");
            x=1;
        }
        else if (!strcmp(user_input, "NEIN"))
        {
            x=1;
        }
        else
        {
            printf("Ungültige Eingabe!");
        }
    }while (x==0);
     */

    char a[2] = {'1','4'};
    write_file(eeprom_datei,100,2,a);

    int  num = 255;
    char hex[5];

    sprintf(hex, "%x", num);
    puts(hex);

    fclose(eeprom_datei);

    return 0;
}