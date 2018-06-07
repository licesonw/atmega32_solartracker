//
//  uartlib.h
//  All
//
//  Created by David Lichtenwalter on 07.06.18.
//  Copyright © 2018 David Lichtenwalter. All rights reserved.
//

#define BAUD 62500UL
#define UBRR_VAL (F_CPU/(BAUD*16)-1)

void USART_Init(void);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_TransmitString (unsigned char *s);
unsigned char* USART_ReceiveString(void);


/*
 Init USART with a baudrate set above. Enable TX and RX.
*/
void USART_Init(void) {
    UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;
    UCSRB = (1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

void USART_Transmit(uint8_t data) {
    while(!(UCSRA & (1<<UDRE))) {
    }
    UDR = data;
}

unsigned char USART_Receive(void) {
    while(!(UCSRA & (1<<RXC))) {
        // wait
    }
    
    return UDR;
}

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

void USART_TransmitString (uint8_t *s)
{
    while (*s)
    {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
        USART_Transmit(*s);
        s++;
    }
}
