/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "fonts.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

CRYP_HandleTypeDef hcryp;
__ALIGN_BEGIN static const uint32_t pKeyCRYP[6] __ALIGN_END = {
                            0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000};

HASH_HandleTypeDef hhash;

I2C_HandleTypeDef hi2c1;

RNG_HandleTypeDef hrng;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRYP_Init(void);
static void MX_HASH_Init(void);
static void MX_I2C1_Init(void);
static void MX_RNG_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRYP_Init();
  MX_HASH_Init();
  MX_I2C1_Init();
  MX_RNG_Init();
  MX_CRC_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
   ssd1306_Init();
   ssd1306_Fill(Black);
   ssd1306_UpdateScreen();
   ssd1306_SetCursor(20,20);
   ssd1306_WriteString("test", Font_7x10, White);
   ssd1306_SetCursor(40,40);
   ssd1306_WriteString("word", Font_7x10, White);
   ssd1306_UpdateScreen();
   ssd1306_SetCursor(30,30);
   HAL_Delay(1000);

   const char wmsg[] = "Some data";
      char rmsg[sizeof(wmsg)]="a";
      // HAL expects address to be shifted one bit to the left
      uint16_t devAddr = (0x50 << 1);
      uint16_t memAddr = 0x0101;
      HAL_StatusTypeDef status;

      HAL_I2C_Mem_Write(&hi2c1, devAddr, memAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)wmsg, sizeof(wmsg), HAL_MAX_DELAY);
      for(;;) { // wait...
       status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1,HAL_MAX_DELAY);
       if(status == HAL_OK)
    	   ssd1306_SetCursor(25,25);
    	     ssd1306_WriteString(wmsg, Font_7x10, White);
                  break;
       }
      HAL_Delay(1000);

      HAL_I2C_Mem_Read(&hi2c1, devAddr, memAddr, I2C_MEMADD_SIZE_16BIT,(uint8_t*)rmsg, sizeof(rmsg), HAL_MAX_DELAY);
          if(memcmp(rmsg, wmsg, sizeof(rmsg)) == 0) {
              const char result[] = "Test passed!\r\n";
              ssd1306_SetCursor(0,0);
                ssd1306_WriteString(&result, Font_7x10, White);

          } else {
              const char result[] = "Test failed :(\r\n";

              ssd1306_SetCursor(0,0);
                ssd1306_WriteString(&result, Font_7x10, White);
          }
          HAL_Delay(1000);
   ssd1306_SetCursor(40,40);
   ssd1306_WriteString(&rmsg, Font_7x10, White);
   //ssd1306_SetCursor(50,50);
     // ssd1306_WriteString(10, Font_7x10, White);
     // ssd1306_WriteString(15, Font_7x10, White);
   ssd1306_UpdateScreen();
   /*
   uint8_t send_buff[] = "SPI WORKING!!! ";
    uint8_t dev_wr[1] = { 0b00000010 };
    uint8_t dev_rd[1] = { 0b00000011 };
    uint8_t dev_ress[1]= { 0x0202 };
    uint8_t dev_addr[1]= { 0x0202  };
    uint8_t deta[1]=    { 0b10101010 };

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
   HAL_StatusTypeDef res1 = HAL_SPI_Transmit(&hspi1, dev_wr, sizeof(dev_wr),HAL_MAX_DELAY);
   HAL_StatusTypeDef res2 = HAL_SPI_Transmit(&hspi1, dev_addr, sizeof(dev_addr),HAL_MAX_DELAY);
   HAL_StatusTypeDef res3 = HAL_SPI_Transmit(&hspi1, deta, sizeof(deta),HAL_MAX_DELAY);

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
   HAL_StatusTypeDef res4 = HAL_SPI_Transmit(&hspi1, dev_rd, sizeof(dev_rd),HAL_MAX_DELAY);
   HAL_StatusTypeDef res5 = HAL_SPI_Transmit(&hspi1, dev_addr, sizeof(dev_addr),HAL_MAX_DELAY);
   HAL_StatusTypeDef res6 = HAL_SPI_Receive(&hspi1, dev_ress, sizeof(dev_ress),HAL_MAX_DELAY);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

   if((res1 != HAL_OK) || (res2 != HAL_OK) || (res3 != HAL_OK) || (res4 != HAL_OK) || (res5 != HAL_OK) || (res6 != HAL_OK)) {
	   ssd1306_SetCursor(40,40);
	   ssd1306_WriteString(dev_ress, Font_7x10, White);
	   ssd1306_SetCursor(10,10);
	   ssd1306_WriteString("WRONG", Font_7x10, White);
	      ssd1306_UpdateScreen();
   }
   else
   {
	   ssd1306_SetCursor(10,10);
	   ssd1306_WriteString("OK", Font_7x10, White);
	   ssd1306_SetCursor(40,40);
	   ssd1306_WriteString(dev_ress, Font_7x10, White);
	   	      ssd1306_UpdateScreen();
   }*/
  /// HAL_StatusTypeDef res1, res2;
  // uint8_t devid_cmd[1] = { 0x9F };
   //uint8_t devid_res[5];
   //printf("Text\n\r");

/*

   FLASH->KEYR = FLASH_KEY1;
      FLASH->KEYR = FLASH_KEY2;



      FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

         FLASH->SR = 0xFFFFFFFF;
         FLASH->CR |= FLASH_CR_SER;
         FLASH->CR |= FLASH_CR_PSIZE_1; //2.7 - 3.6 V 0x10
         //FLASH->CR |= ((uint32_t)11 << FLASH_CR_SNB_Pos);
         FLASH->CR |=  FLASH_CR_SNB_1; //0x1011

         FLASH->CR |= FLASH_CR_STRT;
         while((FLASH->SR & FLASH_SR_BSY) == 1){};

         FLASH->CR = 0x80000000;

      while (FLASH->SR & FLASH_SR_BSY);
      FLASH->CR |= FLASH_CR_PG; //Разрешаем программирование флеша
      while (FLASH->SR & FLASH_SR_BSY);
      uint32_t addres=0x08000000;
      uint32_t data="test";
       *(__IO uint32_t*)addres = (uint32_t)data;
       while (FLASH->SR & FLASH_SR_BSY);
       FLASH->CR &= ~(FLASH_CR_PG); //Запрещаем программирование флеша
       FLASH->CR = 0x80000000;
*/

      // ssd1306_Fill(White);
       //ssd1306_UpdateScreen();

/*
   FLASH->KEYR = FLASH_KEY1;
   FLASH->KEYR = FLASH_KEY2;

   FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

   //FLASH->SR = 0xFFFFFFFF;
   FLASH->CR |= FLASH_CR_SER;
   FLASH->CR |= FLASH_CR_PSIZE_1; //2.7 - 3.6 V 0x10
   //FLASH->CR |= ((uint32_t)11 << FLASH_CR_SNB_Pos);
   FLASH->CR |= FLASH_CR_SNB_0; //0x1011

   FLASH->CR |= FLASH_CR_STRT;
   while((FLASH->SR & FLASH_SR_BSY) == 1){};

   FLASH->CR = 0x80000000;
*/


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_Delay(1000);
	     CDC_Transmit_FS(wmsg, sizeof(wmsg));
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief CRYP Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRYP_Init(void)
{

  /* USER CODE BEGIN CRYP_Init 0 */

  /* USER CODE END CRYP_Init 0 */

  /* USER CODE BEGIN CRYP_Init 1 */

  /* USER CODE END CRYP_Init 1 */
  hcryp.Instance = CRYP;
  hcryp.Init.DataType = CRYP_DATATYPE_32B;
  hcryp.Init.pKey = (uint32_t *)pKeyCRYP;
  hcryp.Init.Algorithm = CRYP_TDES_ECB;
  hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
  if (HAL_CRYP_Init(&hcryp) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRYP_Init 2 */

  /* USER CODE END CRYP_Init 2 */

}

/**
  * @brief HASH Initialization Function
  * @param None
  * @retval None
  */
static void MX_HASH_Init(void)
{

  /* USER CODE BEGIN HASH_Init 0 */

  /* USER CODE END HASH_Init 0 */

  /* USER CODE BEGIN HASH_Init 1 */

  /* USER CODE END HASH_Init 1 */
  hhash.Init.DataType = HASH_DATATYPE_32B;
  if (HAL_HASH_Init(&hhash) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN HASH_Init 2 */

  /* USER CODE END HASH_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
