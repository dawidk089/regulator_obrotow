#include "Adc.h"

bool Adc::isConfigured = false;
uint8_t Adc::mux;
Adc::PRESCALER Adc::prescaler = Adc::_64;

Adc::Measurement::Measurement(const Register::ADDR &low, const Register::ADDR &high)
: low(low), high(high)
{
}

Adc::Measurement::Measurement()
: low(0xff), high(0xff)
{
}

void Adc::configureSingle(const uint8_t &pin, const Adc::VREF &vref, const Adc::PRESCALER &prescaler)
{
	if (pin > 0x07)
		return;
	mux = vref | (pin & 0x07);
	Adc::prescaler = prescaler;
	for (uint8_t i = 0; i <= 0x07; ++i)
		Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * i).pullUp();
	Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * pin).read();
	isConfigured = true;
}

void Adc::configureGained(const Adc::PIN_PAIR &pinPair, const bool &isCallibration, const Adc::GAIN &gain, const Adc::VREF &vref, const Adc::PRESCALER &prescaler)
{
	mux = pinPair | gain | (!isCallibration) | vref;
	Adc::prescaler = prescaler;
	for (uint8_t i = 0; i <= 0x07; ++i)
		Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * i).pullUp();
	if (!isCallibration)
	{
		switch (pinPair)
		{
			case _0_1:
				Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * 0).read();
				Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * 1).read();
				break;
			case _3_2:
				Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * 2).read();
				Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * 3).read();
				break;
		}			
	}
	isConfigured = true;
}

void Adc::configureDifferential(const uint8_t &pinPlus, const uint8_t &pinMinus, const Adc::VREF &vref, const Adc::PRESCALER &prescaler)
{
	if (pinMinus == 1)
	{
		if (pinPlus > 0x07)
			return;
		mux = 0x00;
	}
	else if (pinMinus == 2)
	{
		if (pinPlus > 0x05)
			return;
		mux = 0x08;
	}
	else
		return;
	mux |= (0x10 | pinMinus | vref);
	Adc::prescaler = prescaler;
	for (uint8_t i = 0; i <= 0x07; ++i)
		Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * i).pullUp();
	Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * pinPlus).read();
	Pin::get(ADC_PIN_OFFSET + (ADC_IS_PIN_REVERSED ? -1 : 1) * pinMinus).read();
	isConfigured = true;
}

void Adc::configureSpecial(const Adc::SPECIAL_VREF &specialVref, const Adc::PRESCALER &prescaler)
{
	mux = specialVref;
	Adc::prescaler = prescaler;
	isConfigured = true;
}

void Adc::setRegisters()
{
	while (ADCSRA & (1<<ADSC));
	ADCSRA &= ~(1<<ADEN);
	_delay_ms(ADC_SLEEP_TIME);
	ADCSRA |= (1<<ADEN) | prescaler;
	ADMUX = mux;
	sei();
}

const Adc::Measurement Adc::measure()
{
	if (!isConfigured)
		return Adc::Measurement();
	setRegisters();
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return Adc::Measurement(ADCL, ADCH);
}