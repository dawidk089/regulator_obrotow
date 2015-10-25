#ifndef USART_H
#define USART_H

#include "../config/main.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

class Usart
{
	
public:

	struct Scenario
	{
		Scenario();
		Scenario(void (*function)(), const uint8_t &paramsBytes);
		void (*function)();
		uint8_t paramsBytes;
	};

	// public members
	static char incomeChar;
	static bool newCharReceived;
	static uint8_t params[4];

	// interface
	static void init();
	static void run();
	static void send(char toSend);
	static void send(const char *toSend);
	static void pushFunction(const Scenario &scenario, uint8_t id);
	static const bool getBit(const uint8_t &nr);
	static const uint32_t getBits(const uint8_t &start, const uint8_t &size = 1);
	
	
private:

	// hidden functions
	static const char receive();

	// private properties
	static Scenario scenarios[256];
	static uint8_t paramsToRecv;
	static uint8_t commandWithArguments;
	
};

#endif