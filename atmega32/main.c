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


void IO_Init (void)
{
    // OC0 as output: PWM
    //DDRB |= (1<<PB3);
    // PC0 as output: LED
    //DDRC |= (1<<PC0);
}

int main (void)
{
    IO_Init();
    ADC_Init();
    USART_Init();
    uint8_t adc_val;
    uint8_t temp = 0;
    char buf[10];
    
    sei();
    
    lcd_init(LCD_DISP_ON_BLINK);
    lcd_home();
    uint8_t led = 0;
    lcd_led(led);
    
    
    while(1)
    {
//        int i = 0;
//        int line = 0;
//        for(i=0; i<10; i++) {
//            char buf[10];
//            itoa(i, buf, 10);
//            lcd_gotoxy(1, line);
//            lcd_puts("i= ");
//            itoa(i, buf, 10);
//            lcd_gotoxy(4, line);
//            lcd_puts(buf);
//            line++;
//            line %= 2;
//            USART_TransmitString((uint8_t*) buf);
//            USART_TransmitString((uint8_t*)"\r\n");
//            _delay_ms(100);
//        }
        
        adc_val = ADC_ReadChannel(2);
        itoa(adc_val, buf, 10);
        if(adc_val != temp){
            lcd_clrscr();
            lcd_puts(buf);
        }
        
        _delay_ms(50);
        temp = adc_val;
        
    }
    
    
    
    return 0;
}
