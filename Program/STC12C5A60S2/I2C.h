#ifndef _I2C_
#define _I2C_
sbit SDA = P1^0;
sbit SCL = P1^1;
#include <intrins.h>
#include <I2C.c>
extern void I2CStart(void);
extern void I2CEnd(void);
extern void I2CSendAck(bit ACK/*0 = ACK*/);
extern void I2CReceiveAck(void);
extern void I2CSendByte(unsigned char Data);
extern void Delay5us();
extern unsigned char I2CRecvByte(void);
#endif