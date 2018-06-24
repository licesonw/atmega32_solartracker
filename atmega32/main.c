#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lcdpcf8574.h"
#include "uartlib.h"
#include "adclib.h"
#include "servolib.h"

#define TOLERANCE 100
#define SERVO_VERT_MIN 0
#define SERVO_VERT_MAX 50
#define SERVO_HOR_MIN 0
#define SERVO_HOR_MAX 100

#define SERVO_STEPSIZE 1

void Init (void)
{
    ADC_Init();
    USART_Init();
    Servo_Init();
    
    // LCD Initialization
//    _delay_ms(1000);
//    lcd_init(LCD_DISP_ON_BLINK);
//    lcd_home();
//    uint8_t led = 0;
//    lcd_led(led);
    
    // Set pullup resistors for LCD
    PORTC |= (1<<PC0)|(1<<PC1);
    
    // Set ADC inputs direction
    PORTA &= ~((1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3));
    
    sei();
}

int main (void)
{
    Init();
    int servo_vertical = 50;
    int servo_horizontal = 50;
    
    int avg_top = 0;
    int avg_bottom = 0;
    int avg_left = 0;
    int avg_right = 0;
    
    int diff_vertical = 0;
    int diff_horizontal = 0;
    
    char buf[4];
    
    uint16_t ldr_right_bottom;
    uint16_t ldr_left_bottom;
    uint16_t ldr_right_top;
    uint16_t ldr_left_top;
    
    while(1)
    {
        // Read LDR values
        ldr_right_bottom = ADC_ReadChannel(0);
        _delay_us(10);
        ldr_left_bottom = ADC_ReadChannel(1);
        _delay_us(10);
        ldr_right_top = ADC_ReadChannel(2);
        _delay_us(10);
        ldr_left_top = ADC_ReadChannel(3);
        
        // Calculate average values
        avg_top = (ldr_left_top + ldr_right_top) / 2;
        avg_bottom = (ldr_left_bottom + ldr_right_bottom) / 2;
        avg_left = (ldr_left_bottom + ldr_left_top) / 2;
        avg_right = (ldr_right_bottom + ldr_right_top) / 2;
        
        // Calculate differences
        diff_vertical = abs(avg_top - avg_bottom);
        diff_horizontal = abs(avg_left - avg_right);
        
        // Change vertical angle if out of tolerance
        if(diff_vertical > TOLERANCE)
        {
            if(avg_top < avg_bottom)
            {
                servo_vertical = servo_vertical + SERVO_STEPSIZE;
                if(servo_vertical > SERVO_VERT_MAX)
                    servo_vertical = SERVO_VERT_MAX;
            }
            else if(avg_top > avg_bottom)
            {
                servo_vertical = servo_vertical - SERVO_STEPSIZE;
                if(servo_vertical < SERVO_VERT_MIN)
                    servo_vertical = SERVO_VERT_MIN;
            }
            ServoPC3_Pos(servo_vertical);
        }
        
        // Change horizontal if out of tolerance
        if(diff_horizontal > TOLERANCE)
        {
            if(avg_left > avg_right)
            {
                servo_horizontal = servo_horizontal - SERVO_STEPSIZE;
                if(servo_horizontal < SERVO_HOR_MIN)
                    servo_horizontal = SERVO_HOR_MIN;
            }
            else if(avg_left < avg_right)
            {
                servo_horizontal = servo_horizontal + SERVO_STEPSIZE;
                if(servo_horizontal > SERVO_HOR_MAX)
                    servo_horizontal = SERVO_HOR_MAX;
            }
            ServoPC2_Pos(servo_horizontal);
        }
        
        _delay_ms(10);
        
        
        USART_TransmitString("AVG top:" );
        itoa(avg_top, buf, 10);
        USART_TransmitString(buf);
        USART_TransmitString("\n\0");
        
        USART_TransmitString("AVG bottom:" );
        itoa(avg_bottom, buf, 10);
        USART_TransmitString(buf);
        USART_TransmitString("\n\0");
        
        USART_TransmitString("AVG left:" );
        itoa(avg_left, buf, 10);
        USART_TransmitString(buf);
        USART_TransmitString("\n\0");
        
        USART_TransmitString("AVG right:" );
        itoa(avg_right, buf, 10);
        USART_TransmitString(buf);
        USART_TransmitString("\n\0");
        
        
        
        
        
        
    }
    
    
    
    return 0;
}

