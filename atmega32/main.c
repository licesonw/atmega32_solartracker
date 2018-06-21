#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lcdpcf8574.h"

#include "uartlib.h"
#include "adclib.h"
#include "servolib.h"

#define SERVO_UPPER_LIMIT 180
#define SERVO_LOWER_LIMIT 0
#define TOLERANCE 100

void IO_Init (void)
{
    // Set pullup resistors for LCD
    PORTC |= (1<<PC0)|(1<<PC1);
}

int main (void)
{
    IO_Init();
    ADC_Init();
    USART_Init();
    Servo0_Init();
    
    sei();
    
    uint16_t adc_val_up = 0;
    uint16_t adc_val_down = 0;
    int diff;
    
    char buf[10];
    
    int servo_deg = 0;
    
    
    while(1)
    {
        adc_val_up = ADC_ReadChannel(0);
        _delay_us(10);
        adc_val_down = ADC_ReadChannel(1);
        diff = adc_val_up - adc_val_down;

        if (- 1* TOLERANCE > diff || diff > TOLERANCE)
        {
            if(adc_val_up > adc_val_down)
            {
                servo_deg += 10;
                if(servo_deg > 180)
                    servo_deg = 180;
            }

            else if( adc_val_up < adc_val_down)
            {
                servo_deg -= 10;
                if(servo_deg < 0)
                    servo_deg = 0;
            }
            Servo0_AssumePosition(servo_deg);
        }

        itoa(adc_val_up, buf, 10);
        USART_TransmitString((uint8_t*)"LDR up: \0");
        USART_TransmitString((uint8_t*)buf);
        USART_TransmitString((uint8_t*)"\n\0");

        itoa(adc_val_down, buf, 10);
        USART_TransmitString((uint8_t*)"LDR down: \0");
        USART_TransmitString((uint8_t*)buf);
        USART_TransmitString((uint8_t*)"\n\0");


        itoa(servo_deg, buf, 10);
        USART_TransmitString((uint8_t*)"Servo angle: \0");
        USART_TransmitString((uint8_t*)buf);
        USART_TransmitString((uint8_t*)"\n\0");

        _delay_ms(5);
        
    }
    
    
    
    return 0;
}

