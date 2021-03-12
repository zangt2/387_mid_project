#include <stdint.h>
#include "libLCD/hd44780.h"
#include <avr/io.h>
#include <util/delay.h>

#define SECOND_IN_ms 1000
#define MY_BUTTON1 PD7
#define MY_BUTTON2 PD6

#define nearpin 2
#define farpin 3
#define nearled 6
#define farled 5

int valueFar;
int valueNear;

/* C Prototypes of functions */
void clear_menu();
void ini_analog(void);
uint16_t readValueOf(uint8_t val);
void Time_Delay_Longer( uint32_t delay_time_ms);
short check_button_press(int button);
short check_button_press_and_release(int button);
int main(void)
{
DDRD |= _BV(farled);
DDRD |= _BV(nearled);
//Setup
LCD_Setup();
clear_menu();
ini_analog();
 while(1)
        {
		valueFar=readValueOf(farpin);
		valueNear=readValueOf(nearpin);
		LCD_GotoXY(5, 0);
		LCD_PrintInteger(valueFar);
		LCD_GotoXY(5, 1);
                LCD_PrintInteger(valueNear);
		Time_Delay_Longer(100);

   
 	}
}

/* 
 * clear the screen and show the menu 
 * 
 */
void clear_menu()
{
	//Print two lines with menu
	uint8_t line;
	for (line = 0; line < 2; line++)
	{
		LCD_GotoXY(0, line);
		if (line == 0)
		{
			LCD_PrintString("far: ");
		}
		else 
		{
			LCD_PrintString("near:");
		}
	}
	
}

/* 
 * checks when a button on the D port is pressed assuming a pull-down in non-pressed state 
 * 
 * WIRING: input and resitor on same connection, Vcc on other connection
 */
short check_button_press_and_release(int button)
{
	int ret_val = 0;
	//PRE_CONDITION_DBC(button >= 0, 6000);
	//PRE_CONDITION_DBC(button < 8, 7000);
	if ((PIND & (1 << button)) != 0)
	{
		/* software debounce */
		_delay_ms(50);
		if ((PIND & (1 << button)) != 0)
		{
			/* wait for button to be released */
			while((PIND & (1 << button)) != 0)
				ret_val = 1;
		}
	}

	//POST_CONDITION_DBC(ret_val == 1 || ret_val == 0, 5000);
	return ret_val;
}

/* 
 * checks when a button on the D port is pressed assuming a pull-down in non-pressed state 
 * 
 * WIRING: input and resitor on same connection, Vcc on other connection
 */
short check_button_press(int button)
{
	int ret_val = 0;

	//PRE_CONDITION_DBC(button >= 0, 4000);
	//PRE_CONDITION_DBC(button < 8, 5000);

	if ((PIND & (1 << button)) != 0)
	{
		/* software debounce */
		_delay_ms(50);
		if ((PIND & (1 << button)) != 0)
		{
			ret_val = 1;
		}
	}

	//POST_CONDITION_DBC(ret_val == 1 || ret_val == 0, 5000);

	return ret_val;
}

/* * * * * * * * * * * * * *
  purpose: split a large delay into small pieces to avoid wrong timing when facing long duration in arduino
  how: for every ten ms, delay 10ms; for initial time in ms mod 10, delay 1 ms for each ms
  input: a long delay time in ms
  output: none
  borrowed from : https://www.avrfreaks.net/forum/delayms-problem, and edit by Selina
 * * * * * * * * * * * * * */
void Time_Delay_Longer(uint32_t delay_time_ms) 
{
	uint32_t i; //index for every ten ms

	for (i=0; i<(delay_time_ms/10); i++) 
	{
		_delay_ms(10);
	}
	uint32_t ii; //index foe every one ms
	for(ii=0;ii<(delay_time_ms%10);ii++){
		_delay_ms(1);
	}
}


uint16_t readValueOf(uint8_t val)
{
	ADMUX &= 0xF0;  //Clear the older channel that was read
 	ADMUX |= val;                //Defines the new ADC channel to be read
 	ADCSRA |= (1<<ADSC);                //Starts a new conversion
 	while(ADCSRA & (1<<ADSC));            //Wait until the conversion is done
 	return ADCW; 
}

void ini_analog(void)
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    //16Mhz/128 = 125Khz the ADC reference clock
	ADMUX |= (1<<REFS0);                //Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN);                //Turn on ADC
	ADCSRA |= (1<<ADSC);  
}
