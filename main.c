#include "stm8.h"
#include <string.h>
#include <stdint.h>
#define UART_SEND(data) while(!((UART1_SR)&(1<<7))); UART1_DR = data

unsigned int millis = 0;

void tim2_update(void) __interrupt(13)
{
	millis+=1;
	TIM2_SR1 &= ~1;
}

int uart_write(const char *str) {
    char i;
    for(i = 0; i < strlen(str); i++) {
        while(!(UART1_SR & UART_SR_TXE)); // !Transmit data register empty
        UART1_DR = str[i];
    }
    return(i); // Bytes sent
}

void init_uart()
{
	UART1_CR2 |= UART_CR2_TEN;
  UART1_BRR2 = 0x03; UART1_BRR1 = 0x68;
}

void init_tim2()
{
	TIM2_ARRH=0x3e;
	TIM2_ARRL=0x80;
	TIM2_IER|=1;
	TIM2_CR1|=1;
}

void init_i2c()
{
	I2C_FREQR=16;
	I2C_CCRL=0x50;
	I2C_TRISER=17;
	I2C_CR1=1;
}

void test_i2c()
{
	I2C_CR2|=1;
  while (!(I2C_SR1&1));
	I2C_DR=0x3C<<1;
	while (!(I2C_SR1&2));
	I2C_CR2=2;
  while (I2C_SR3&1);
	uart_write("hel\n\r");
}


void main()
{
	CLK_CKDIVR = 0;
	init_tim2();
	init_uart();
	init_i2c();
	enableInterrupts();
	int d;
	while(1)
	{
		d = millis;
		while(millis-d<2000);
		//test_i2c();
	}
}