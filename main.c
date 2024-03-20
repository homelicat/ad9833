#include <stdint.h>
#include "stm8.h"
#include "lcd.h"
unsigned int millis = 0;
#include "ad9833.h"

#define BTN(a) bit(4-a)


char old=0;
char mode='n';
uint32_t freq=0;
char str[]="00000000";
int cur=0;

void tim2_int(void) __interrupt(13)
{
	millis+=1;
	reset(tim2->sr1,bit(0));
}

void tim2_init()
{
	tim2->arrh=0x3e;
	tim2->arrl=0x80;
	set(tim2->ier,bit(0));
	set(tim2->cr1,bit(0));
}

void gpio_init()
{
	set(gpio_d->cr1,bit(1)|bit(2)|bit(3));
}

void freq_str()
{
	uint32_t tmp = freq;
	for(int i =7;i>=0;i--)
	{
		str[i]=tmp%10+'0';
		tmp/=10;
	}
}

void main()
{
	clk->ckdivr = 0;
	gpio_init();
	tim2_init();
	i2c_init();
	int_all();
	lcd_init();
	lcd_clear();
		spi_init();
	spi_test();
	//ad_reset();
	while(1);
	/*
	freq_str();
	lcd_page(0);
	lcd_char(mode);
	lcd_str(str);
	lcd_page(1);
	for(int i =0;i<cur;i++)
	{
		lcd_char(' ');
	}
	lcd_char('^');
	for(int i =cur;i<20;i++)
	{
		lcd_char(' ');
	}
	
	while(1)
	{
		d=millis;
			old=gpio_d->idr;
			if(~(old|(~BTN(2))))
			{
				cur++;
				if(cur==9) cur=0;
				lcd_page(1);
				for(int i =0;i<cur;i++)
				{
					lcd_char(' ');
				}
				lcd_char('^');
				for(int i =cur;i<20;i++)
				{
					lcd_char(' ');
				}
				while(millis-d<200);
			} else if (~(old|(~(BTN(1)|BTN(3)))))
			{
				if(cur==0)
				{
					switch(mode)
					{
						case 'n':
						mode='s';
						break;
						case 's':
						mode='t';
						break;
						case 't':
						mode='p';
						break;
						case 'p':
						mode='n';
						break;
					}
				} else
				{
					int i=8-cur;
					uint32_t tmp=1;
					while(i-->0)tmp*=10;
					if(~(old|(~BTN(1))))
					{
						
						freq+=tmp;
					} else if (~(old|(~BTN(3))))
					{
						freq-=tmp;
					}
				}
				ad_cfg(mode,freq);
				freq_str();
				lcd_page(0);
				lcd_char(mode);
				lcd_str(str);
				while(millis-d<200);
			}
	}*/
}