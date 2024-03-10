#include <string.h>
#include <stdint.h>
#include "stm8.h"

#define F_MASTER 16000000UL
#define UART_BAUD(baud) uart->brr2 = (((F_MASTER/baud) & 0xF000)>>8)|((F_MASTER/baud) & 0x000F); uart->brr1 = ((F_MASTER/baud) >> 4) & 0x00FF
//#define UART_CHECK() (UART->SR&(1<<5))>0
#define UART_RECV() uart->dr
#define UART_SEND(data) while(!((uart->sr)&(1<<7))); uart->dr = data
#define GPIO_OUT(port,pin) port->ddr|=1<<pin
#define GPIO_IN(port,pin) port->ddr&=~(1<<pin)
#define GPIO_PULLUP(port,pin) port->cr1|=1<<pin
#define GPIO_FLOAT(port,pin) port->cr1&=~(1<<pin)
#define GPIO_FAST(port,pin) port->cr2|=1<<pin
#define GPIO_SLOW(port,pin) port->cr2&=~(1<<pin)
#define GPIO_INT(port,pin) port->cr2|=1<<pin
#define GPIO_NOINT(port,pin) port->cr2&=~(1<<pin)
#define GPIO_SET(port,pin,state) port->odr ^=((state>0)<<pin)
#define GPIO_GET(port,pin) ((port->idr&(1<<pin))>0)

unsigned int millis = 0;

void tim2_update(void) __interrupt(13)
{
	millis+=1;
	tim2->sr1 &= ~1;
}

void init_uart()
{
	uart->cr2 |= (1<<3);
	UART_BAUD(9600);
}

void init_tim2()
{
	tim2->arrh=0x3e;
	tim2->arrl=0x80;
	tim2->ier|=1;
	tim2->cr1|=1;
}

void init_i2c()
{
	i2c->freqr=16;
	i2c->ccrl=0x50;
	i2c->triser=17;
	i2c->cr1=1;
}

void test_i2c()
{
	i2c->cr2|=1;
  while (!(i2c->sr1&1));
	i2c->dr=0x3C<<1;
	while (!(i2c->sr1&2));
	i2c->cr2=2;
  while (i2c->sr3&1);
	//UART_SEND('b');
}


void main()
{
	clk->ckdivr = 0;
	init_tim2();
	init_uart();
	init_i2c();
	//int_all();
	int d;
	while(1)
	{
		d = millis;
		while(millis-d<2000);
		test_i2c();
	}
}