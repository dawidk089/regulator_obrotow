#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

#include "../modules/Usart.h"
#include "../modules/Adc.h"
#include "../modules/Pin.h"

void temperatureSensor()
{
	for (uint8_t adcPinNr = 5; adcPinNr < 8; ++adcPinNr)
	{
		Adc::configureSingle(adcPinNr, Adc::V2_56);
		Adc::Measurement measurement = Adc::measure();
		Usart::send(measurement.high);
		Usart::send(measurement.low);
	}
}

#endif /* TEMPERATURESENSOR_H_ */