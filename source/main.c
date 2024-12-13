#include <stddef.h>
#include "MKE16Z4.h"
#include "my_gpio.h"
#include "clock_config.h"
#include "my_lpit.h"
/*-------------Define------------------*/
#define LED_PORT PORTB
#define LED_GPIO GPIOB
#define gLED_PIN 4
#define rLED_PIN 5
#define bLED_PIN 1


#define SW_PORT PORTD
#define SW_GPIO GPIOD
#define SW_PIN 2  //sw3

volatile uint32_t g_systickCounter;
volatile uint8_t g_mutex=1;

volatile uint8_t mode=1;
#define toggleMode() (mode = (mode==1)?2:1)
/*--------------- Prototype -----------------*/
void mode1();
void mode2();
void initGPIO();
void enableClock();
void turnOffAll();
void lpitCallback();
void SysTick_DelayTicks(uint32_t);
void buttonCallback(PORT_Type *port,uint8_t pin);

/*-------------------- MAIN -------------------*/
int main(void) {
	enableClock();
	initGPIO();
	// init sys tick
	if (SysTick_Config(SystemCoreClock / 1000U))
	{
	    while (1) {}  // Error handling, stay here if SysTick fails
	}

	// auto toggle led with timer lpit
	LPIT_init(lpitCallback);
	LPIT_Delay(1000);
	LPIT_StartTimer(0);


	while(1){
		if(mode==1){
			mode1();
		}else{
			mode2();
		}
	}


	return 0;

}

/*--------------- Function -----------------*/
void lpitCallback(){
	toggleMode();
}
void buttonCallback(PORT_Type *port,uint8_t pin){
	if(port == SW_PORT && pin == SW_PIN){
		toggleMode();
	}
	return;
}
void turnOffAll(){
	  GPIO_WritePin(LED_GPIO, gLED_PIN, GPIO_HIGH);  // Green LED OFF
	  GPIO_WritePin(LED_GPIO, rLED_PIN, GPIO_HIGH);   // Red LED OFF
	  GPIO_WritePin(LED_GPIO, bLED_PIN, GPIO_HIGH);   // Blue LED OFF

}
void mode1(){
	/* Mode 1: Green and Red LEDs blink concurrently with T = 200ms*/
    GPIO_WritePin(LED_GPIO, gLED_PIN, GPIO_LOW); // Green LED ON
    GPIO_WritePin(LED_GPIO, rLED_PIN, GPIO_LOW); // Red LED ON
    SysTick_DelayTicks(200);

    GPIO_WritePin(LED_GPIO, gLED_PIN, GPIO_HIGH);  // Green LED OFF
    GPIO_WritePin(LED_GPIO, rLED_PIN, GPIO_HIGH);   // Red LED OFF
    SysTick_DelayTicks(200);

}
void mode2(){
    /* Mode 2: Green LED and Red LED alternate with T = 200ms*/
    GPIO_WritePin(LED_GPIO, gLED_PIN, GPIO_LOW); // Green LED ON
    GPIO_WritePin(LED_GPIO, rLED_PIN, GPIO_HIGH);  // Red LED OFF
    SysTick_DelayTicks(200);

    GPIO_WritePin(LED_GPIO, gLED_PIN, GPIO_HIGH);  // Green LED OFF
    GPIO_WritePin(LED_GPIO, rLED_PIN, GPIO_LOW); // Red LED ON
    SysTick_DelayTicks(200);
}

void initGPIO(){
	/* LED configuration (Green, Red, Blue)*/
	PortConfig_t ledPortConfig = {LED_PORT, gLED_PIN, PULL_DISABLE, ISF_DISABLED};
	GPIOConfig_t ledConfig = {LED_GPIO, OUTPUT, GPIO_HIGH, NULL};

	PortConfig_t redLedPortConfig = {LED_PORT, rLED_PIN, PULL_DISABLE, ISF_DISABLED};
	GPIOConfig_t redLedConfig = {LED_GPIO, OUTPUT, GPIO_HIGH, NULL};

	PortConfig_t blueLedPortConfig = {LED_PORT, bLED_PIN, PULL_DISABLE, ISF_DISABLED};
	GPIOConfig_t blueLedConfig = {LED_GPIO, OUTPUT, GPIO_HIGH, NULL};

	/* Initialize GPIO for LEDs*/
	GPIO_Init(&ledPortConfig, &ledConfig);
	GPIO_Init(&redLedPortConfig, &redLedConfig);
	GPIO_Init(&blueLedPortConfig, &blueLedConfig);

	/* Button (SW) configuration*/
	PortConfig_t swPortConfig = {SW_PORT, SW_PIN, PULL_UP, ISF_FALLING_EDGE};
	GPIOConfig_t swConfig = {SW_GPIO, INPUT, GPIO_HIGH, buttonCallback};

	/* Initialize GPIO for button*/
	GPIO_Init(&swPortConfig, &swConfig);

}
void enableClock(){
	PCC->CLKCFG[PCC_PORTA_INDEX] |= PCC_CLKCFG_CGC(1); /*enable port A for Button*/
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1); /*enable port B for Button*/
	PCC->CLKCFG[PCC_PORTC_INDEX] |= PCC_CLKCFG_CGC(1); /*enable port C for Button*/

	PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CLKCFG_CGC(1); /*enable port D for RGB LED*/
	PCC->CLKCFG[PCC_PORTE_INDEX] |= PCC_CLKCFG_CGC(1); /*enable port E for Button*/
}

/* SysTick Handler */
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
    //GPIO_TogglePin(LED_GPIO, gLED_PIN);
}

/* SysTick Delay function */
void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}
