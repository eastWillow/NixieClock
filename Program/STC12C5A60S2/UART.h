#ifndef _UART_
#define _UART_
#include <UART.c>
extern void UartInit(void);
extern void uartSend (char *string,char len,char EOL);
void uartSendHex (unsigned char Data);
extern char *uartReceive(char len);
#endif