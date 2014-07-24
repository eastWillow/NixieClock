#include <STC12C5A60S2.h>
//#include <DS1307.h>
#include <intrins.h>
//#include <I2C.h>
//#include <UART.h>
#define DISPLAY P0
#define NUMBER P2
#define ASCIIZERO 0x30
sbit NUMBER_EN = P1^3;
sbit HV_EN = P1^2;
void Delay100ms();
void main(void){
	char i=0;
	char scan[7]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
	NUMBER = 0x06;
	NUMBER_EN = 0;
	HV_EN = 0;
	//UartInit();
	while(1){
		for(i=0;i<6;i++){
		DISPLAY = scan[i];
		Delay100ms();
		}
		/*gotDS1307time();
		uartSend("Hour:",5,0);
		uartSendHex(ASCIIZERO+(time.hours>>4));
		uartSendHex(ASCIIZERO+(time.hours&0x0f));
		uartSend("Minutes:",8,0);
		uartSendHex(ASCIIZERO+(time.minutes>>4));
		uartSendHex(ASCIIZERO+(time.minutes&0x0f));
		uartSend("Seconds:",8,0);
		uartSendHex(ASCIIZERO+(time.seconds>>4));
		uartSendHex(ASCIIZERO+(time.seconds&0x0f));
		uartSend("",0,1);
		Delay500ms();*/
		
	}
}

void Delay100ms()		//@12.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 10;
	j = 82;
	do
	{
		while (--j);
	} while (--i);
}
