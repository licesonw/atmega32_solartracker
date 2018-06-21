//
//  servolib.h
//  Library for driving a the servo motor
//
//  Created by David Lichtenwalter on 07.06.18.
//  Copyright © 2018 David Lichtenwalter. All rights reserved.
//

#ifndef SERVOLIB_H
#define SERVOLIB_H

#include <math.h>

#define SERVO_PWM_LOW 8
#define SERVO_PWM_HIGH 37

void Servo0_Init(void)
{
    DDRB |= (1<<PB3);
    // Timer0 Init
    TCCR0 |= (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01)|(1<<CS00);
}

void Servo0_AssumePosition(uint8_t angle)
{
    // Only allow angles up to 180 degrees
    if(angle > 180)
        angle = 180;
    else if(angle < 0)
        angle = 0;
    
    // scale into region from 0 to 1
    double scaled = (double)angle/180;
    
    // rescale into region for output compare value
    scaled = round(scaled * (SERVO_PWM_HIGH - SERVO_PWM_LOW));
    
    // calculate output compare value for the PWM pulse
    uint8_t ocr_val = SERVO_PWM_LOW + (uint8_t)scaled;
    OCR0 = ocr_val;
}

#endif
