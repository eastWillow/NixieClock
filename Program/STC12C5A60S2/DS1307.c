#include <STC12C5A60S2.h>
#include <DS1307.h>
#include <intrins.h>
#define DISPLAY P0
#define NUMBER P2
sbit SDA = P1^0;
sbit SCL = P1^1;
sbit NUMBER_EN = P1^3;
sbit HV_EN = P1^2;
void I2CStart(void);
void I2CEnd(void);
void I2CSendAck(bit ACK/*0 = ACK*/);
void I2CReceiveAck(void);
void I2CSendByte(unsigned char Data);
unsigned char I2CRecvByte(void);
void UartInit(void);
void uartSend (char *string,char len,char EOL);
char *uartReceive(char len);
void Delay5us();
void uartSendHex (unsigned char Data);
void Delay500ms();
void main(void){
	unsigned char buffer2;
	UartInit();
	while(1){
		I2CStart();
		I2CSendByte(DS1307_DEVICES_ADRESS);
		I2CSendByte(DS1307_SECONDS);
		I2CStart();
		I2CSendByte(DS1307_DEVICES_ADRESS+1);
		buffer2 = I2CRecvByte();
		I2CSendAck(1);
		I2CEnd();
		SBUF = buffer2;
		while(!TI);
		TI=0;
		Delay500ms();
	}
}
/*
I2C Time
SDA = data
delay
SCL = 1
delay
SCL = 0
delay
*/
void I2CStart(void){
	SDA = 1;
	SCL = 1;
	Delay5us();
	SDA = 0;
	Delay5us();
	SCL = 0;
	Delay5us();
}
void I2CEnd(void){
	SDA = 0;
	SCL = 1;
	Delay5us();
	SDA = 1;
	Delay5us();
}
void I2CSendAck(bit ACK/*0 = ACK*/){
	SDA = ACK;
	SCL = 1;
	Delay5us();
	SCL = 0;
	Delay5us();
}
void I2CReceiveAck(void){
	SCL = 1;
	Delay5us();
	//SDA = 1;
	while(SDA != 0);
	//ACK = SDA;
	SCL = 0;
	Delay5us();
}
void I2CSendByte(unsigned char Data){
	unsigned char i;
	for(i=1;i<9;i++){
		SDA = _crol_(Data,i)&0x01;
		SCL = 1;
		Delay5us();
		SCL = 0;
		Delay5us();
	}
	I2CReceiveAck();
}
unsigned char I2CRecvByte(void){
	unsigned char i;
	unsigned char buffer = 0;
	SDA = 1;
	for(i=0;i<8;i++){
		buffer = _crol_(buffer,1);
		SCL = 1;
		Delay5us();
		buffer = SDA | buffer;
		SCL = 0;
		Delay5us();
	}
	return buffer;
}
void UartInit(void)		//9600bps@12.000MHz
{
	PCON |= 0x80;		//Enable SMOD bit
	SCON = 0x50;		//8bit and variable baudrate
	AUXR |= 0x04;		//BRT's clock is Fosc (1T)
	BRT = 0xB2;		//Set BRT's reload value
	AUXR |= 0x01;		//Use BRT as baudrate generator
	AUXR |= 0x10;		//BRT running
}
void uartSend (char *string,char len,char EOL){
	unsigned char i;
	for(i=0;i<len;i++){
		SBUF = string[i];
		while(!TI);
		TI=0;
	}
	if(EOL == 1){
		SBUF = 0x0D;
		while(!TI);
		TI=0;
		SBUF = 0x0A;
		while(!TI);
		TI=0;
	}
}
void uartSendHex (unsigned char Data){
	SBUF = Data;
	while(!TI);
	TI=0;
}
char *uartReceive(char len){
	int i;
	static unsigned char string[10];
	for(i=0;i<len;i++){
		while(!RI);
		string[i]=SBUF;
		RI = 0;
	}
	return string;
}
void Delay5us()		//@12.000MHz
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
void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	i = 23;
	j = 205;
	k = 120;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
