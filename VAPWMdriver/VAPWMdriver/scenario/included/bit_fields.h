#ifndef BIT_FIELDS_H_
#define BIT_FIELDS_H_

#include "../modules/Usart.h"
#include "../modules/Adc.h"
#include "../modules/Pin.h"

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
}

#endif /* BIT_FIELDS_H_ */

;