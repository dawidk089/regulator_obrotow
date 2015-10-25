#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "../modules/Usart.h"
#include "../modules/Adc.h"
#include "../modules/Pin.h"

/************************************************************************
#kodowanie parametrow:                            
   -3: id_pin 0-7
   zawsze V_ref=2.56V 
************************************************************************/ 

void temperature()
{
	uint8_t adcPinNr = Usart::getBits(0,3);
	Adc::configureSingle(adcPinNr, Adc::V2_56);

	Adc::Measurement measurement = Adc::measure();
	Usart::send(measurement.high);
	Usart::send(measurement.low);
}

#endif /* TEMPERATURE_H_ */