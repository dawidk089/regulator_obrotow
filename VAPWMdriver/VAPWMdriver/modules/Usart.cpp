#include "Usart.h"

// inicjalizacja wlasciwosci statycznych klasy Usart
Usart::Scenario Usart::scenarios[256];
uint8_t Usart::params[4];
uint8_t Usart::paramsToRecv;
uint8_t Usart::commandWithArguments;
char Usart::incomeChar;
bool Usart::newCharReceived;

// definicja wektora przerwan odbioru danych USART
ISR(USART_RXC_vect)
{
	Usart::incomeChar = UDR;
	Usart::newCharReceived = true;
}

Usart::Scenario::Scenario()
{
}

Usart::Scenario::Scenario(void (*function)(), const uint8_t &paramsBytes)
: function(function), paramsBytes(paramsBytes)
{
}

void Usart::init()
{
	// wlaczenie transmisji, wlaczenie odbioru, wlaczenie przerwania odbioru
	UCSRB = (1<<TXEN) | (1<<RXEN) | (1<<RXCIE);
	//nastaw 8-bitowej ramki
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	// for 9600 baud at 1MHz
	UBRRL = USART_UBRRL;
	sei();
}

void Usart::run()
{
	while (true)
	{
		const char scenarioCode = receive();
		const uint8_t &scenarioParams = scenarios[scenarioCode].paramsBytes;
		for (uint8_t i = 0; i < scenarioParams; ++i)
			params[i] = receive();
		send(scenarioCode);
		scenarios[scenarioCode].function();
	}
}

const char Usart::receive()
{
	while (!newCharReceived)
		_delay_ms(USART_SLEEP_TIME);
	char temp = incomeChar;
	newCharReceived = false;
	return temp;
}

void Usart::send(char toSend)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = toSend;
}

void Usart::send(const char *toSend)
{
	send(128);
	while (*toSend != '\0')
		send(*toSend++);
	send('\0');
}

void Usart::pushFunction(const Scenario &scenario, uint8_t id)
{
	scenarios[id] = scenario;
}

const bool Usart::getBit(const uint8_t &nr)
{
	
	return   ( params[(nr>>3)] & (1 << ((nr) - ((nr)>>3<<3))))   ;
}



const uint32_t Usart::getBits(const uint8_t &start, const uint8_t &size)
{
	uint32_t bits = 0x00;
	for (uint8_t i = 0; i < size; ++i)
		bits += (getBit(start + i) << i);
	
	return bits;
}