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
    
    lcd_init(LCD_DISP_ON_BLINK);
    lcd_home();
    uint8_t led = 0;
    lcd_led(led);
    
    sei();
    
    uint16_t adc_val_up = 0;
    uint16_t adc_val_down = 0;
    int diff;
    
    char buf[10];
    
    int servo_deg = 0;
    
    
    while(1)
    {
        lcd_puts("XYZ\0");
        _delay_ms(2000);
        
    }
    
    
    
    return 0;
}

