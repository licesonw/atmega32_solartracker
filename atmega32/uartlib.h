//
//  uartlib.h
//  Library for the USART
//
//  Created by David Lichtenwalter on 07.06.18.
//  Copyright © 2018 David Lichtenwalter. All rights reserved.
//

#ifndef UARTLIB_H
#define UARTLIB_H

#include <stdlib.h>

#define BAUD 62500UL
#define UBRR_VAL (F_CPU/(BAUD*16)-1)

void USART_Init(void);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_TransmitString (unsigned char *s);
unsigned char* USART_ReceiveString(void);


/**
 @brief     Init USART with a baudrate of 62500. Enable TX and RX.
*/
void USART_Init(void) {
    UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;
    UCSRB = (1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}


/**
 @brief     Transmit a single byte via USART.
 */
void USART_Transmit(uint8_t data) {
    while(!(UCSRA & (1<<UDRE))) {
    }
    UDR = data;
}


/**
 @brief     Reveive a single byte via USART.
 @return    Returns the reveived byte.
 */
unsigned char USART_Receive(void) {
    while(!(UCSRA & (1<<RXC))) {
        // wait
    }
    
    return UDR;
}


/**
 @brief     Reveive a string via USART.
 @return    Returns the string as a char array.
 */
unsigned char* USART_ReceiveString(void)
{
    unsigned char c;
    unsigned char str[20];
    int i = 0;
    while( (c = USART_Receive()) != '\0')
    {
        str[i] = c;
        i++;
        USART_Transmit(c);
    }
    return str;
}


/**
 @brief     Transmit a string via USART.
 */
void USART_TransmitString (uint8_t *s)
{
    while (*s)
    {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
        USART_Transmit(*s);
        s++;
    }
}


/**
 @brief     Transmit an integer together with a descriptive string.
 */
void USART_TransmitInteger(int integer, unsigned char *str)
{
    char buf[10];
    USART_TransmitString(str);
    itoa(integer, buf, 10);
    USART_TransmitString((uint8_t*)buf);
    USART_TransmitString((uint8_t*)"\n\0");
}

#endif
