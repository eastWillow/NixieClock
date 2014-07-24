void gotDS1307time (void){
	I2CStart();
	I2CSendByte(DS1307_DEVICES_ADRESS);
	I2CSendByte(DS1307_SECONDS);
	I2CStart();
	I2CSendByte(DS1307_DEVICES_ADRESS+1);
	time.seconds = I2CRecvByte();
	I2CSendAck(0);
	time.minutes = I2CRecvByte();
	I2CSendAck(0);
	time.hours = I2CRecvByte();
	I2CSendAck(0);
	time.day = I2CRecvByte();
	I2CSendAck(0);
	time.date = I2CRecvByte();
	I2CSendAck(0);
	time.month = I2CRecvByte();
	I2CSendAck(0);
	time.year = I2CRecvByte();
	I2CSendAck(1);
	I2CEnd();
}
void resetDS1307time(void){
	I2CStart();
	I2CSendByte(DS1307_DEVICES_ADRESS);
	I2CSendByte(DS1307_SECONDS);
	I2CSendByte(0x55);
	I2CSendByte(0x59);
	I2CSendByte(0x00);
	I2CEnd();
}
