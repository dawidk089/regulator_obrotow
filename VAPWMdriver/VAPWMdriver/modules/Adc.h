#ifndef ADC_H_
#define ADC_H_

#include "../config/main.h"
#include "Usart.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Pin.h"

class Adc
{

public:

	enum VREF
	{
		EXT = 0x00,
		VCC = 0x40,
		V2_56 = 0xc0
	};

	enum SPECIAL_VREF
	{
		VGB = 0x1e,
		GND = 0x1f
	};
	
	enum PIN_PAIR
	{
		_0_1 = 0x00,
		_3_2 = 0x04
	};
	
	enum GAIN
	{
		_10x = 0x00,
		_200x = 0x02
	};
	
	enum PRESCALER
	{
		_2 = 0x01,
		_4 = 0x02,
		_8 = 0x03,
		_16 = 0x04,
		_32 = 0x05,
		_64 = 0x06,
		_128 = 0x07
	};
	
	struct Measurement
	{
		Measurement(const Register::ADDR &low, const Register::ADDR &high);
		Measurement();
		uint8_t low;
		uint8_t high;
	};

	static void configureSingle(const uint8_t &pin, const VREF &vref, const PRESCALER &prescaler = _64);
	static void configureGained(const PIN_PAIR &pinPair, const bool &isCallibration, const GAIN &gain, const VREF &vref, const PRESCALER &prescaler = _64);
	static void configureDifferential(const uint8_t &pinPlus, const uint8_t &pinMinus, const VREF &vref, const PRESCALER &prescaler = _64);
	static void configureSpecial(const SPECIAL_VREF &specialVref, const PRESCALER &prescaler = _64);
	static const Measurement measure();

private:

	static bool isConfigured;
	static uint8_t mux;
	static PRESCALER prescaler;
	
	static void setRegisters();

};

#endif /* ADC_H_ */