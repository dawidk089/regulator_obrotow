/*
 * paramsTest.h
 *
 * Created: 2015-05-11 01:00:24
 *  Author: Kamil
 */ 

#include "../modules/Usart.h"
#include "../modules/Pin.h"

#ifndef PARAMSTEST_H_
#define PARAMSTEST_H_

union MyParams
{
	uint8_t params[4];
	struct
	{
		char p1: 8;
		char p2: 8;
		char p3: 8;
		char p4: 8;
	};
};

void paramsTest()
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		Pin::get(22).setHigh();
		Pin::get(23).setHigh();
		Pin::get(24).setHigh();
		Pin::get(25).setHigh();
		_delay_ms(100);
		Pin::get(22).setLow();
		Pin::get(23).setLow();
		Pin::get(24).setLow();
		Pin::get(25).setLow();
		_delay_ms(100);
	}
	MyParams myParams;
	myParams.params[0] = Usart::params[0];
	myParams.params[1] = Usart::params[1];
	myParams.params[2] = Usart::params[2];
	myParams.params[3] = Usart::params[3];
	Usart::send(myParams.p1);
	Usart::send(myParams.p2);
	Usart::send(myParams.p3);
	Usart::send(myParams.p4);
}

#endif /* PARAMSTEST_H_ */