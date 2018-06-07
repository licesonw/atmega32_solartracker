#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uartlib.h"
#include "adclib.h"

int main (void)
{
    ADC_Init();
    USART_Init();
    uint8_t adc_val;
    unsigned char str_adc_val[4];
    
    while(1)
    {
        adc_val = ADC_ReadChannel0();
        itoa(adc_val, str_adc_val, 10);
        str_adc_val[3] = '\0';
        USART_TransmitString((uint8_t*)"Current adc val: \0");
        USART_TransmitString(str_adc_val);
        USART_Transmit('\n');
        _delay_ms(50);
    }
    
    
    
    return 0;
}
