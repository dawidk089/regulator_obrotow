/************************************************************************/
/* 
get(nr)
.is_on()
.on()
.off()
.set()

tryb nieodwrocony
8 bitow rozdzielczosci
                                                                    */
/************************************************************************/


#ifndef PWM_H_
#define PWM_H_

#include "../config/main.h"
#include "Usart.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Pin.h"




class PWM {
	
public:

//unikalne id kazdego wyjscie pwm 
//OC0, OC1A, OC1B, OC2
	enum ID{
		PWM0 = 0x00,
		PWM1A = 0x01,
		PWM1B = 0x02,
		PWM2 = 0x03
	};
	
private:

//pole obiektu PWM (modulu PWM) przechowujace swoje id
	ID pwm_id;
	
//ple obiektu PWM (modulu PWM) przechowujace swoj stan (wl/wyl)
	bool state;
	
//pole statyczne PWM przechowuje tablice czterech obiektow (modulow) PWM 
	static PWM pwm_unit[4];

public: 
	
// konstruktor obiektu PWM, pobierajacy wlasny id
	PWM(ID id);
	
// metoda zwracajaca obiekt o podanym id
	static PWM get(ID id);
	
// metoda zwracajaca stan (wl/wyl) obiektu PWM
	bool is_on(){
		return state;
	}
	
// metoda inincjalizujaca modul PWM
	void on();
	
// metoda deinicjalizujaca (zerujaca) modul PWM
	void off();
	
// metoda ustawiajaca szerokosc impulsu modulu PWM
	void set(uint8_t width);	
			
};

#endif /* PWM_H_ */