#ifndef __FREQ_H_
#define __FREQ_H_

//#include "../config/main.h"
//#include <avr/interrupt.h>
//#include <util/delay.h>
//#include "Pin.h"
#include "Pwm.h"
//#include "Usart.h"

class FREQ{
	
	private:
	static uint8_t l_val;
	static uint8_t h_val;
	static bool capture_state;
	static uint8_t to_fix_low;
	static uint8_t to_fix_high;
	static uint8_t setting;
	
	
	protected:

	public:
	static void init();
	static void uninit();
	static void set_int(bool timeout=false);
	static void set_period(uint8_t freq);
	static void update();
	static bool is_init();
	static bool is_capture();
	static void start_engine();
	
};



#endif /* FREQ_H_ */