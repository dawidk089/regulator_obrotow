#include "config/scenario_glue.h"
#include "modules/Usart.h"
#include "modules/Adc.h"


int main(void)
{ 
	//DDRD |= (1<<PD6);
	
	DDRC |= (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);
	Usart::init();
	#include "config/scenario_register.h"
	Usart::run();
	/*DDRD |= (1<<PD6);
	while(1){
		PORTD ^= (1<<PD6);
		_delay_ms(50);		
	}*/
}