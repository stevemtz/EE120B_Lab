/*	Author: smart051
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


int main(void) {
  DDRA = 0x00; PORTA = 0xFF; 
  DDRC = 0xFF; PORTC = 0x00;

  unsigned char level = 0x00;
  unsigned char Lights = 0x00; 



    while (1) {
      level = PINA ;
      Lights = 0x00; 
      if(level <= 2){
	Lights =  0x60;
	PORTC = Lights ;
      }
      if(level <= 4 && level >= 3){
	Lights = 0x70;
	PORTC = Lights;
      }
      if(level >= 5 && level<= 6){
	Lights = 0x38;
	PORTC = Lights;
      }
      if(level <= 9&& level >= 7){
	Lights = 0x3C;
	PORTC= Lights;
      }
      if(level >= 10 && level<= 12){
	Lights = 0x3E;
	PORTC =Lights;
      }
      if(level <= 15 && level >= 12){
	Lights = 0x3F;
	PORTC = Lights;
      }
    PORTC = Lights ;

    }
      return 1;
}
