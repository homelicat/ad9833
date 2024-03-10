struct
{
	uint8_t ickr;
	uint8_t eckr;
	uint8_t resv1;
	uint8_t cmsr;
	uint8_t swr;
	uint8_t swcr;
	uint8_t ckdivr;
	uint8_t pckenr1;
	uint8_t cssr;
	uint8_t ccor;
	uint8_t pckenr2;
	uint8_t hsitrimr;
	uint8_t swimccr;
} * clk = 0x50c0;

struct port
{
	uint8_t odr;
	uint8_t idr;
	uint8_t ddr;
	uint8_t cr1;
	uint8_t cr2;
};

struct port *gpio_a = 0x5000;
struct port *gpio_b = 0x5005;
struct port *gpio_c = 0x500a;
struct port *gpio_d = 0x500f;

struct
{
	uint8_t sr;
	uint8_t dr;
	uint8_t brr1;
	uint8_t brr2;
	uint8_t cr1;
	uint8_t cr2;
	uint8_t cr3;
	uint8_t cr4;
	uint8_t cr5;
	uint8_t gtr;
	uint8_t pscr;
} * uart = 0x5230;

struct
{
	uint8_t cr1;
	uint8_t cr2;
	uint8_t smcr;
	uint8_t etr;
	uint8_t ier;
	uint8_t sr1;
	uint8_t sr2;
	uint8_t egr;
	uint8_t ccmr1;
	uint8_t ccmr2;
	uint8_t ccmr3;
	uint8_t ccmr4;
	uint8_t ccer1;
	uint8_t ccer2;
	uint8_t cntrh;
	uint8_t cntrl;
	uint8_t pscrh;
	uint8_t pscrl;
	uint8_t arrh;
	uint8_t arrl;
	uint8_t rcr;
	uint8_t ccr1h;
	uint8_t ccr1l;
	uint8_t ccr2h;
	uint8_t ccr2l;
	uint8_t ccr3h;
	uint8_t ccr3l;
	uint8_t ccr4h;
	uint8_t ccr4l;
	uint8_t bkr;
	uint8_t dtr;
	uint8_t oisr;
} *tim1 = 0x5250;

struct
{
	uint8_t cr1;
	uint8_t cr2;
	uint8_t smcr;
	uint8_t ier;
	uint8_t sr1;
	uint8_t sr2;
	uint8_t egr;
	uint8_t ccmr1;
	uint8_t ccmr2;
	uint8_t ccmr3;
	uint8_t ccer1;
	uint8_t ccer2;
	uint8_t cntrh;
	uint8_t cntrl;
	uint8_t pscr;
	uint8_t arrh;
	uint8_t arrl;
	uint8_t ccr1h;
	uint8_t ccr1l;
	uint8_t ccr2h;
	uint8_t ccr2l;
	uint8_t ccr3h;
	uint8_t ccr3l;
} * tim2 = 0x5300;

struct
{
	uint8_t cr1;
	uint8_t cr2;
	uint8_t smcr;
	uint8_t ier;
	uint8_t sr;
	uint8_t egr;
	uint8_t cntr;
	uint8_t pscr;
	uint8_t arr;
} * tim4 = 0x5340;

struct
{
	uint8_t cr1;
	uint8_t cr2;
	uint8_t freqr;
	uint8_t oarl;
	uint8_t oarh;
	uint8_t;
	uint8_t dr;
	uint8_t sr1;
	uint8_t sr2;
	uint8_t sr3;
	uint8_t itr;
	uint8_t ccrl;
	uint8_t ccrh;
	uint8_t triser;
	uint8_t pecr;
} * i2c = 0x5210;

struct
{
	uint8_t sr;
} * rst = 0x50b3;

inline void nop() {__asm__("nop\n");}
inline void int_all() {__asm__("rim\n");}
inline void int_none() {__asm__("sim\n");}
inline void int_trap() {__asm__("trap\n");}
inline void int_wfi() {__asm__("wfi\n");}
inline void int_halt() {__asm__("halt\n");}

struct
{
	uint8_t cr1;
	uint8_t cr2;
} * exti = 0x50a0;

/*
Interrupts:

0 TLI
1 AWU Auto Wake up from Halt
2 CLK Clock controller
3 EXTI0 Port A external interrupts
4 EXTI1 Port B external interrupts
5 EXTI2 Port C external interrupts
6 EXTI3 Port D external interrupts
7 EXTI4 Port E external interrupts
8 CAN CAN RX interrupt
9 CAN CAN TX/ER/SC interrupt
10 SPI End of Transfer
11 TIM1 Update /Overflow/Underflow/Trigger/Break
12 TIM1 Capture/Compare
13 TIM2 Update /Overflow
14 TIM2 Capture/Compare
15 TIM3 Update /Overflow
16 TIM3 Capture/Compare
17 UART1 Tx complete
18 UART1 Receive Register DATA FULL
19 I2C I2C interrupt
20 UART2/3 Tx complete
21 UART2/3 Receive Register DATA FULL
22 ADC End of Conversion
23 TIM4 Update/Overflow
24 FLASH EOP/WR_PG_DIS
*/