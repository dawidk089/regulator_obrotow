#include "Pin.h"

// static members

Pin Pin::instances[] =
{
	#include "../config/pinout.h"
};

// interface

void Pin::setLow()
{
	Register::setOn(direction, addrMask);
	Register::setOff(outState, addrMask);
}

void Pin::setHigh()
{
	Register::setOn(direction, addrMask);
	Register::setOn(outState, addrMask);
}

const bool Pin::isHigh() const
{
	return Register::isHigh(outState, addrMask);
}

void Pin::read()
{
	Register::setOff(direction, addrMask);
	Register::setOff(outState, addrMask);
}

void Pin::pullUp()
{
	Register::setOff(direction, addrMask);
	Register::setOn(outState, addrMask);
}

const Register::BIT_NR &Pin::getAddrMask() const
{
	return addrMask;
}

Pin &Pin::get(const uint8_t &index)
{
	for (uint8_t i = 0; i < CONFIG_PINOUT_COUNT; ++i)
	{
		if (index == instances[i].nr)
			return instances[i];
	}
	return instances[0];
}

// hidden

Pin::Pin(const uint8_t &nr, Register::ADDR &direction, Register::ADDR &inState, Register::ADDR &outState, const int &n_addrMask, const bool &n_isAllowed)
: nr(nr), direction(direction), inState(inState), outState(outState), addrMask(n_addrMask), isAllowed(n_isAllowed)
{
}