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
#include "data.h"

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
__ALIGN_BEGIN static const uint32_t pKeyCRYP[6] __ALIGN_END = { 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

HASH_HandleTypeDef hhash;

I2C_HandleTypeDef hi2c1;

RNG_HandleTypeDef hrng;

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */

uint16_t dictionarySeze = 500;
char *wordsForPassFrase[] = { "aiken", "durga", "essen", "evers", "haiti",
		"horus", "issus", "kamet", "klimt", "laius", "locke", "lorre", "lowry",
		"mamet", "marti", "medea", "niger", "oates", "potos", "quito", "senor",
		"turin", "ushas", "wells", "aboil", "acari", "acoma", "actin", "adage",
		"adeem", "adfix", "adion", "afore", "agasp", "aglet", "alans", "albin",
		"algic", "alody", "amide", "ample", "ancon", "anker", "annat", "annie",
		"anous", "aoife", "aotes", "argil", "aries", "arkab", "arneb", "artal",
		"arvel", "arzan", "astay", "atter", "avoid", "awash", "axion", "axoid",
		"ayond", "bache", "bahay", "bajra", "balai", "baloo", "bando", "barbe",
		"bayal", "beamy", "becut", "bedad", "beget", "belga", "bemad", "benne",
		"betta", "bezel", "birle", "blast", "blimp", "bloat", "bocal", "bodge",
		"bonny", "boose", "boral", "bortz", "bosom", "brass", "bring", "broll",
		"buddy", "bully", "bushy", "butch", "cajun", "canna", "canoe", "carol",
		"carse", "carya", "cased", "casse", "catti", "celom", "chaya", "cheve",
		"chips", "choel", "claim", "clary", "claut", "clava", "cleek", "cloot",
		"clove", "clump", "coapt", "cobia", "cobus", "cogue", "colla", "comma",
		"copsy", "corps", "covet", "crash", "cress", "creta", "crete", "croci",
		"daffy", "dafla", "darer", "deign", "denda", "dewey", "diner", "dinus",
		"disco", "dixit", "dizzy", "domal", "douar", "dover", "dreng", "dropt",
		"drown", "drunk", "dural", "dusun", "easer", "echis", "elmer", "elops",
		"elute", "elves", "embed", "emcee", "emmer", "envoy", "erian", "erick",
		"erose", "erupt", "every", "exdie", "fanon", "fanti", "fanwe", "fatal",
		"favus", "fedia", "feint", "fesse", "fiard", "finer", "fiver", "flame",
		"flare", "flary", "fleam", "fleet", "flesh", "flong", "foaly", "fogle",
		"forth", "fosse", "found", "freed", "freit", "fresh", "fritt", "frizz",
		"fubsy", "futon", "gaine", "ganch", "gatch", "genin", "genus", "gipon",
		"gippy", "given", "glaik", "gland", "glazy", "gledy", "gloom", "goban",
		"golee", "gorra", "gourd", "gouty", "grail", "grebo", "gripy", "gugal",
		"gypsy", "habit", "halse", "harpa", "herne", "hevea", "hocky", "howso",
		"humph", "ictic", "iddat", "idose", "illth", "imber", "infer", "inlaw",
		"innet", "input", "irfan", "irone", "itchy", "jaman", "jamie", "jenny",
		"jural", "kafiz", "kanji", "kapai", "kappe", "keleh", "kench", "khaya",
		"khoja", "kissy", "klosh", "known", "kodro", "kokio", "krems", "lacer",
		"lacet", "lairy", "lammy", "larch", "large", "lever", "ligas", "lived",
		"lobed", "loner", "lotta", "louey", "lowth", "lucan", "luigi", "lyard",
		"maggy", "mahdi", "maidy", "mamma", "manei", "mapau", "masty", "mayan",
		"mease", "merak", "merop", "metal", "metol", "miaul", "mikie", "minty",
		"misty", "moity", "mossy", "mourn", "moyen", "muffy", "namda", "nanes",
		"nanga", "nasch", "nasty", "navar", "nayar", "nazir", "nigre", "niqab",
		"niter", "norie", "nunni", "nuque", "nyxis", "oasal", "oasis", "ohmic",
		"onymy", "otary", "oxbow", "oxlip", "pacer", "padre", "padus", "palar",
		"palpi", "parra", "parse", "parts", "pasmo", "patly", "peasy", "peaty",
		"pedal", "peggy", "pekan", "penta", "pesky", "phase", "pinko", "pinky",
		"pinny", "plaga", "plaid", "plica", "plyer", "pokom", "pommy", "poria",
		"prase", "pudic", "puppy", "quart", "quoit", "raggy", "raker", "raman",
		"raphe", "rapic", "rebid", "rebus", "refan", "renet", "repew", "resay",
		"rewed", "richt", "rinse", "rohob", "rondo", "royal", "runed", "ryder",
		"sabra", "salma", "samen", "sanai", "sandy", "savor", "schwa", "sclaw",
		"scope", "scout", "scrim", "segno", "senci", "septi", "seral", "sereh",
		"serum", "seven", "shahi", "shiko", "shire", "shive", "shoya", "sided",
		"sidth", "sigeh", "simar", "sinew", "sirih", "skank", "skill", "slent",
		"slive", "snafu", "snake", "sneap", "spale", "spang", "spece", "sprig",
		"squab", "steri", "stilt", "stoff", "stong", "stosh", "strag", "stree",
		"strow", "stunk", "sturt", "suant", "suety", "surfy", "swile", "swoop",
		"tahil", "taich", "taler", "tangi", "tanti", "tanzy", "taraf", "techy",
		"tellt", "tenty", "terce", "terse", "tetum", "thatn", "thawy", "thymy",
		"tilde", "titar", "tizzy", "toity", "toned", "tongs", "torah", "torma",
		"trill", "trixy", "trope", "truck", "tryst", "tufty", "tumor", "turco",
		"uinal", "unhad", "unhid", "unket", "upend", "urare", "ureic", "utick",
		"vagas", "valve", "vealy", "vepse", "vibex", "vicar", "virtu", "volet",
		"volva", "vuggy", "wabby", "walth", "waltz", "wamus", "wawah", "weaky",
		"wendy", "whalp", "wheen", "while", "wined", "wings", "wisse", "words",
		"wrack", "wrive", "xylon", "yummy", "zanze", "ziega", "zonta" };

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
int main(void) {
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
	MX_TIM6_Init();
	/* USER CODE BEGIN 2 */
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();
	HAL_Delay(1000);
	initConstants();
	HAL_Delay(1000);
	if (isInit == 0) {
		deviceIsntInit();
	}

	else {
		if (ProtectType == 0) {
			menuStatus = 1;
			initMenu();
		} else if (ProtectType == 1) {

			setPasswordStep2 = 1;
			passwordInputStatus = 1;
			setPasswordProcess2();
		} else if (ProtectType == 2) {
			//
			menuStatus = 1;
			initMenu();
		} else if (ProtectType == 3) {
			//
			setPasswordStep2 = 1;
			passwordInputStatus = 1;
			setPasswordProcess2();
		}

	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		HAL_Delay(300);
		if (dataReciveBufer[0] != 0) {
			//начать инициацию

			if (dataReciveBufer[0] == 'P') {

				if (M5PCIDdefaultIsGetted == 0) {
					for (uint32_t i = 2; i < 27; i++) {
						PCIDOne[i - 2] = dataReciveBufer[i];
					}
					writeToEeprom(0x0300, &PCIDOne, 24);
					M5PPCIDCount = 1;
					uploadPCIDcount();
					//M5PPCIDCount = 1;
					//MD5PCID[0] = PCIDt;
					//ssd1306_SetCursor(2,10);
					//ssd1306_WriteString(PCIDt, Font_7x10, White);
					//uploadPCIDcount();

					//uploadPCIDmas();

					//uploadIsfirstPC();
					//PCIDt="";
					//MD5PCID[0] = "test";
					//ssd1306_SetCursor(2,20);
					//ssd1306_WriteString(MD5PCID[0], Font_7x10, White);

					//downloadPCIDcount();
					//downloadPCIDmas();

					//ssd1306_SetCursor(2,30);
					//ssd1306_WriteString(MD5PCID[0], Font_7x10, White);
					M5PCIDdefaultIsGetted = 1;					//
					uploadIsfirstPC();					//
					initStatus = 1;
					initChoseProcess();
					CDC_Transmit_FS("OK", 2);
					//ssd1306_UpdateScreen();
					//HAL_Delay(2000);
					//ssd1306_SetCursor(2,10);
					//ssd1306_WriteString(MD5PCID[0], Font_7x10, White);
					//downloadPCIDmas() ;

				} else if (addDeviceEnable == 1) {

					if (M5PPCIDCount < 5) {
						for (uint32_t i = 2; i < 27; i++) {
							PCIDbuf[i - 2] = dataReciveBufer[i];
						}
						//writeToEeprom(0x0300,&PCIDOne ,24);
						if (PCIDbuf != PCIDOne && PCIDbuf != PCIDTwo
								&& PCIDbuf != PCIDThre && PCIDbuf != PCIDFour
								&& PCIDbuf != PCIDFive) {
							if (M5PPCIDCount == 1) {
								writeToEeprom(0x0300 + 24, &PCIDTwo, 24);
							} else if (M5PPCIDCount == 2) {
								writeToEeprom(0x0300 + 48, &PCIDThre, 24);
							} else if (M5PPCIDCount == 3) {
								writeToEeprom(0x0300 + 72, &PCIDFour, 24);
							} else if (M5PPCIDCount == 4) {
								writeToEeprom(0x0300 + 96, &PCIDFive, 24);
							}
							M5PPCIDCount++;
							uploadPCIDcount();
							CDC_Transmit_FS("OK", 2);
						} else {
							CDC_Transmit_FS("PC already exist", 16);
						}

						addDeviceEnable = 0;
						uploadaddDeviceEnable();

					} else {
						CDC_Transmit_FS("No more space for PC", 27);
					}
				} else {
					for (uint32_t i = 2; i < 27; i++) {
						PCIDbuf[i - 2] = dataReciveBufer[i];
					}
					if (PCIDbuf == PCIDOne || PCIDbuf == PCIDTwo
							|| PCIDbuf == PCIDThre || PCIDbuf == PCIDFour
							|| PCIDbuf == PCIDFive) {
						CDC_Transmit_FS("OK", 2);
						initStatus = 1;
						initChoseProcess();
						//
					} else {
						initStatus = 1;
						initChoseProcess();
						CDC_Transmit_FS("OK", 18);					//
					}

				}

			}

			//добавить идент. данные
			if (dataReciveBufer[0] == 'N') {
				char str[64] = "";
				uint8_t pasgen[37] = "";
				uint8_t domen[16];
				for (uint32_t i = 0; i < 16; i++) {
					str[i] = dataReciveBufer[i + 18];
					domen[i] = dataReciveBufer[i + 18];
				}
				downloadPrivate();
				//uint8_t pasgen[37];
				for (int i = 0; i < 20; i++) {
					pasgen[i] = privateKey[i];
				}
				for (int i = 20; i < 36; i++) {
					pasgen[i] = dataReciveBufer[i - 2];
				}
				pasgen[16] = (uint8_t) privateKey
						& (uint8_t) domen + (uint8_t) 1;
				HAL_HASH_Init(&hhash);
				HAL_HASH_SHA1_Start(&hhash, &pasgen, 36, &bufer, HAL_MAX_DELAY);
				HASH_Finish(&hhash, &bufer, HAL_MAX_DELAY);
				char pass[16];
				for (int i = 0; i < 16; i++) {
					pass[i] = bufer[i];
					bufer[i] = 0;
				}

				for (uint32_t i = 16; i < 32; i++) {
					str[i] = pass[i - 16];
				}
				for (uint32_t i = 32; i < 48; i++) {
					str[i] = dataReciveBufer[i - 30];
				}
				char iter[16] = "1               ";
				for (uint32_t i = 48; i < 64; i++) {
					str[i] = iter[i - 48];
				}
				//str[0]=DataCount;
				writeToEeprom(0x1000 + DataCount * 64, str, 64);
				DataCount++;
				uploadDataCount();
				accauntBlock blocksbuf[DataCount + 1];
				for (uint16_t i = 0; i < DataCount; i++) {

					readFromEeprom(0x1000 + 64 * i, bufer2, 64);
					stringToStruct(&bufer2, &blocksbuf[i]);
				}
				menu.blocks = blocksbuf;
				sconstants.blockscount = DataCount;
				CDC_Transmit_FS(str, 64);

			}
			//импорт
			if (dataReciveBufer[0] == 'I') {
				CDC_Transmit_FS("OK", 2);
				if (exportEnable == 1) {
					HAL_Delay(300);
					sendAllData();
				}
			}
			//сброс
			if (dataReciveBufer[0] == 'C') {
				//clearDevice();
				clearDevice();
				deviceIsntInit();
				CDC_Transmit_FS("OK", 2);
			}
			//добавить безопасный ПК
			if (dataReciveBufer[0] == 'A') {
				addDeviceEnable = 1;
				uploadaddDeviceEnable();
				// downloadaddDeviceEnable(); uploadaddDeviceEnable();
				CDC_Transmit_FS("OK", 2);
			}

			for (uint32_t i = 0; i < usbBuferSize; i++) {
				dataReciveBufer[i] = 0;
			}
		} else {
			//	ssd1306_SetCursor(2,2);
			// 	ssd1306_WriteString("0", Font_7x10, White);
			//	ssd1306_UpdateScreen();
		}

	}

	/*
	 if(dataReciveBufer[0]==(uint8_t)"P")
	 {
	 PCReciveProces=1;
	 ssd1306_SetCursor(2,2);
	 ssd1306_WriteString(dataReciveBufer, Font_7x10, White);
	 ssd1306_UpdateScreen();
	 }
	 //CDC_Transmit_FS(dataReciveBufer, sizeof(dataReciveBufer));
	 //for(uint32_t i=0;i<usbBuferSize;i++)
	 //{
	 //	  dataReciveBufer[i]=0;
	 //}
	 }
	 //if(PCReciveProces==1)
	 //{
	 // 	CDC_Transmit_FS("OK", 2);
	 // 	HAL_Delay(100);
	 // 	PCReciveProces=0;
	 // }
	 // ssd1306_SetCursor(2,2);
	 //   			   ssd1306_WriteString(&dataReciveBufer, Font_7x10, White);
	 // 			   ssd1306_UpdateScreen();


	 // CDC_Transmit_FS(wmsg, sizeof(wmsg));
	 // }
	 /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void) {

	/* USER CODE BEGIN CRC_Init 0 */

	/* USER CODE END CRC_Init 0 */

	/* USER CODE BEGIN CRC_Init 1 */

	/* USER CODE END CRC_Init 1 */
	hcrc.Instance = CRC;
	if (HAL_CRC_Init(&hcrc) != HAL_OK) {
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
static void MX_CRYP_Init(void) {

	/* USER CODE BEGIN CRYP_Init 0 */
	hcryp.Init.pKey = "test";
	/* USER CODE END CRYP_Init 0 */

	/* USER CODE BEGIN CRYP_Init 1 */

	/* USER CODE END CRYP_Init 1 */
	hcryp.Instance = CRYP;
	hcryp.Init.DataType = CRYP_DATATYPE_32B;
	hcryp.Init.pKey = (uint32_t*) pKeyCRYP;
	hcryp.Init.Algorithm = CRYP_TDES_ECB;
	hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
	if (HAL_CRYP_Init(&hcryp) != HAL_OK) {
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
static void MX_HASH_Init(void) {

	/* USER CODE BEGIN HASH_Init 0 */

	/* USER CODE END HASH_Init 0 */

	/* USER CODE BEGIN HASH_Init 1 */

	/* USER CODE END HASH_Init 1 */
	hhash.Init.DataType = HASH_DATATYPE_8B;
	if (HAL_HASH_Init(&hhash) != HAL_OK) {
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
static void MX_I2C1_Init(void) {

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
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
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
static void MX_RNG_Init(void) {

	/* USER CODE BEGIN RNG_Init 0 */

	/* USER CODE END RNG_Init 0 */

	/* USER CODE BEGIN RNG_Init 1 */

	/* USER CODE END RNG_Init 1 */
	hrng.Instance = RNG;
	if (HAL_RNG_Init(&hrng) != HAL_OK) {
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
static void MX_TIM6_Init(void) {

	/* USER CODE BEGIN TIM6_Init 0 */

	/* USER CODE END TIM6_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM6_Init 1 */

	/* USER CODE END TIM6_Init 1 */
	htim6.Instance = TIM6;
	htim6.Init.Prescaler = 24000;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 10;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig)
			!= HAL_OK) {
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
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pins : PC8 PC9 */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_8 && !leftButtonStatus) {
		HAL_TIM_Base_Stop(&htim6);
		tim6_counter = 0;
		leftButtonStatus = 1;
		HAL_TIM_Base_Start(&htim6);
		HAL_TIM_Base_Start_IT(&htim6);
	}
	if (GPIO_Pin == GPIO_PIN_9 && !rightButtonStatus) {
		HAL_TIM_Base_Stop(&htim6);
		tim6_counter = 0;
		rightButtonStatus = 1;
		HAL_TIM_Base_Start(&htim6);
		HAL_TIM_Base_Start_IT(&htim6);
	}
	if (rightButtonStatus && leftButtonStatus) {
		bothButtonStatus = 1;
	}
}

void leftButtonActions() {
//	ssd1306_SetCursor(10, 0);
//	ssd1306_WriteString("L", Font_7x10, White);
//	ssd1306_UpdateScreen();
	if (menuStatus) {
		menu.pointer--;
		updateScreen();
	} else if (initStatus) {
		initProcess1();
	} else if (initStatusStep1) {
		//initProcess1Next();
	} else if (initStatusStep2) {
		initStatus = 1;
		initStatusStep2 = 0;
		initProcess1();
	} else if (setPasswordStep1) {
		setPasswordProcess1Down();
	} else if (setPasswordStep2) {
		setPasswordProcess1Down();
	} else if (restoreStatusStep1) {
		initStatus = 1;
		restoreStatusStep1 = 0;
		initChoseProcess();
	} else if (setProtectTypeStep1) {
		setProtectTypeProcess1Down();
	} else if (settingsMenuStatus) {
		settingsMenuDown();
	} else if (dataControlMenuStatus) {
		dataControlMenuDown();
	} else if (ResetComand) {
		settingsMenuStatus = 1;
		ResetComand = 0;
		settingsMenu();
	} else if (exportEnable) {
		exportEnable = 0;
		settingsMenuStatus = 1;

		settingsMenu();
	} else if (DataInfoMenu) {
		DataInfoMenu = 0;
		settingsMenuStatus = 1;
		settingsMenu();
	}
}

void rightButtonActions() {
//	ssd1306_SetCursor(24, 0);
//	ssd1306_WriteString("R", Font_7x10, White);
//	ssd1306_UpdateScreen();
	if (menuStatus) {
		menu.pointer++;
		updateScreen();
	} else if (initStatus) {
		restoreProcess1();
	} else if (initStatusStep1) {
		//initProcess1Next();
	} else if (initStatusStep2) {
		initProcess2Next();
	} else if (setPasswordStep1) {
		setPasswordProcess1Up();
	} else if (setPasswordStep2) {
		setPasswordProcess1Up();
	} else if (restoreStatusStep1) {
		initStatus = 1;
		restoreStatusStep1 = 0;
		initChoseProcess();
	} else if (setProtectTypeStep1) {
		setProtectTypeProcess1Up();
	} else if (settingsMenuStatus) {
		settingsMenuUp();
	} else if (dataControlMenuStatus) {
		dataControlMenuUp();
	} else if (ResetComand) {
		settingsMenuStatus = 0;
		ResetComand = 0;
		clearDevice();
		deviceIsntInit();
	} else if (exportEnable) {
		exportEnable = 0;
		settingsMenuStatus = 1;

		settingsMenu();
	} else if (DataInfoMenu) {
		DataInfoMenu = 0;
		settingsMenuStatus = 1;

		settingsMenu();
	}
	//endDataPointer++;
}

void bothButtonActions() {
	//ssd1306_SetCursor(17, 0);
//	ssd1306_WriteString("B", Font_7x10, White);
	//ssd1306_UpdateScreen();
	//initProcess1();
	if (menuStatus) {
		chooseMainMenu();
	} else if (initStatus) {
		//initProcess1();
	} else if (initStatusStep1) {
		initProcess1Next();
	} else if (setPasswordStep1) {
		setPasswordProcess1Next();
	} else if (setPasswordStep2) {
		setPasswordProcess2Next();
	} else if (restoreStatusStep1) {
		initStatus = 1;
		restoreStatusStep1 = 0;
		initChoseProcess();
	} else if (setProtectTypeStep1) {
		setProtectTypeProcess1Next();
	} else if (settingsMenuStatus) {
		settingsMenuSelect();
	} else if (dataControlMenuStatus) {
		dataControlMenuSelect();
	} else if (ResetComand) {

	} else if (exportEnable) {
		exportEnable = 0;
		settingsMenuStatus = 1;

		settingsMenu();
	} else if (DataInfoMenu) {
		DataInfoMenu = 0;
		settingsMenuStatus = 1;
		settingsMenu();
	}
}

void generatePassFrase() {
	uint16_t num;
	uint16_t bfstr[60];
	generateRandomNumbers(500, 0xfff);
	for (int i = 0; i < 12; i++) {
		passFrase[i] = wordsForPassFrase[RNGNumbers[i]];
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {
			bfstr[i * 5 + j] = passFrase[i][j];
		}
	}
	HAL_HASH_Init(&hhash);
	HAL_HASH_SHA1_Start(&hhash, &bfstr, 60, &privateKey, HAL_MAX_DELAY);
	HASH_Finish(&hhash, &privateKey, HAL_MAX_DELAY);
	HAL_HASH_DeInit(&hhash);
	HAL_HASH_Init(&hhash);
	HAL_HASH_SHA1_Start(&hhash, &privateKey, 60, &publicKey, HAL_MAX_DELAY);
	HASH_Finish(&hhash, &publicKey, HAL_MAX_DELAY);
	HAL_HASH_DeInit(&hhash);
/*	CDC_Transmit_FS("      ", sizeof("      "));
	HAL_Delay(1000);
	CDC_Transmit_FS(privateKey, 20);
	HAL_Delay(1000);
	CDC_Transmit_FS("      ", sizeof("      "));
	HAL_Delay(1000);
	CDC_Transmit_FS(publicKey, 20);
	HAL_Delay(1000);*/
	uploadPrivate();
	uploadadPublic();
}

void generateRandomNumbers(uint16_t blocknumber, uint16_t filter) {
	uint16_t j = 0;
	for (uint16_t i = 0; i < 12; i++) {
		RNGNumbers[i] = HAL_RNG_GetRandomNumber(&hrng) & filter;
		//isOk=0;
		while ((RNGNumbers[i] >= blocknumber)) {
			RNGNumbers[i] = HAL_RNG_GetRandomNumber(&hrng) & filter;
		}

	}
	for (uint16_t i = 0; i < 12; i++) {
		j = 0;
		while (j < i) {
			if (RNGNumbers[i] == RNGNumbers[j]
					|| (RNGNumbers[i] >= blocknumber)) {
				RNGNumbers[i] = HAL_RNG_GetRandomNumber(&hrng) & filter;
				j = 0;
			} else
				j++;
		}
	}
}

void changePasswordData() {
	char buf[64] = "abc";
	uint8_t pasgen[37] = "";
	uint8_t domen[16];
	uint8_t num;
	readFromEeprom(0x1000 + 64 * (menu.pointer), buf, 64);
	for (int i = 0; i < 16; i++) {
		domen[i] = buf[i];
	}
	num = (uint8_t) buf[48];
	num++;
	buf[48] = num;
	pasgen[16] = (uint8_t) privateKey & (uint8_t) domen + (uint8_t) num;
	HAL_HASH_Init(&hhash);
	HAL_HASH_SHA1_Start(&hhash, &pasgen, 36, &bufer, HAL_MAX_DELAY);
	HASH_Finish(&hhash, &bufer, HAL_MAX_DELAY);
	//writeToEeprom(startaddressfordata + 64 *(i-1), buf,64);

	for (uint16_t i = 16; i < 32; i++) {
		buf[i] = pasgen[i - 16];
	}
	writeToEeprom(0x1000 + 64 * (menu.pointer), buf, 64);
	stringToStruct(&buf, &menu.blocks[menu.pointer]);
	menuStatus = 1;
	dataControlMenuStatus = 0;
	updateScreen();

}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
