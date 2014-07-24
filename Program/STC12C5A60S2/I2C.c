/*
I2C Time
SDA = data
delay
SCL = 1
delay
SCL = 0
delay
*/
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