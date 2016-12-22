/*
 * final_game.c
 *
 * Created: 8/24/2016 6:02:00 PM
 *  Author: Baba
 */ 

/*
 * final_code.c
 *
 * Created: 8/15/2016 12:04:52 AM
 *  Author: Baba
 */ 



#include <avr/io.h>
#include <avr/sfr_defs.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define threshold 80
#include "USART_128.h"
//#define overflow 0.065
int rc,avg,rand_on,time=0,tot_time=0,i,count=0,comp_flag=0;

 /*int average( int rc)
{
	//int frequency=10;
    int i,tcnt[10]={0},sum=0;int j=0;
	if(i>10)
	{i=0;}
	tcnt[i]=rc;
	for(j=0;j<10;j++)
	avg=(sum+tcnt[j])/10;
	i++;
	return avg;
}*/
 
volatile int tot_overflow=0;

void timer_init()
{
	ETIMSK|=1<<TOIE3;
	TCCR1B|=1<<CS12;      //prescalar 256
	TCNT1=0;
	TCCR3B|= 1<<CS30;    // prescaler 1024 
	TCNT3=0;
	//TIMSK |= 1<<OCIE3B;
	sei();
	//OCR3B=7812;
	
}

int main(void)
{
	USART_Init(12,0);
	//int i;
	timer_init();
	DDRD|=0b11111111;
	//PORTD=1<<PIND2;
	USART_TransmitString("Hello",0);
	
	//TCNT3=0;
	
	
		for (i=0;i<36;i++)
		{ 	
			rand_on=rand()%6;	
			PORTD=1<<rand_on;
		   
			label:
			DDRA|=0xFF;
			PORTA=0b00000000;
			_delay_ms(100);
			DDRA=0b00000000;
			TCNT1=0;
			while (!bit_is_set(PINA,rand_on));
			rc=TCNT1;
			//int average( int rc);
			//rc=avg;
			if(rc>threshold)
			{
				PORTD &= ~(1<<rand_on);
			}
			else 
			//timer_overflow();
			goto label;
			USART_TransmitNumber(rc,0);
			USART_Transmitchar(' ',0);		
		}
		//comp_flag=1;
		
		USART_Transmitchar(0x0D,0);
		tot_time=tot_overflow*65535/8000000;
		USART_TransmitNumber(tot_time,0);
		
		//USART_TransmitNumber(tot_time,0);
		
		
		//TODO:: Please write your application code
	}

ISR(TIMER3_OVF_vect)
{  
	tot_overflow++;
	
	
	/*if(comp_flag==1){
	
	}*/
	
	
	/*if(tot_overflow>3)
	{
		PORTD &= ~(1<<rand_on);
		main();
	}*/
	/*while (!(i<=36));
	PORTD=0b00000000;
	count=tot_overflow;
	time=count*7812+TCNT3;
	USART_TransmitNumber(time,0);*/
	
}
/*void timer_overflow()
{
	int count=0,time=0;
	while (TCNT3>31250)
	{
		count++;
		if(count==3)
		break;
	}
	time=time+TCNT3*count;
	//return time;
	if (time==93750)
	{
		PORTD=1<<rand_on;
	}
	
}*/