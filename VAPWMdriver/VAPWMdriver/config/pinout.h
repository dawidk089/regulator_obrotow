/*
 * pinout.h
 *
 * Created: 2015-04-20 02:56:17
 *  Author: Kamil
 *
 * parametry konstruktora Pin:
 * - adres rejestru (dla DIRECTION, PIN_IN, PIN_OUT)
 * - nr bitu
 * - czy dostêpny
 *
 * wa¿ne: nale¿y ustawiæ CONFIG_PINOUT_COUNT
 * - jest to liczba dostêpnych pinów
 */ 

#define CONFIG_PINOUT_COUNT 32

//rejestr B (8)
Pin(1, DDRB, PINB, PORTB, PB0, true),
Pin(2, DDRB, PINB, PORTB, PB1, true),
Pin(3, DDRB, PINB, PORTB, PB2, true),
Pin(4, DDRB, PINB, PORTB, PB3, true),
Pin(5, DDRB, PINB, PORTB, PB4, true),
Pin(6, DDRB, PINB, PORTB, PB5, false),
Pin(7, DDRB, PINB, PORTB, PB6, false),
Pin(8, DDRB, PINB, PORTB, PB7, false),

//rejestr D (8)
Pin(14, DDRD, PIND, PORTD, PD0, false),
Pin(15, DDRD, PIND, PORTD, PD1, false),
Pin(16, DDRD, PIND, PORTD, PD2, true),
Pin(17, DDRD, PIND, PORTD, PD3, true),
Pin(18, DDRD, PIND, PORTD, PD4, true),
Pin(19, DDRD, PIND, PORTD, PD5, true),
Pin(20, DDRD, PIND, PORTD, PD6, true),
Pin(21, DDRD, PIND, PORTD, PD7, true),

//rejestr C (8)
Pin(22, DDRC, PINC, PORTC, PC0, true),
Pin(23, DDRC, PINC, PORTC, PC1, true),
Pin(24, DDRC, PINC, PORTC, PC2, true),
Pin(25, DDRC, PINC, PORTC, PC3, true),
Pin(26, DDRC, PINC, PORTC, PC4, true),
Pin(27, DDRC, PINC, PORTC, PC5, true),
Pin(28, DDRC, PINC, PORTC, PC6, true), 
Pin(29, DDRC, PINC, PORTC, PC7, true),

//rejestr A (ku zaskoczeniu wszystkich 8)
Pin(33, DDRA, PINA, PORTA, PA7, true),
Pin(34, DDRA, PINA, PORTA, PA6, true),
Pin(35, DDRA, PINA, PORTA, PA5, true),
Pin(36, DDRA, PINA, PORTA, PA4, true),
Pin(37, DDRA, PINA, PORTA, PA3, true),
Pin(38, DDRA, PINA, PORTA, PA2, true),
Pin(39, DDRA, PINA, PORTA, PA1, true),
Pin(40, DDRA, PINA, PORTA, PA0, true) // bez przecinka!
