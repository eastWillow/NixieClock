#ifndef _DS1307_
#define _DS1307_
#define DS1307_DEVICES_ADRESS 0xD0

#define DS1307_SECONDS 0x00
#define DS1307_MINUTES 0X01
#define DS1307_HOURS 0X02
#define DS1307_DAY 0x03
#define DS1307_DATE 0x04
#define DS1307_MONTH 0x05
#define DS1307_YEAR 0x06
#define DS1307_CONTROL 0x07
#define DS1307_RAMSTART 0x08
#define DS1307_RAMEND 0x3F
/*First Write TO Change Register Pointer
Then Read That Data*/
#endif
