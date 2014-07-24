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