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
__ALIGN_BEGIN static const uint32_t pKeyCRYP[6] __ALIGN_END = {
                            0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000};

HASH_HandleTypeDef hhash;

I2C_HandleTypeDef hi2c1;

RNG_HandleTypeDef hrng;

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */


uint16_t dictionarySeze=500;
char* wordsForPassFrase[] ={
		"aiken","durga","essen","evers","haiti","horus","issus","kamet","klimt","laius",
		"locke","lorre","lowry","mamet","marti","medea","niger","oates","potos","quito",
		"senor","turin","ushas","wells","aboil","acari","acoma","actin","adage","adeem",
		"adfix","adion","afore","agasp","aglet","alans","albin","algic","alody","amide",
		"ample","ancon","anker","annat","annie","anous","aoife","aotes","argil","aries",
		"arkab","arneb","artal","arvel","arzan","astay","atter","avoid","awash","axion",
		"axoid","ayond","bache","bahay","bajra","balai","baloo","bando","barbe","bayal",
		"beamy","becut","bedad","beget","belga","bemad","benne","betta","bezel","birle",
		"blast","blimp","bloat","bocal","bodge","bonny","boose","boral","bortz","bosom",
		"brass","bring","broll","buddy","bully","bushy","butch","cajun","canna","canoe",
		"carol","carse","carya","cased","casse","catti","celom","chaya","cheve","chips",
		"choel","claim","clary","claut","clava","cleek","cloot","clove","clump","coapt",
		"cobia","cobus","cogue","colla","comma","copsy","corps","covet","crash","cress",
		"creta","crete","croci","daffy","dafla","darer","deign","denda","dewey","diner",
		"dinus","disco","dixit","dizzy","domal","douar","dover","dreng","dropt","drown",
		"drunk","dural","dusun","easer","echis","elmer","elops","elute","elves","embed",
		"emcee","emmer","envoy","erian","erick","erose","erupt","every","exdie","fanon",
		"fanti","fanwe","fatal","favus","fedia","feint","fesse","fiard","finer","fiver",
		"flame","flare","flary","fleam","fleet","flesh","flong","foaly","fogle","forth",
		"fosse","found","freed","freit","fresh","fritt","frizz","fubsy","futon","gaine",
		"ganch","gatch","genin","genus","gipon","gippy","given","glaik","gland","glazy",
		"gledy","gloom","goban","golee","gorra","gourd","gouty","grail","grebo","gripy",
		"gugal","gypsy","habit","halse","harpa","herne","hevea","hocky","howso","humph",
		"ictic","iddat","idose","illth","imber","infer","inlaw","innet","input","irfan",
		"irone","itchy","jaman","jamie","jenny","jural","kafiz","kanji","kapai","kappe",
		"keleh","kench","khaya","khoja","kissy","klosh","known","kodro","kokio","krems",
		"lacer","lacet","lairy","lammy","larch","large","lever","ligas","lived","lobed",
		"loner","lotta","louey","lowth","lucan","luigi","lyard","maggy","mahdi","maidy",
		"mamma","manei","mapau","masty","mayan","mease","merak","merop","metal","metol",
		"miaul","mikie","minty","misty","moity","mossy","mourn","moyen","muffy","namda",
		"nanes","nanga","nasch","nasty","navar","nayar","nazir","nigre","niqab","niter",
		"norie","nunni","nuque","nyxis","oasal","oasis","ohmic","onymy","otary","oxbow",
		"oxlip","pacer","padre","padus","palar","palpi","parra","parse","parts","pasmo",
		"patly","peasy","peaty","pedal","peggy","pekan","penta","pesky","phase","pinko",
		"pinky","pinny","plaga","plaid","plica","plyer","pokom","pommy","poria","prase",
		"pudic","puppy","quart","quoit","raggy","raker","raman","raphe","rapic","rebid",
		"rebus","refan","renet","repew","resay","rewed","richt","rinse","rohob","rondo",
		"royal","runed","ryder","sabra","salma","samen","sanai","sandy","savor","schwa",
		"sclaw","scope","scout","scrim","segno","senci","septi","seral","sereh","serum",
		"seven","shahi","shiko","shire","shive","shoya","sided","sidth","sigeh","simar",
		"sinew","sirih","skank","skill","slent","slive","snafu","snake","sneap","spale",
		"spang","spece","sprig","squab","steri","stilt","stoff","stong","stosh","strag",
		"stree","strow","stunk","sturt","suant","suety","surfy","swile","swoop","tahil",
		"taich","taler","tangi","tanti","tanzy","taraf","techy","tellt","tenty","terce",
		"terse","tetum","thatn","thawy","thymy","tilde","titar","tizzy","toity","toned",
		"tongs","torah","torma","trill","trixy","trope","truck","tryst","tufty","tumor",
		"turco","uinal","unhad","unhid","unket","upend","urare","ureic","utick","vagas",
		"valve","vealy","vepse","vibex","vicar","virtu","volet","volva","vuggy","wabby",
		"walth","waltz","wamus","wawah","weaky","wendy","whalp","wheen","while","wined",
		"wings","wisse","words","wrack","wrive","xylon","yummy","zanze","ziega","zonta"
};




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
   generateRandomNumbers(12,0xf);
   ssd1306_UpdateScreen();
   HAL_Delay(10000);

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



   /*
   HAL_Delay(1000);
   initConstants();
   initMenu();
   HAL_Delay(1000);
   char inpt[64]="krakozabe       qwertyuii       4pda.ru         105             ";
   addDataBlock(inpt);
   HAL_Delay(1000);
   sendAllData();*/
   initConstants();
   initChoseProcess();

   //generatePassFrase();



   //updateScreen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
/*
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
*/

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
	if(menuStatus==1)
	{
		menu.pointer--;
		updateScreen();
	}
	if(initStatus==1)
	{
		initProcess1();

	}
	if(initStatusStep1==1){
		//initProcess1Next();
	}
	if(initStatusStep2==1){
		initStatus=1;
		initStatusStep2=0;
		initProcess1();
	}else if(setPasswordStep1==1){
		setPasswordProcess1Down();
	}
	else if(setPasswordStep2==1){
			setPasswordProcess1Down();
		}
	else if(restoreStatusStep1==1)
		{
		initStatus=1;
				restoreStatusStep1=0;
			initChoseProcess();
		}else if(setProtectTypeStep1==1)
		{
			setProtectTypeProcess1Down();
		}
		else if(settingsMenuStatus==1)
			{
			settingsMenuDown();
			}
		else if(dataControlMenuStatus==1)
				{
			dataControlMenuDown();
				}

}

void rightButtonActions()
{
	ssd1306_SetCursor(24,0);
	ssd1306_WriteString("R", Font_7x10, White);
	ssd1306_UpdateScreen();
	if(menuStatus==1)
	{
		menu.pointer++;
		updateScreen();
	}
	else if(initStatus==1)
	{
		restoreProcess1();
	}
	else if(initStatusStep1==1){
		//initProcess1Next();
	}
	else if(initStatusStep2==1){
			initProcess2Next();
	}else if(setPasswordStep1==1){
		setPasswordProcess1Up();
	}else if(setPasswordStep2==1){
		setPasswordProcess1Up();
	}
	else if(restoreStatusStep1==1)
		{
		initStatus=1;
				restoreStatusStep1=0;
			initChoseProcess();
		}else if(setProtectTypeStep1==1)
		{
			setProtectTypeProcess1Up();
		}
		else if(settingsMenuStatus==1)
			{
			 settingsMenuUp();
			}
		else if(dataControlMenuStatus==1)
				{
			dataControlMenuUp();
				}


	//endDataPointer++;
}

void bothButtonActions()
{
	ssd1306_SetCursor(17,0);
	ssd1306_WriteString("B", Font_7x10, White);
	ssd1306_UpdateScreen();
	//initProcess1();
	if(menuStatus==1)
	{
		chooseMainMenu();
	}
	else if(initStatus==1){
		//initProcess1();
    }
	else if(initStatusStep1==1){
		initProcess1Next();
	}
	else if(setPasswordStep1==1){
		setPasswordProcess1Next();
	}
	else if(setPasswordStep2==1){
			setPasswordProcess2Next();
		}
	else if(restoreStatusStep1==1)
	{
		initStatus=1;
		restoreStatusStep1=0;
		initChoseProcess();
	}
	else if(setProtectTypeStep1==1)
	{
		setProtectTypeProcess1Next();
	}
	else if(settingsMenuStatus==1)
	{
		settingsMenuSelect();
	}
	else if(dataControlMenuStatus==1)
		{
		dataControlMenuSelect();
		}
	//updateScreen();dataControlMenuStatus
}



void generatePassFrase()
{
	uint16_t num;
	generateRandomNumbers(500,0xfff);
	      for(int i=0;i<12;i++)
	      {
	    	  passFrase[i]=wordsForPassFrase[RNGNumbers[i]];
	      }

	      for(int i=0;i<12;i++)
	      {
	    	  CDC_Transmit_FS(passFrase[i], 5);
	    	  HAL_Delay(10);
	    	  CDC_Transmit_FS(" ", sizeof(" "));
	    	  HAL_Delay(10);
	      }
}

void generateRandomNumbers(uint16_t blocknumber,uint16_t filter)
{
	/*
	uint16_t dev=10;
	uint16_t count=1;

	while(blocknumber/dev>0)
	{
		dev=dev*10;
		count++;
	}*/
	_Bool isOk=0;
	for(uint16_t i=0;i<12;i++)
		{
		    RNGNumbers[i]=HAL_RNG_GetRandomNumber(&hrng)&filter;
		    //isOk=0;
		    while((RNGNumbers[i]>=blocknumber))
		    {
		    	RNGNumbers[i]=HAL_RNG_GetRandomNumber(&hrng)&filter;
		    	/*for(uint16_t j=0;j<i;j++)
		    	{
		    		if (RNGNumbers[i]==RNGNumbers[j])
		    		{
		    			isOk=0;
		    		}
		    		else
		    		{
		    			isOk=1;
		    		}

		    	}*/
		    }

	}
	for(uint16_t i=0;i<12;i++)
	{
		for(uint16_t j=0;j<i;j++)
		{
			while(RNGNumbers[i]==RNGNumbers[j]||(RNGNumbers[i]>=blocknumber))
			{
				RNGNumbers[i]=HAL_RNG_GetRandomNumber(&hrng)&filter;
			}
		}
	}

	for(uint16_t i=0;i<6;i++)
		{
		ssd1306_SetCursor(2,10+i*10);
		ssd1306_WriteStringUint(RNGNumbers[i], Font_7x10, White);
		ssd1306_SetCursor(72,10+i*10);
		ssd1306_WriteStringUint(RNGNumbers[i+6], Font_7x10, White);
	    }
	ssd1306_SetCursor(2,0);
	ssd1306_WriteStringUint(filter, Font_7x10, White);
	/*

	RNG[0]=HAL_RNG_GetRandomNumber(&hrng)&0x000001FF;*/
	//RNGNumbers[12];
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
