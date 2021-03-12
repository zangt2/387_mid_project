#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define ledPin 3
//#define flexPin 0
//#define photoPin 5
#define buttonPin 2
#define indicatorPin DDB5

uint16_t threFlex;
uint16_t threPho;

uint8_t numpress;

uint16_t valueFlex;
uint16_t valuePhoto;
/* PROTOTPYES */
void ini_analog(void);
uint16_t readValueOf(uint8_t val);
void my_delay_ms(unsigned int delay);
short check_button_press(int button);
short check_button_press_and_release(int button);

int main(void){
	DDRD |= _BV(DDD3);
	DDRB |= _BV(DDB5);
	ini_analog();
	numpress=0;  


	while(1)
	{	
		if(check_button_press_and_release(buttonPin))
		{	
			numpress++;
			if(numpress%2==1)
			{
				PORTB |= _BV(indicatorPin);
			}
			else
			{
				PORTB &= ~_BV(indicatorPin);
			}
			
			threFlex=readValueOf(0)+30;
			threPho=readValueOf(5)-30;
		}

		valueFlex=readValueOf(0);
		valuePhoto=readValueOf(5);

		if((threFlex>0)&&(threPho>0))
		{
			if((valueFlex<threFlex)&&(valuePhoto>threPho))
			{
				PORTD |= _BV(ledPin);
			}
			else
			{
				PORTD &= ~_BV(ledPin);
			}
			my_delay_ms(100);
		}
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

/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
 *
 * borrowed from : https://www.avrfreaks.net/forum/delayms-problem 
 * */
void my_delay_ms(unsigned int delay_time_ms) 
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
		_delay_ms(15);
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
		_delay_ms(15);
		if ((PIND & (1 << button)) != 0)
		{
			ret_val = 1;
		}
	}

	//POST_CONDITION_DBC(ret_val == 1 || ret_val == 0, 5000);

	return ret_val;
}
