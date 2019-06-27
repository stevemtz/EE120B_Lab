/*	Author: smart051
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 1
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
  DDRB = 0x00; PORTB = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;

  unsigned char bitCountA = 0x00;
  unsigned char bitCountB = 0x00;
  unsigned char numOnes = 0x00; 


    while (1) {
      PINA = PINA >> 1;
      PINB = PINB >> 1;
      bitCountA = (PINA & 0x01);
      bitCountB = (PINB & 0x01);
      
      if (bitCountA== 0x01){
	numOnes= numOnes+1;
      }

      if (bitCountB== 0x01){
	numOnes= numOnes+1;
      }
      if (bitCountA ==0 && bitCountB==0){
	PORTC = numOnes;
      }
      else{
	PORTC = numOnes;
      }


    }
    PORTC = numOnes;
    bitCountA = 0x00; 
    bitCountB = 0x00;
    numOnes = 0x00;
    return 1;
}
