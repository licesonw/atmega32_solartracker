//
//  servolib2.h
//  All
//
//  Created by David Lichtenwalter on 22.06.18.
//  Copyright © 2018 David Lichtenwalter. All rights reserved.
//

#ifndef servolib_h
#define servolib_h

#include <math.h>

#define SERVO_PC2_PULSELIMIT_LOW 560
#define SERVO_PC2_PULSELIMIT_HIGH 2400
#define SERVO_PC3_PULSELIMIT_LOW 700
#define SERVO_PC3_PULSELIMIT_HIGH 2500

// Servos on PC0 - PC4
volatile unsigned int servo[4] = {1500, 1500, 1500, 1500};


ISR(TIMER1_COMPA_vect)
{
    static unsigned char servo_num;
    
    PORTC = (1<<servo_num);          // end pulse for servo (n), start pulse for servo (n+1)
    OCR1A = servo[servo_num];        // set width of pulse
    servo_num++;                     // prepare next servo
    if(servo_num > 4) servo_num = 0; // again from servo 2;
}


/**
 @brief     Intialize TIMER1 for the servo motors.
 */
void Servo_Init(void)
{
    // Servos on PC0 and PC1
    DDRC |= (1<<PC2)|(1<<PC3);
    
    TCCR1B |= (1<<WGM12) | (1<<CS11);  // pwm mode 4,CTC, prescale=8
    TIMSK |= (1<<OCIE1A);             // enable T1_compareA interrupt
    TCNT1 = 65530;
}


/**
 @brief     Set position of servo on PC2 to a percentage of the full range.
*/
void ServoPC2_Pos(uint8_t percent)
{
    if(percent > 100)
        percent = 100;
    else if( percent < 0)
        percent = 0;
    
    // scale into region from 0 to 1
    double scaled = (double)percent/100;
    
    // rescale into region for output compare value
    uint16_t pulse;
    pulse = SERVO_PC2_PULSELIMIT_LOW +  round(scaled * (SERVO_PC2_PULSELIMIT_HIGH - SERVO_PC2_PULSELIMIT_LOW));
    
    servo[2] = pulse;
}


/**
 @brief     Set position of servo on PC3 to a percentage of the full range.
 */
void ServoPC3_Pos(uint8_t percent)
{
    if(percent > 100)
        percent = 100;
    else if( percent < 0)
        percent = 0;
    
    // scale into region from 0 to 1
    double scaled = (double)percent/100;
    
    // rescale into region for output compare value
    uint16_t pulse;
    pulse = SERVO_PC3_PULSELIMIT_LOW +  round(scaled * (SERVO_PC3_PULSELIMIT_HIGH - SERVO_PC3_PULSELIMIT_LOW));
    servo[3] = pulse;
}


#endif /* servolib_h */
