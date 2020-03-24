#include "stm32f1xx.h"

int main()
{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);


  GPIO_InitTypeDef gpio;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIOC, &gpio);

 
  GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_9);

  do __NOP(); while (1); 
}