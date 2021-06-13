//Where is the LED connected?  You can find in Nucleo board reference manual
//Port: A
//Pin: 5
#define PERIPH_BASE       (0x40000000UL)   //UL: unsigned long (starting point)
#define AHB1PERIPH_OFFSET (0x00020000UL) // =0x0200000
#define AHB1PERIPH_BASE   (PERIPH_BASE + AHB1PERIPH_OFFSET)
//0x4000 0000 + 0x0002 0000 = 0x40020000 (GPIOA address: 0x40020000)
#define GPIOA_OFFSET      (0x0000UL)  //= 0x 0000 0000
#define GPIOA_BASE        (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET        (0x3800UL)
#define RCC_BASE          (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET   (0x30UL)
#define RCC_AHB1EN_R      (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET     (0x00UL)
#define GPIOA_MODE_R      (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET       (0x14UL)
#define GPIOA_OD_R        (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN           (1U<<0) // 0b0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5              (1U<<5)
#define LED_PIN           (PIN5)
/*  to set mode to OUTPUT mode for GPIOA
(1U<<10): set bit10 to 1 without changing other states
&=~(1U<<11): set bit11 to 0 without changing other states
*/
int main()
{
	/* 1. Enable clock access to GPIOA */
	RCC_AHB1EN_R  |= GPIOAEN;


	/* 2. Set PA5 as output PIN */
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &= ~(1U<<11);

	while(1){
		/* 3. Set PA5 HIGH*/
		//GPIOA_OD_R  |= LED_PIN;

		/* 4. experiment 2: toggle PA5 */
		GPIOA_OD_R  ^= LED_PIN;

		for (int i=0; i<150000;i++);
	}

}
