#include "Pwm.h"

PWM PWM::get(PWM::ID id){
	return PWM::pwm_unit[uint8_t(id)];
}


PWM PWM::pwm_unit[4] = {
PWM(PWM::PWM0), PWM(PWM::PWM1A), PWM(PWM::PWM1B), PWM(PWM::PWM2)};

PWM::PWM(ID id):pwm_id(id), state(false){}

void PWM::on(){
	switch(pwm_id){
		case PWM::PWM0:
		TCCR0 |= ((1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00));
		OCR0 = 0;
		DDRB |= (1<<PB3);
		break;
	}
	state = true;
}

void PWM::off(){
	switch(pwm_id){
		case PWM::PWM0:
		TCCR0 = 0;
		OCR0 = 0;
		DDRB |= (1<<PB3);
		break;
	}
	
	state = false;
}

void PWM::set(uint8_t width){
	if(!state)
		on();
	switch(pwm_id){
		case PWM::PWM0:
		OCR0 = width;	
		break;
	}
}

	
