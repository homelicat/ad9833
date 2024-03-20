void spi_init()
{
	//set(gpio_c->ddr,bit(5)|bit(6));
	//set(gpio_c->cr1,bit(5)|bit(6));
	//set(gpio_c->cr2,bit(5)|bit(6));
	set(gpio_a->ddr,bit(1));
	set(gpio_a->cr1,bit(1));
	set(gpio_a->odr,bit(1));
	spi->cr1=0;
	spi->cr2=0;
	spi->cr1=bit(3)|bit(2)|bit(6);
	spi->cr2=0b11000011;
}

void spi_send(int siz, char * data)
{
	for (int i =0;i<siz;i++)
	{
		spi->dr=data[i];
		while(!(get(spi->sr,bit(1))));
	}
	while(get(spi->sr,bit(7)));
}

void spi_test()
{
	uint16_t cfg =(1<<13);
	spi_send(2,&cfg);
	lcd_char('a');
}

void ad_freq(uint32_t freq)
{
	set(spi->cr1,bit(6));
	reset(gpio_a->odr,bit(1));
	uint16_t cfg =(1<<13);
	spi_send(2,&cfg);
	uint16_t b;
	freq*=10.7374182f;
	b=0x4000+(freq&0x3fff);
	spi_send(2,&b);
	b=0x4000+(freq>>14);
	spi_send(2,&b);
	set(gpio_a->odr,bit(1));
	
}

void ad_reset()
{
	set(spi->cr1,bit(6));
	reset(gpio_a->odr,bit(1));
	uint16_t cfg =(1<<8);
	spi_send(2,&cfg);
	set(gpio_a->odr,bit(1));
	reset(spi->cr1,bit(6));
	
	ad_freq(1000);

	set(spi->cr1,bit(6));
	reset(gpio_a->odr,bit(1));
	cfg =0;
	spi_send(2,&cfg);
	set(gpio_a->odr,bit(1));
	reset(spi->cr1,bit(6));
}

void ad_cfg(char mode,uint32_t freq) //n s t p
{
	set(spi->cr1,bit(6));
	reset(gpio_a->odr,bit(1));
	uint16_t cfg =(1<<13);
	if(mode=='n')
	{
		cfg|=(1<<8);
	} else if(mode=='t')
	{
		cfg|=(1<<1);
	} else if(mode=='p')
	{
		cfg|=(1<<5)|(1<<3);
	}
	spi_send(2,&cfg);
	
	uint16_t b;
	freq&=0xfffffff;
	freq*=10.7374182f;
	b=0x4000+(freq&0x3fff);
	spi_send(2,&b);
	b=0x4000+(freq>>14);
	spi_send(2,&b);
	set(gpio_a->odr,bit(1));
	reset(spi->cr1,bit(6));
}