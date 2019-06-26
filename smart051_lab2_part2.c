/*	Author: smart051
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 2  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include"simAVRHeader.h"
#endif	


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char cntavail = 0;
	unsigned char TakenSpots = 0; 

    while(1){
        if (PINA & 0x01){
            TakenSpots++;
        }
        if (PINA & 0x02){
            TakenSpots++;
        }        
        if (PINA & 0x04){
            TakenSpots++;
        }        
        if (PINA & 0x08){
            TakenSpots++;
        }

        cntavail = 4 - TakenSpots;


        PORTC = cntavail;
        TakenSpots = 0;  
    }
          
}
