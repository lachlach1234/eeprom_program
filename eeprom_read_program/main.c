


#include <stdio.h>
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


int main() {

    FILE *eeprom_datei;
    char pfad[500];

    printf("Bitte geben Sie den Pfad für die EEPROM Datei ein!");
    gets(pfad);

    eeprom_datei=fopen(pfad,"r+w");
    //eeprom_datei=fopen("/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom/12.12.2018/read_after_2.5V_calibration.eep","r+");
    if (eeprom_datei==NULL)
    {
        printf("Datei kann nicht geöffnet werden!");
    }
    else
    {
        printf("öffen hat funktioniert\n");
    }

    printf("Folgende Werte wurden aus der EEPROM Datei gelesen:\n");

    u_int8_t status_byte;
    u_int16_t adc_measurement_2_5v,adc_measurement_4v,adc_slope_error,adc_offset_temp_error;
    u_int32_t adc_offset_error;

    status_byte=read_byte_and_convert(eeprom_datei,STATUS_START_POSITION);
    adc_measurement_2_5v=read_two_byte_and_convert(eeprom_datei,_2_5v_VOLT_MEASUREMENT_START_POSITION);
    adc_measurement_4v=read_two_byte_and_convert(eeprom_datei,_4v_VOLT_MEASUREMENT_START_POISTION);
    adc_slope_error=read_two_byte_and_convert(eeprom_datei,ADC_SLOPE_ERROR_START_POSITION);
    adc_offset_error=read_four_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_START_POSITION);
    adc_offset_temp_error=read_two_byte_and_convert(eeprom_datei,ADC_OFFSET_ERROR_TEMP_START_POSITION);

    printf("StatusByte: %d\n",status_byte);
    printf("2,5v value: %.2fV (%d)\n",adc_measurement_2_5v*VOLTAGE_CALCULATION,adc_measurement_2_5v);
    printf("4v value: %.2fV (%d)\n",adc_measurement_4v*VOLTAGE_CALCULATION,adc_measurement_4v);
    printf("ADC slope error %d yV\n",adc_slope_error);
    printf("ADC offset error %zu\n",adc_offset_error);
    printf("ADC offset error %2.f°C (%d)\n",adc_offset_temp_error*TEMPERATURE_CALCULATION,adc_offset_temp_error-ADC_VALUE_FOR_23C);



    fclose(eeprom_datei);


    return 0;
}