/*	Author: smart051
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include"simAVRHeader.h"
#endif	

int main(void) {
DDRA = 0x00; PORTA = 0xFF; // Configure port A as input
DDRC = 0xFF; PORTC = 0x00; // Configure port C as output
DDRB = 0x00; PORTB = 0xFF; // Configure port B as input


unsigned char LightSensor = 0x00;
unsigned char DoorSensor = 0x00;
unsigned char LED = 0x00;

while(1) {
        DoorSensor = PINA;
        DoorSensor = DoorSensor & 0x01;   //sets first pin A0
        LightSensor = PINB;
        LightSensor = LightSensor & 0x01;   //sets Second pin A1

        LED = DoorSensor && !LightSensor;

        if (LED){
            PORTC = 0x01;
        }
        else{
            PORTC = 0x00;
        }  

}
return 1;
}
