#ifndef STATE_H
#define STATE_H

#include <avr/io.h>
#include "../modules/Usart.h"

void state()
{
	Usart::send(DDRA);
	Usart::send(DDRB);
	Usart::send(DDRC);
	Usart::send(DDRD);
	Usart::send(PORTA);
	Usart::send(PORTB);
	Usart::send(PORTC);
	Usart::send(PORTD);
	//Usart::send(PINA);
	//Usart::send(PINB);
	//Usart::send(PINC);
	//Usart::send(PIND);
}

#endif