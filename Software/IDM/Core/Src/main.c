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
#include "data.h"
#include "stm32f2xx_it.h"
//#include "stdbool.h"
//#include "usbd_cdc_if.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */



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

TIM_HandleTypeDef htim6;

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
static void MX_TIM6_Init(void);
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
	leftButtonStatus=0;
	rightButtonStatus=0;
	bothButtonStatus=0;
	//endDataPointer=0;
	//startDataPointer=0;
	//dataReciveBufer[0]=(char)'t';
	//dataReciveBufer[1]=(char)'s';
	//endDataPointer=2;
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
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
   ssd1306_Init();
   ssd1306_Fill(White);
   ssd1306_UpdateScreen();
   ssd1306_Fill(Black);
   ssd1306_UpdateScreen();
   //пример записи в память


   //uint8_t wmsg[] ={'A','B','C'};
   //char rmsg[64]="a";
  // HAL_Delay(5000);
/*
   uint16_t memoryAddres = 0x1000;
   char inp1[64]="Dubinich1       Password1       habr1.ru        105             ";
   char inp2[64]="Dubinich2       Password2       habr2.ru        105             ";
   char inp3[64]="Dubinich3       Password3       habr3.ru        105             ";
   char inp4[64]="";
   writeToEeprom(memoryAddres, inp1,64);
   HAL_Delay(100);
   writeToEeprom(memoryAddres+64, inp2,64);
   HAL_Delay(100);
   writeToEeprom(memoryAddres+64+64, inp3,64);
   HAL_Delay(100);
   writeToEeprom(memoryAddres+64+64+64, inp4,64);
      HAL_Delay(100);
      */



   //writeToEeprom(memoryAddres, inp3,sizeof(wmsg));
/*
   HAL_Delay(100);
   //readFromEeprom(memoryAddres,rmsg,sizeof(wmsg));


   readFromEeprom(memoryAddres,inp1,64);
   HAL_Delay(100);
   readFromEeprom(memoryAddres+64,inp2,64);
   HAL_Delay(100);
   readFromEeprom(memoryAddres+64+64,inp3,64);
   HAL_Delay(100);

   CDC_Transmit_FS(inp3, 64);
      HAL_Delay(1000);

      CDC_Transmit_FS(inp2, 64);
         HAL_Delay(1000);

         CDC_Transmit_FS(inp1, 64);
            HAL_Delay(1000);

            */
   //--------------------
  // HAL_Delay(3000);
   /*
   accauntBlock tst;
   char* inpp="Dubinich        Password        habr.ru         105             ";
   stringToStruct(inpp, &tst);
   char out[64]="";
   structToString(&tst,out);
  // visualizeStruct(&tst);
   HAL_Delay(1000);

    //char* wmsgg="Dubinich        Password        habr.ru         105             ";
    char outpttt[64]="";
    writeToEeprom(memoryAddres, out,64);
    //structToMemory(&tst,memoryAddres);
    //ssd1306_UpdateScreen();
    readFromEeprom(memoryAddres,outpttt,64);
    HAL_Delay(100);
    CDC_Transmit_FS(outpttt, 64);
      HAL_Delay(1000);
    //memoryToStruct(&tst,memoryAddres);
    HAL_Delay(100);


   ssd1306_Fill(Black);
   ssd1306_UpdateScreen();
   HAL_Delay(300);
   ssd1306_SetCursor(0,10);
   ssd1306_WriteString("test", Font_7x10, White);
  // ssd1306_SetCursor(0,20);
   //ssd1306_WriteString(out, Font_7x10, White);
   //ssd1306_SetCursor(0,30);
   //ssd1306_WriteString(tst.url, Font_7x10, White);
   //ssd1306_SetCursor(0,40);
   //ssd1306_WriteString(tst.number, Font_7x10, White);
   //HAL_Delay(300);

   ssd1306_UpdateScreen();


   //HAL_Delay(10);
   //CDC_Transmit_FS(tst.login, sizeof(tst.login));
   //HAL_Delay(10);
   //CDC_Transmit_FS(tst.password, sizeof(tst.password));
   //HAL_Delay(10);
   //CDC_Transmit_FS(tst.url, sizeof(tst.url));
   //HAL_Delay(10);
   CDC_Transmit_FS(out, 64);
   HAL_Delay(1000);

   */


   /*
   HAL_Delay(100);
   CDC_Transmit_FS(wmsg, sizeof(wmsg));
   HAL_Delay(100);
   CDC_Transmit_FS("|", sizeof("|"));
   hcryp.Init.pKey = (uint32_t *)"test5";
        HAL_CRYP_Init(&hcryp);
        while(HAL_CRYP_GetState(&hcryp)!= HAL_CRYP_STATE_READY){}
        HAL_CRYP_Encrypt(&hcryp, (uint8_t*)wmsg, sizeof(wmsg),outp, 10);
        while(HAL_CRYP_GetState(&hcryp)!= HAL_CRYP_STATE_READY){}
       // HAL_CRYP_DeInit(&hcryp);
        HAL_Delay(100);
        CDC_Transmit_FS(outp, sizeof(outp));
        HAL_Delay(100);
        CDC_Transmit_FS("|", sizeof("|"));
        //HAL_CRYP_Init(&hcryp);
        while(HAL_CRYP_GetState(&hcryp)!= HAL_CRYP_STATE_READY){}
        HAL_CRYP_Decrypt(&hcryp, (uint8_t*)outp, sizeof(wmsg),	outpt, 10);
        while(HAL_CRYP_GetState(&hcryp)!= HAL_CRYP_STATE_READY){}
       // HAL_CRYP_DeInit(&hcryp);
        CDC_Transmit_FS(outpt, sizeof(outpt));
        HAL_Delay(100);
        CDC_Transmit_FS("|", sizeof("|"));

        ssd1306_SetCursor(0,40);
        ssd1306_WriteString(outpt, Font_7x10, White);
        HAL_Delay(300);
   ssd1306_UpdateScreen();*/
   //DES_ECB_Encrypt_Init();

   HAL_Delay(3000);
   initConstants();
   initMenu();
   HAL_Delay(3000);
   char inpt[64]="krakozabe       qwertyuii       4pda.ru         105             ";
      addDataBlock(inpt);
      HAL_Delay(3000);
      sendAllData();
   //updateScreen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    HAL_Delay(1000);
    if(dataReciveBufer!=0)
    {
    	//if(dataReciveBufer[])
    	CDC_Transmit_FS(dataReciveBufer, sizeof(dataReciveBufer));
    	for(uint32_t i=0;i<usbBuferSize;i++)
    	{
    		  dataReciveBufer[i]=0;
    	}
    }


   // CDC_Transmit_FS(wmsg, sizeof(wmsg));
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
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
	hcryp.Init.pKey = "test";
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
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 24000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 10;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin== GPIO_PIN_8&&!leftButtonStatus) {
		HAL_TIM_Base_Stop(&htim6);
		tim6_counter=0;
		leftButtonStatus=1;
		HAL_TIM_Base_Start(&htim6);
		HAL_TIM_Base_Start_IT(&htim6);
	}
	if(GPIO_Pin== GPIO_PIN_9&&!rightButtonStatus) {
		HAL_TIM_Base_Stop(&htim6);
		tim6_counter=0;
		rightButtonStatus=1;
		HAL_TIM_Base_Start(&htim6);
		HAL_TIM_Base_Start_IT(&htim6);
    }
	if(rightButtonStatus&&leftButtonStatus)
	{
		bothButtonStatus=1;
	}
}

void leftButtonActions()
{
	ssd1306_SetCursor(10,0);
	ssd1306_WriteString("L", Font_7x10, White);
	ssd1306_UpdateScreen();
	menu.pointer--;
	updateScreen();
}

void rightButtonActions()
{
	ssd1306_SetCursor(24,0);
	ssd1306_WriteString("R", Font_7x10, White);
	ssd1306_UpdateScreen();
	menu.pointer++;
    updateScreen();
	//endDataPointer++;
}

void bothButtonActions()
{
	ssd1306_SetCursor(17,0);
	ssd1306_WriteString("B", Font_7x10, White);
	ssd1306_UpdateScreen();
	//updateScreen();
}



void setInitStatus(uint8_t status)
{

}

void setPublicKey(char* status)
{

}

void setPrivateKey(char* status)
{

}

void setEmail(char* status)
{

}

void setNumber(uint16_t status)
{

}

void setPcId(uint16_t status)
{

}
void setPassword (uint16_t status)
{

}





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
