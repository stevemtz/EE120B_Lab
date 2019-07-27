
/*	Author: smart051
 *  Partner(s) Name: 
 *	Lab Section:/Users/stevemartinez/Downloads/smart051_lab11_part2.c
 *	Assignment: Final Project
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */









=============================================================================================================
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "io.c"
#include "bit.h"
#include "timer.h"

unsigned long int findGCD(unsigned long int a, unsigned long int b) { 
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
		b = c;
	}
	return 0;	
}

typedef struct _task {
	signed char state; 
	unsigned long int period; 
	unsigned long int elapsedTime; 
	int (*TickFct)(int); 
} task;










unsigned char High_score;
unsigned char Score;
unsigned short count;
unsigned char Joy;
unsigned char SM1_out;
unsigned char Obstacle;
unsigned char me;
unsigned char Obstacle1_pos;
unsigned char Obstacle2_pos;
unsigned char Obstacle3_pos;
unsigned char Obstacle4_pos;
unsigned char Pause; 
unsigned char Vert;
unsigned char Game_over;
unsigned int Big_Bet;



enum SM1_States {SM1_Start, SM1_Wait, SM1_Press, SM1_Hold};  
enum SM2_States {SM2_Start, SM2_Wait, SM2_Up, SM2_Down, SM2_Hold};  
enum SM3_States {SM3_Start, SM3_Move};  
enum SM4_States {SM4_Start, SM4_Check, SM4_Display, SM4_Wait4Reset}; 

/*
unsigned short Yupper = 900;
unsigned short Ylower = 100;
void ADC_init(){
  ADCSRA |= (1<< ADEN) | (1 << ADSC) | (1<< ADATE);

}

if(vertMov > Yupper){
	Vert = 1;
}
if(vertMov < Ylower){
	Vert = 0;
} 
*/









int Tick_Start(int state) {
	switch (state) {
		case SM1_Start: state = SM1_Wait; break;
		case SM1_Wait: state = (Joy == 0x01) ? SM1_Press : SM1_Wait; break;
		case SM1_Press: state = (Joy == 0x01) ? SM1_Hold : SM1_Wait; break;
		case SM1_Hold: state = (Joy == 0x00) ? SM1_Wait : SM1_Hold; break;
		default: state = SM1_Start; break;
	}
	switch (state) {
		case SM1_Start: 
		LCD_DisplayString(2," Press Start!   High Score:");
 		LCD_WriteData(High_score + '0');
		break;
		case SM1_Wait: 
		break;
		case SM1_Press: 
		Pause = (Pause) ? 0 : 1; 
		LCD_DisplayString(2," Press Start!   High Score:");
 		LCD_WriteData(High_score + '0');	
		break;
		case SM1_Hold: break;
		default: break;
	}
	return state;
}

int Tick_Move(int state) {
	switch(state) {
		case SM2_Start: state = SM2_Wait; break;
		case SM2_Wait:
			if (!Game_over && !Pause) {
				if (Joy == 0x02) {
					state = SM2_Up;
				}
				else if (Joy == 0x04) {
					state = SM2_Down;
				}
				else {
					state = SM2_Wait;
				}
			}
			break;
		case SM2_Up:
			state = (Joy == 0x02) ? SM2_Hold : SM2_Wait;
			break;
	case SM2_Down:
			state = (Joy == 0x04) ? SM2_Hold : SM2_Wait;
			break;
		case SM2_Hold:
			state = (Joy == 0x00) ? SM2_Wait : SM2_Hold;
			break;
		default: state = SM2_Start; break;
	}
	switch (state) {
		case SM2_Start: break;
		case SM2_Wait: break;
		case SM2_Up: 
			Vert = 1; 
			LCD_Cursor(2); 
			LCD_WriteData(me);
			Score++;
			break;
		case SM2_Down: 
			Vert = 0; 
			LCD_Cursor(18); 
			LCD_WriteData(me);
			Score++;
			break;
		default: break;
	}
	return state;
}

int Tick_Keep(int state) {
	switch (state) {
		case SM3_Start: state = SM3_Move; break;
		case SM3_Move: break;
		default: state = SM3_Start; break;
	}
	switch (state) {
		case SM3_Start: break;
		case SM3_Move:
			if (!Pause) {
				if (Obstacle1_pos == 1) {
					Obstacle1_pos = 16;
				}
				else {
					Obstacle1_pos--;
				}
				if (Obstacle2_pos == 17) {
					Obstacle2_pos = 32;
				}
				else {
					Obstacle2_pos--;
				}
				if (Obstacle3_pos == 1) {
					Obstacle3_pos = 16;
				}
				else {
					Obstacle3_pos--;
				}
				if (Obstacle4_pos == 17) {
					Obstacle4_pos = 32;
				}
				else {
					Obstacle4_pos--;
				}
				
				
				LCD_ClearScreen();
				
				LCD_Cursor(Obstacle1_pos);
				LCD_WriteData(Obstacle);
				
				LCD_Cursor(Obstacle2_pos);
				LCD_WriteData(Obstacle);
				
				LCD_Cursor(Obstacle3_pos);
				LCD_WriteData(Obstacle);
				
				LCD_Cursor(Obstacle4_pos);
				LCD_WriteData(Obstacle);
				
				if (Vert) {
				  LCD_Cursor(2);
				    LCD_WriteData(me);
				}
				else {
				  LCD_Cursor(18);
				  LCD_WriteData(me);
				}
				
			}
			
			break;
		default: break;
	}
	return state;
}
int Tick_Collision(int state) {
	switch (state) {
		case SM4_Start: state = SM4_Check;
		case SM4_Check:
			if ((Vert && (Obstacle1_pos == 2)) 
			|| (!Vert && (Obstacle2_pos == 18))
			|| (Vert && (Obstacle3_pos == 2))
			|| (!Vert && (Obstacle4_pos == 18))) {
				state = SM4_Display;
			}
			break;
		case SM4_Display: state = SM4_Wait4Reset; break;
		case SM4_Wait4Reset:
			if (Joy == 0x01) {
				state = SM4_Check;
				Game_over = 0;
			}
			break;
		default: state = SM4_Start; break;
	}
	switch (state) {
		case SM4_Start: break;
		case SM4_Check: break;
		case SM4_Display: 
			Pause = 1; Game_over = 1;
			LCD_ClearScreen();
			LCD_ClearScreen();
			if(Score > High_score){
				High_score = Score;
			}
			else{
 				High_score = High_score;
			}
		/*
		if(High_score < Score){
 			High_score;
 			eeprom_update_byte((uint8_t*)0x02,Score);
		}
		int16_tBig_Bet = eeprom_read_byte((uint8_t*)0x02);
		char Highest[10];
		itoa(Big_Bet, Highest,10);
		*/
			LCD_DisplayString(1,"Your Score:" );
			LCD_WriteData(Score + '0');
			break;
		case SM4_Wait4Reset: 
			Obstacle1_pos = 15;
			Obstacle2_pos = 27;
			Obstacle3_pos = 7;
			Obstacle4_pos = 19;
			Vert = 1;
			Score = 0;
			break;
		default: break;
	}
	return state;
}

int main() {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF, PORTD = 0x00; 

	
	unsigned long int Tick_Start_calc = 100;
	unsigned long int Tick_Move_calc = 100;
	unsigned long int Tick_Keep_calc = 300;
	unsigned long int Tick_Collision_calc = 100;

	
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(Tick_Start_calc, Tick_Move_calc);
	tmpGCD = findGCD(tmpGCD, Tick_Keep_calc);
	tmpGCD = findGCD(tmpGCD, Tick_Collision_calc);

	
	unsigned long int GCD = tmpGCD;

	
	unsigned long int Tick_Start_period = Tick_Start_calc/GCD;
	unsigned long int Tick_Move_period = Tick_Move_calc/GCD;
	unsigned long int Tick_Keep_period = Tick_Keep_calc/GCD;
	unsigned long int Tick_Collision_period = Tick_Collision_calc/GCD;


	
	static task task1, task2, task3, task4;
	task *tasks[] = { &task1, &task2, &task3, &task4};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	
	task1.state = -1;//Task initial state.
	task1.period = Tick_Start_period;//Task Period.
	task1.elapsedTime = Tick_Start_period;//Task current elapsed time.
	task1.TickFct = &Tick_Start;//Function pointer for the tick.

	
	task2.state = -1;
	task2.period = Tick_Move_period;
	task2.elapsedTime = Tick_Move_period;
	task2.TickFct = &Tick_Move;

	
	task.state = -1;
	task3.period = Tick_Keep_period;
	task3.elapsedTime = Tick_Keep_period;
	task3.TickFct = &Tick_Keep;
	
	
	task4.state = -1;
	task4.period = Tick_Collision_period;
	task4.elapsedTime = Tick_Collision_period;
	task4.TickFct = &Tick_Collision;

	
	TimerSet(GCD);
	TimerOn();
	
	
	LCD_init();
	LCD_ClearScreen();
	
	Obstacle = ‘⇼’;
	me = '♡';
	Pause = 1;
	Obstacle1_pos = 15;
	Obstacle2_pos = 27;
	Obstacle3_pos = 7;
	Obstacle4_pos = 19;
	
	LCD_Cursor(Obstacle1_pos); LCD_WriteData(Obstacle);
	LCD_Cursor(Obstacle2_pos); LCD_WriteData(Obstacle);
	LCD_Cursor(Obstacle3_pos); LCD_WriteData(Obstacle);
	LCD_Cursor(Obstacle4_pos); LCD_WriteData(Obstacle);
 	LCD_Cursor(2); LCD_WriteData(me);
	Vert = 1;

	unsigned short i; 
	unsigned short vertMov;

	while(1) {
		Joy = ~PINA & 0x0F;

		for ( i = 0; i < numTasks; i++ ) {
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	return 0;
}


