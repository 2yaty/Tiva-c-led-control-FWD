#include "../MCAL/SysTick/SysTick.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/NVIC/NVIC.h"

void GPIOF_Handler (void);


u32 volatile time_on= 1;
u32 volatile time_off = 1;
u8 volatile timeOn_turn = 1;


GPIO_PIN_ST led = {1 , PORTF , OUTPUT , 0};

GPIO_PIN_ST button1 = {0 , PORTF, INPUT , 0};
GPIO_PIN_ST button2 = {4 , PORTF, INPUT , 0};



void led_control (void){
	
	GPIO_pin_toggle(&led);
		
	if(timeOn_turn){
		
		SYSTICK_delay_m_callback(time_on * 1000, led_control);
		timeOn_turn = 0;
	}
	else {
		SYSTICK_delay_m_callback(time_off * 1000, led_control);
		timeOn_turn=1;
	}
}


int main(void){
	
	SYSTICK_init();
	
	GPIO_port_init(PORTF);
	
	
	GPIO_pin_init(&led);
	GPIO_pin_init(&button1);
	GPIO_pin_init(&button2);
	
	NVIC_SetInterrupt(NVIC_GPIO_PORTF);
	GPIO_pin_EN_interrupt(&button1 , 0 , 0 ,0);
	GPIO_pin_EN_interrupt(&button2 , 0 , 0 ,0);
	led_control();
	
	while(1);
}

void GPIOF_Handler (void){
	
	if(GPIO_get_interrupt_St(&button1)){
		
		GPIO_clr_interrupt_St(&button1 );
		time_on ++;
		time_off --;
		
	}	
	
	
	if(GPIO_get_interrupt_St(&button2)){

		
		GPIO_clr_interrupt_St(&button2 );
		time_on --;
		time_off ++;
	}
	
	
	if(!time_on){
		time_on = 1;
	}
	if(!time_off){
		time_off = 1;
	}
		

}





