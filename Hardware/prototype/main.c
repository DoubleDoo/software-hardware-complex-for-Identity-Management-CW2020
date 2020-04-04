
#include "stm32f1xx.h"
//#include <stdbool.h>
//STM32F103C6 

int val=1;
int test_count=0;


void PortInit(void)
{
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
  SET_BIT(RCC->APB2ENR, RCC_APB1ENR_I2C1EN);

  
  SET_BIT(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI0_PB);
  
  

  MODIFY_REG(GPIOC->CRH,0x00,(0x02 << GPIO_CRH_MODE13_Pos));
  MODIFY_REG(GPIOC->CRH,0x00,(0x00 << GPIO_CRH_CNF13_Pos));
  MODIFY_REG(GPIOC->BSRR,0x00,(1<<13));

  
  GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0); 
  GPIOB->CRL |= (0x02 << GPIO_CRL_MODE0_Pos) | (0x01 << GPIO_CRL_CNF0_Pos);
  
  
  NVIC_SetPriority(TIM2_IRQn, 15);
  NVIC_SetPriority(EXTI0_IRQn , 14);
  NVIC_EnableIRQ(TIM2_IRQn);
  NVIC_EnableIRQ(EXTI0_IRQn);
  
  TIM2->PSC = 8000 - 1;
  TIM2->ARR = 1000 - 1;
  TIM2->DIER |= TIM_DIER_UIE;
  TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
  

  
  EXTI->RTSR |= EXTI_RTSR_TR0;
  EXTI->FTSR |= EXTI_RTSR_TR0;
  EXTI->IMR |= EXTI_IMR_MR0;
  
}



void OFF(void)
{
  printf("HI\r\n"); 
  MODIFY_REG(GPIOC->BSRR,0x00,(1<<13));
}
 
void ON(void)
{
  printf("LOW\r\n"); 
  MODIFY_REG(GPIOC->BRR,0x00,(1<<13));
}

void TIM2_IRQHandler(void)
{
  TIM2->SR &= ~TIM_SR_UIF;  
   printf("Tick!\r\n"); 
		if (test_count == 0)
		{
			OFF();
		}
		else if (test_count == 3)
		{ 
			ON();
		}
		if (++test_count >= 5)
			test_count = 0;

}

void EXTI0_IRQHandler(void)
{
  EXTI->PR = EXTI_PR_PR0;
        if (val>0)
        {
          ON();
          val=-1;
        }
        else
        {
          OFF();
          val=1;
        }
        
}

void main()
{
  int i;
  printf("Start\r\n"); 
  PortInit();
  for(;;){}
}