/*
Usart::pushFunction(Usart::Scenario(state, 0), 0);
Usart::pushFunction(Usart::Scenario(temperatureSensor, 0), 1);
Usart::pushFunction(Usart::Scenario(paramsTest, 4), 2);
Usart::pushFunction(Usart::Scenario(asciiTest, 0), 3);
*/

/************************************************************************/
/* scenariusz programu - przykladowy kod
	Usart::pushFunction(Usart::Scenario(nazwa_funcji, ilosc_charow_do_odebrania), nr_komendy);
*/
/************************************************************************/

Usart::pushFunction(Usart::Scenario(state, 0), 0);
Usart::pushFunction(Usart::Scenario(voltometer, 1), 1);
Usart::pushFunction(Usart::Scenario(set_pwm, 2), 2);
Usart::pushFunction(Usart::Scenario(set_freq, 1), 3);
//Usart::pushFunction(Usart::Scenario(temperature, 1), 2);
//Usart::pushFunction(Usart::Scenario(temperatureSensor, 0), 2);
//Usart::pushFunction(Usart::Scenario(paramsTest, 4), 2);
//Usart::pushFunction(Usart::Scenario(asciiTest, 0), 3);
//...