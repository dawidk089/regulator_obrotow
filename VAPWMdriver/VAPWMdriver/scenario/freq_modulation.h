#ifndef FREQ_MODULATION_H_
#define FREQ_MODULATION_H_

//inlcude modules
#include "../modules/Usart.h"
#include "../modules/Pwm.h"
#include "../modules/Freq.h"

void set_freq(){

	uint8_t freq = Usart::getBits(0, 8);	

	DDRB |= (1<<PB2);
	PORTB |= (1<<PB2);

	
	FREQ::set_period(freq);
	
	if(!FREQ::is_init())
		FREQ::init();
	else if(freq==0)
		FREQ::uninit();
}


#endif /* FREQ_MODULATION_H_ */