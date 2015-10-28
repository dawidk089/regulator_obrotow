#ifndef DC_MODULATION_H_
#define DC_MODULATION_H_

//inlcude modules
#include "../modules/Usart.h"
#include "../modules/Pwm.h"

/************************************************************************/
/* PWM
#kodowanie parametrow:
-1: id_pin 0-3 [OC0, OC1A, OC1B, OC2]
-2: width value 0-255
*/
/************************************************************************/

void set_pwm(){
	
	uint8_t temp = Usart::getBit(0);
	PWM::ID pwm_nr = PWM::ID(temp);
	uint8_t width = Usart::getBits(8, 8);
	
	Usart::send(temp);
	Usart::send(width);
	
	DDRB |= (1<<PB2);
	PORTB |= (1<<PB2);
	
	if(width){
		if(!PWM::get(pwm_nr).is_on())
			PWM::get(pwm_nr).on();
		PWM::get(pwm_nr).set(width);
	}
	else{
		PORTB &= ~(1<<PB2);
		PWM::get(pwm_nr).set(0);
		PWM::get(pwm_nr).off();
	}
	
}





#endif /* DC_MODULATION_H_ */