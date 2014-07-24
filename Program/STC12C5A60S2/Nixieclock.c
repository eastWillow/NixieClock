#include <STC12C5A60S2.h>
#include <DS1307.h>
#include <intrins.h>
#include <I2C.h>
#define DISPLAY P0
#define NUMBER P2
#define ASCIIZERO 0x30
unsigned char number[6]={0,0,0,0,0,0};
//Number ={Seconds.1 Seconds.10 Minutes.1 Minutes.10 Hour.1 Hour.10}
sbit NUMBER_EN = P1^3;
sbit HV_EN = P1^2;
void Delay50us();
void Delay700us();
void display();
void avoidGhost();
void main(void){
	char scan[6]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
	int i;
	while(1){
		HV_EN = 1;
		NUMBER_EN = 1;
		gotDS1307time();
		number[0]=time.seconds&0x0f;
		number[1]=time.seconds>>4;
		number[2]=time.minutes&0x0f;
		number[3]=time.minutes>>4;
		number[4]=time.hours&0x0f;
		number[5]=time.hours>>4;
		NUMBER_EN = 0;
		HV_EN = 0;
		for(i=0;i<6;i++){
			NUMBER=number[i];
			avoidGhost();
			avoidGhost();
			DISPLAY = scan[i];
			Delay700us();
			avoidGhost();
		}
		//resetDS1307time(0x00,0x36,0x14);
	}
}

void Delay700us()		//@12.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 9;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}
void Delay50us()		//@12.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 1;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}
void avoidGhost(){
	NUMBER_EN = 1;
	Delay50us();
	DISPLAY=0xff;
  Delay50us();
	NUMBER_EN=0;
}