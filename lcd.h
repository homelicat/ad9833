#include "charMap.h"

#define OLED_DISPLAY_OFF        0xAE
#define OLED_DISPLAY_ON         0xAF

#define OLED_COMMAND_MODE       0x00
#define OLED_ONE_COMMAND_MODE   0x80
#define OLED_DATA_MODE          0x40
#define OLED_ONE_DATA_MODE      0xC0

#define OLED_ADDRESSING_MODE    0x20
#define OLED_HORIZONTAL            0x00
#define OLED_VERTICAL           0x01

#define OLED_NORMAL_V            0xC8
#define OLED_FLIP_V                0xC0
#define OLED_NORMAL_H            0xA1
#define OLED_FLIP_H                0xA0

#define OLED_CONTRAST           0x81
#define OLED_SETCOMPINS           0xDA
#define OLED_SETVCOMDETECT        0xDB
#define OLED_CLOCKDIV             0xD5
#define OLED_SETMULTIPLEX        0xA8
#define OLED_COLUMNADDR            0x21
#define OLED_PAGEADDR            0x22
#define OLED_CHARGEPUMP            0x8D

#define OLED_NORMALDISPLAY        0xA6
#define OLED_INVERTDISPLAY        0xA7

void i2c_init()
{
	i2c->freqr=16;
	i2c->ccrl=0x50;
	i2c->triser=17;
	set(i2c->cr1,bit(0));
}

const uint8_t lcd_init_data[] = {
    OLED_DISPLAY_OFF,
    OLED_CLOCKDIV,
    0x80,    // value
    OLED_CHARGEPUMP,
    0x14,    // value
    OLED_ADDRESSING_MODE,
    2,
    OLED_NORMAL_H,
    OLED_NORMAL_V,
    OLED_CONTRAST,
    0x7F,    // value
    OLED_SETVCOMDETECT,
    0x40,     // value
    OLED_NORMALDISPLAY,
    OLED_DISPLAY_ON,
};

void lcd_send(char com,int siz,char * data)
{
	volatile char a = 0;
	//start
	set(i2c->cr2,bit(0));
	while (!(get(i2c->sr1,bit(0))));
	//addr
	i2c->dr=0x3C<<1;
	while (!(get(i2c->sr1,bit(1))));
	a+=i2c->sr1;
	a+=i2c->sr3;	
	//data
	i2c->dr=com?0:64;
	while(!(get(i2c->sr1,bit(7))));
	for(int i=0;i<siz;i++)
	{
		i2c->dr=data[i];
		while(!(get(i2c->sr1,bit(7))));
	}
	//stop
	set(i2c->cr2,bit(1));
	while (get(i2c->sr3,bit(0)));
}

void lcd_char(char c)
{
	lcd_send(0,5,charMap[c-32]);
	char a=0;	
	lcd_send(0,1,&a);
}

void lcd_str(char * s)
{
	int i =0;
	while(s[i]!=0)
	{
		lcd_char(s[i]);
		i++;
	}
}

void lcd_page(char p)
{
	p+=0xb0;
	lcd_send(1,1,&p);
	p=0;
	lcd_send(1,1,&p);
	p+=0x10;
	lcd_send(1,1,&p);
}

void lcd_clear()
{
	for (int j=0;j<8;j++)
	{
		lcd_page(j);
		for (int i =0;i<128;i++)
		{
			char a=0;
			lcd_send(0,1,&a);
		}
	}
}

void lcd_init()
{
	lcd_send(1,sizeof(lcd_init_data),lcd_init_data);
}
