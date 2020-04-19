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

//Переменные кнопок
_Bool leftButtonStatus;
_Bool rightButtonStatus;
_Bool bothButtonStatus;

//шаги инициации
uint8_t* initStatus;
uint8_t* initStatusStep1;
uint8_t* initStatusStep2;
uint8_t* restoreStatusStep1;
uint8_t* restoreStatusStep2;

//шаги установки пароля
uint8_t* setPasswordStep1;
uint8_t* setPasswordStep2;

//шаги установки защиты
uint8_t* ProtectType;
uint8_t* setProtectTypeStep1;
uint8_t* setProtectTypeStep2;
uint8_t* passwordInputStatus;

//буферы
uint8_t dataReciveBufer[usbBuferSize];
int16_t bufer[20];
char bufer2[64];

//Данные
uint8_t DataCount;

//переменные команд
uint8_t* restoreStatus;
uint8_t* setPasswordStatus;
uint8_t* settingsStatus;
uint8_t* ResetComand;
uint8_t* chpassComand;
uint8_t* cProtectComand;

//переменные разрешений
uint8_t* exportEnable;
uint8_t* addDeviceEnable;
uint8_t* M5PCIDdefaultIsGetted;
uint8_t* isInit;
uint8_t* dataTransferEnable;

//переменные меню
uint8_t DataInfoMenu;
uint8_t* devpreinitmenu;
uint8_t* datasettingsStatus;
uint8_t* menuStatus;
uint8_t* settingsMenuStatus;
uint8_t* dataControlMenuStatus;

//Секретные ключи
int16_t privateKey[20];
int16_t publicKey[20];
char* passFrase[12];

//генератор рандоманых чисел
uint16_t RNGNumbers[12];

//хранение данных о надежных ПК
uint8_t M5PPCIDCount;
uint8_t PCIDOne[24];
uint8_t PCIDTwo[24];
uint8_t PCIDThre[24];
uint8_t PCIDFour[24];
uint8_t PCIDFive[24];
uint8_t PCIDbuf[24];
uint8_t PCIDSix[24];
uint8_t PCIDSeven[24];

typedef struct {
	char *login[16];
	char *password[16];
	char *url[16];
	char *number[16];
}accauntBlock;

typedef struct {
	int16_t pointer;
	accauntBlock *blocks;
}menuAB;

menuAB menu;
int8_t pointer;
int8_t Unlocked;
int8_t updownpointer;
uint8_t password[6];
uint8_t imputpassword[6];

uint8_t test[24];

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
void changePasswordData(void);
void generateRandomNumbers(uint16_t blocknumber,uint16_t filter);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
