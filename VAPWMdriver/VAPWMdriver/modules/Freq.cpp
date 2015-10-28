#include "Freq.h"

bool FREQ::capture_state = false;
uint8_t FREQ::setting = 0;

uint8_t FREQ::l_val = 0;
uint8_t FREQ::h_val = 0;
uint8_t FREQ::to_fix_low = 0;
uint8_t FREQ::to_fix_high = 0;

void FREQ::init(){
	TCCR1B |= /*((1<<WGM12) | (1<<WGM13) |*/ ((1<<CS12) | (1<<CS10));
	TIMSK |= ((1<<TICIE1) | (1<<TOIE1));
	sei();
	PWM::get(PWM::PWM0).on();
	
	DDRD |= (1<<PD7);
	DDRC |= (1<<PC0);
}

void FREQ::uninit(){
	TCCR1B = 0;
	TIMSK = 0;
	PWM::get(PWM::PWM0).off();
}

void FREQ::set_int(bool timeout){
	if(!timeout){
		FREQ::l_val = ICR1L;
		FREQ::h_val = ICR1H;
	}
	else{
		FREQ::h_val = 0;
		FREQ::l_val = 0;
	}
	FREQ::capture_state = true;
	TCNT1 = 0;
}
	
void FREQ::start_engine(){
	FREQ::setting+=5;
	PWM::get(PWM::PWM0).set(FREQ::setting);
	Usart::send(FREQ::setting);
}

void FREQ::set_period(uint8_t freq){
	float freq_cpu = 14745600;
	uint16_t tictoc = (uint16_t)(freq_cpu/freq/1024);
	
	FREQ::to_fix_low = (uint8_t)(tictoc&0x00FF);
	FREQ::to_fix_high = (uint8_t)((tictoc&0xFF00)>>8);
	//Usart::send('l');
	//Usart::send(FREQ::to_fix_low);
	//Usart::send('h');
	//Usart::send(FREQ::to_fix_high);
}

void FREQ::update(){
	FREQ::capture_state = false;
	
	int balance = FREQ::h_val - FREQ::to_fix_high;
	
	
	if(balance + FREQ::setting < 0)
		FREQ::setting = 0;
	else if(balance + FREQ::setting > 255)
		FREQ::setting = 255;
	else
		FREQ::setting = balance + FREQ::setting;
	
	
	PWM::get(PWM::PWM0).set(FREQ::setting);
	Usart::send(FREQ::setting);
}

bool FREQ::is_init(){
	if(FREQ::setting==0)
	return false;
	else
	return true;
}

bool FREQ::is_capture(){
	return FREQ::capture_state;
}

ISR(TIMER1_CAPT_vect){
	FREQ::set_int(false);
	FREQ::update();
	PORTD ^= (1<<PD7);
}

ISR(TIMER1_OVF_vect){
	FREQ::set_int(true);
	Usart::send('m');
	FREQ::start_engine();
};