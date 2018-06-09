//
//  adclib.h
//  Library for the ADC
//
//  Created by David Lichtenwalter on 07.06.18.
//  Copyright © 2018 David Lichtenwalter. All rights reserved.
//

#ifndef ADCLIB_H
#define ADCLIB_H

uint8_t ADC_ReadChannel( uint8_t channel );
void ADC_Init(void);

void ADC_Init(void)
{
    // 8 bit mode
    ADMUX |= (1<<ADLAR)|(1<<REFS0);
    
    // Enable and free running mode
    ADCSRA |= (1<<ADEN)|(1<<ADATE);
    
    // free running mode
    SFIOR &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
    
    // Prescaler of 2
    ADCSRA &= ~((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2));
    
    // 8bit mode: only read ADCH register
}

uint8_t ADC_ReadChannel(uint8_t channel)
{
    // Choose channel with bitmask
    uint8_t muxmask = channel & 0x1F;
    ADMUX |= muxmask;
    
    ADCSRA |= (1<<ADSC);            // Single conversion
    while (!(ADCSRA & (1<<ADSC)) ) {   // Wait for conversion
    }
    return ADCH;                    // Read adc
}

#endif
