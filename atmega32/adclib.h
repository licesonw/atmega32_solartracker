//
//  adclib.h
//  Library for the ADC
//
//  Created by David Lichtenwalter on 07.06.18.
//  Copyright © 2018 David Lichtenwalter. All rights reserved.
//

#ifndef ADCLIB_H
#define ADCLIB_H

uint16_t ADC_ReadChannel( uint8_t channel );
void ADC_Init(void);

void ADC_Init(void)
{
    // 8 bit mode
    ADMUX |= (1<<REFS0);
    
    // Enable
    ADCSRA |= (1<<ADEN);
    
    // free running mode
    //SFIOR &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
    
    // Prescaler of 64
    ADCSRA &= ~(1<<ADPS0);
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1);
    
    // 8bit mode: only read ADCH register
}

uint16_t ADC_ReadChannel(uint8_t channel)
{
    ADMUX = (ADMUX & 0xE0) | (channel & 0x1F);  // Set channel via bitmask
    
    ADCSRA |= (1<<ADSC);            // Single conversion
    while (ADCSRA & (1<<ADSC));   // Wait for conversion
    return ADCW;                    // Read adc
}

#endif
