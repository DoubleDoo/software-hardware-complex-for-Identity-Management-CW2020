/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "fonts.h"
#include "stm32f2xx_it.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define usbBuferSize 128
#define usbBlockSize 64
_Bool leftButtonStatus;
_Bool rightButtonStatus;
_Bool bothButtonStatus;
_Bool isUSBBusy;
char* passFrase[12];

uint16_t* isInit;
uint16_t* initStatus;
uint16_t* initStatusStep1;
uint16_t* initStatusStep2;
uint16_t* restoreStatusStep1;
uint16_t* restoreStatusStep2;

uint16_t* setPasswordStep1;
uint16_t* setPasswordStep2;

uint16_t* ProtectType;
uint16_t* setProtectTypeStep1;
uint16_t* setProtectTypeStep2;

uint16_t* settingsMenuStatus;

uint16_t* dataControlMenuStatus;

uint16_t* menuStatus;
uint16_t* restoreStatus;
uint16_t* setPasswordStatus;
uint16_t* settingsStatus;
uint16_t* datasettingsStatus;
uint8_t dataReciveBufer[usbBuferSize];

uint16_t RNGNumbers[12];

//uint16_t startDataPointer;
//uint16_t endDataPointer;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void leftButtonActions(void);

void rightButtonActions(void);

void bothButtonActions(void);
void generatePassFrase(void);
void generateRandomNumbers(uint16_t blocknumber,uint16_t filter);


void printCounter(uint16_t i);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
