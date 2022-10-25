#include "GPIO_test.h"
#include "SysTick.h"
#include "GPIO.h"
#include "NVIC.h"

//void led_off(void);
//void led_on (void);
void GPIOF_Handler (void);


u32 volatile time_on= 1000;
u32 volatile time_off = 1000;
//u8 volatile finished_on = 1 , finished_off = 1;

GPIO_PIN_ST led = {0 , PORTF , OUTPUT , 0};

GPIO_PIN_ST button1 = {1 , PORTF, INPUT , 0};
GPIO_PIN_ST button2 = {1 , PORTF, INPUT , 0};
/*
	
void led_off(void){
	finished_off = 0;

}

void led_on (void){
	finished_on = 0;
}
	*/
int main(void){
	
	SYSTICK_init();
	
	GPIO_port_init(PORTF);
	
	
	GPIO_pin_init(&led);
	GPIO_pin_init(&button1);
	GPIO_pin_init(&button2);
	
	NVIC_SetInterrupt(NVIC_GPIO_PORTF);
	GPIO_pin_EN_interrupt(&button1 , 0 , 0 ,1);
	GPIO_pin_EN_interrupt(&button2 , 0 , 0 ,1);
	
	while(1){
		
		GPIO_pin_write(&led,HIGH);
		SYSTICK_delay_m(time_on);
		GPIO_pin_write(&led,LOW);
		SYSTICK_delay_m(time_off);
		
				
		/*
		GPIO_pin_write(&led,HIGH);
		SYSTICK_delay_m_callback(time_on , led_on);
		
		while(finished_on);
			

		GPIO_pin_write(&led,LOW);
		SYSTICK_delay_m_callback(time_off , led_off);
		
		while(finished_off);
*/
	}
}

void GPIOF_Handler (void){
	u8 pushed = 0;
	GPIO_pin_read(&button1 , &pushed);
	if(pushed){
		time_on = 0;
		
		GPIO_pin_read(&button1 , &pushed);
		while(pushed){
			
			time_on ++;
		}
		time_on /= 16000;
	}	
	
	GPIO_pin_read(&button2 , &pushed);
		if(pushed){
		time_on = 0;
		GPIO_pin_read(&button2 , &pushed);
		while(pushed){
			
			time_off ++;
		}
		
		time_off /= 16000;
	
	}
		
	
}





