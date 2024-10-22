/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */
#define SettingKey_id 0
#define Btn1_id 1
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t App_State = 0;
struct Button Setting,Btn1;
uint8_t SettingFlag = 0,Setting_Next_Flag = 0;
uint8_t Btn1_AddFlag = 0,Value_Add_direction_flag = 1;
uint8_t display_flag = 0,Play_Flag = 1,Practice_Flag = 0;
uint8_t Practice_TIM_Res_Flag=0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display();
void display_Struct();
uint8_t State_Change_Check();
_Noreturn void Application();


uint8_t read_button_GPIO(uint8_t button_id)
{
    switch(button_id)
    {
        case SettingKey_id:
            return HAL_GPIO_ReadPin(SettingKey_GPIO_Port,SettingKey_Pin);
            break;
        case Btn1_id:
            return HAL_GPIO_ReadPin(Btn1_GPIO_Port,Btn1_Pin);
            break;
        default:
            return 0;
            break;
    }
}

void SettingKey_SINGLE_Click_Handler(void* btn)
{
    if(App_State == 1)
    {
        Setting_Next_Flag = 1;
    }
    else if(App_State == 0 || App_State==3)
    {
        Play_Flag = 0;
    }
    else if(App_State == 2 )
    {
        Play_Flag = 1;
    }
}
void SettingKey_DOUBLE_Click_Handler(void* btn)
{
    if(App_State !=0 && App_State !=1)return;
   if(SettingFlag == 0)
   {
       SettingFlag = 1;
//       OLED_Clear();
//       App_State = 1;
//       HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_2);
   }
   else
   {
       SettingFlag = 0;
//       OLED_Clear();
//       App_State = 0;
   }
}

void Btn1_SINGLE_Click_Handler(void* btn)
{

    if(App_State!=1)return;
    HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
    Btn1_AddFlag = 1;
}
void Btn1_LONG_PRESS_HOLD_Handler(void *btn)
{
    if(App_State!=1)return;
//    HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
    Btn1_AddFlag = 1;
}
void Btn1_DOUBLE_Click_Handler(void * btn)
{
    if(App_State == 1)
    {
        Value_Add_direction_flag = !Value_Add_direction_flag;
    }
    else if(App_State == 0 || App_State == 3)
    {
        Practice_Flag = 1;
    }
}
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
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

    button_init(&Setting,read_button_GPIO,1,SettingKey_id);
    button_attach(&Setting,SINGLE_CLICK,SettingKey_SINGLE_Click_Handler);
    button_attach(&Setting,DOUBLE_CLICK,SettingKey_DOUBLE_Click_Handler);

    button_start(&Setting);

    button_init(&Btn1,read_button_GPIO,1,Btn1_id);
    button_attach(&Btn1,SINGLE_CLICK,Btn1_SINGLE_Click_Handler);
    button_attach(&Btn1,LONG_PRESS_HOLD,Btn1_LONG_PRESS_HOLD_Handler);
    button_attach(&Btn1,DOUBLE_CLICK,Btn1_DOUBLE_Click_Handler);
    button_start(&Btn1);

    Tick_Init();
    HAL_TIM_Base_Start_IT(&htim3);

    OLED_Init();
    OLED_ShowString(2,5,"Hello");
    HAL_Delay(2000);
    OLED_Clear();
    Application();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

_Noreturn void Application()
{
    while (1)
    {
        static uint8_t star_flag = 0;
        switch(App_State){
            case 0:  //run
                if(star_flag == 0)
                {
//                    OLED_Clear();
                    SettingBuff[0] = Nc;
                    SettingBuff[1] = Nd;
                    SettingBuff[2] = BPM;
                    star_flag = 1;   //already
                    display_flag = 1;
                    time_flag = 1;
                    Practice_TIM_Res_Flag = 0;

                    HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_2);
                    HAL_GPIO_WritePin(StateLED_G_GPIO_Port,StateLED_G_Pin,GPIO_PIN_SET);
                    HAL_GPIO_WritePin(StateLED_B_GPIO_Port,StateLED_B_Pin,GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(StateLED_R_GPIO_Port,StateLED_R_Pin,GPIO_PIN_RESET);
                    continue;
                }
                if(SettingFlag == 1)
                {
                    App_State = 1;
                    SettingFlag = 0;
                    continue;
                }

                if(Play_Flag == 0)
                {
                    App_State = 2;
                    continue;
                }
                if(Practice_Flag)
                {
                    App_State = 3;
                    Practice_Flag = 0;
                    continue;
                }

                break;
            case 1:   //setting
                time_flag = 0; //stop counting time
                HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_2);
                if(SettingFlag == 1)
                {
//                    OLED_Clear();
                    setTick(SettingBuff[0],SettingBuff[1],SettingBuff[2]);

                    App_State = 0;
                    SettingFlag = 0;
                }
                if(Setting_Next_Flag )
                {
                    Setting_FixIndex++;
                    Setting_FixIndex%=5;
                    Setting_Next_Flag = 0;
//                    OLED_Clear();
                }
                if(Btn1_AddFlag == 1)
                {
                    switch (Setting_FixIndex) {
                        case 0:
                            if(Value_Add_direction_flag)
                            {
                                SettingBuff[Setting_FixIndex]++;
                                if(SettingBuff[Setting_FixIndex]>16)
                                {
                                    SettingBuff[Setting_FixIndex] = 1;
                                }
                            }
                            else
                            {
                                SettingBuff[Setting_FixIndex]--;
                                if(SettingBuff[Setting_FixIndex]==0)
                                {
                                    SettingBuff[Setting_FixIndex] = 16;
                                }
                            }

                            break;
                        case 1:
                            if(Value_Add_direction_flag)
                            {
                                SettingBuff[Setting_FixIndex] =  SettingBuff[Setting_FixIndex] << 1;
                                if( SettingBuff[Setting_FixIndex] > 16)
                                {
                                    SettingBuff[Setting_FixIndex] = 2;
                                }
                            }
                            else
                            {
                                SettingBuff[Setting_FixIndex] =  SettingBuff[Setting_FixIndex] >> 1;
                                if( SettingBuff[Setting_FixIndex] < 2)
                                {
                                    SettingBuff[Setting_FixIndex] = 16;
                                }
                            }
                            break;
                        case 2:
                            if(Value_Add_direction_flag)
                            {
                                SettingBuff[Setting_FixIndex]++;
                                if( SettingBuff[Setting_FixIndex] >=400)
                                {
                                    SettingBuff[Setting_FixIndex] = 400;
                                }
                            }
                            else
                            {
                                SettingBuff[Setting_FixIndex]--;
                                if( SettingBuff[Setting_FixIndex] <=20)
                                {
                                    SettingBuff[Setting_FixIndex] = 20;
                                }
                            }

                            break;
                        case 3:
                            if(Value_Add_direction_flag)
                            {

                                SettingBuff[3]++;
                                SettingBuff[3] %= SettingBuff[0];
//                                if( SettingBuff[Setting_FixIndex] > SettingBuff[0])
//                                {
//                                    SettingBuff[Setting_FixIndex] = 1;
//                                }
                            }
                            else
                            {
                                if( SettingBuff[3] <=0)
                                {
                                    SettingBuff[3] = SettingBuff[0]-1;
                                }
                                else
                                {
                                    SettingBuff[3]--;
                                }

                            }
                            SettingBuff[4] = PlayQueueMode[SettingBuff[3]];
                            break;
                        case 4:
                            if(Value_Add_direction_flag)
                            {
                                SettingBuff[4]++;
                                SettingBuff[4]%=3;
                            }
                            else
                            {
                                if(SettingBuff[4] > 0)
                                {
                                    SettingBuff[4]--;
                                }
                               else
                                {
                                   SettingBuff[4]=2;
                                }

                            }
                            PlayQueueMode[SettingBuff[3]] = SettingBuff[4];
                            break;
                    }


                    HAL_GPIO_WritePin(StateLED_R_GPIO_Port,StateLED_R_Pin,GPIO_PIN_SET);
                    HAL_Delay(5);
                    HAL_GPIO_WritePin(StateLED_R_GPIO_Port,StateLED_R_Pin,GPIO_PIN_RESET);
                    Btn1_AddFlag = 0;


                }

                HAL_GPIO_WritePin(StateLED_B_GPIO_Port,StateLED_B_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(StateLED_R_GPIO_Port,StateLED_R_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(StateLED_G_GPIO_Port,StateLED_G_Pin,GPIO_PIN_RESET);

                star_flag = 0;  //prepare
                break;
            case 2:
                time_flag = 0; //stop counting time
                if(Play_Flag == 1)
                {
                    if(star_flag)
                    {
                        App_State = 0;
                        star_flag = 0;  //prepare
                    }
                    else
                    {
                        App_State = 3;
//                        OLED_Clear();
                        HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_2);
                    }
                    continue;
                }

                HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_2);
                HAL_GPIO_WritePin(StateLED_R_GPIO_Port,StateLED_R_Pin,GPIO_PIN_SET);

                HAL_GPIO_WritePin(StateLED_B_GPIO_Port,StateLED_B_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(StateLED_G_GPIO_Port,StateLED_G_Pin,GPIO_PIN_RESET);

                break;
            case 3:
                if(Practice_Flag)
                {
                    Practice_Flag = 0;
                    App_State = 0;

                    continue;
                }
                if(!Play_Flag)
                {
                    App_State = 2;
                    continue;
                }
                star_flag = 0; //pre
                time_flag = 1;
                if(Sec%6==0 && Sec_Clear_flag)
                {
                    Sec_Clear_flag = 0;
                    Practice_TIM_Res_Flag = !Practice_TIM_Res_Flag;
                }

                HAL_GPIO_WritePin(StateLED_R_GPIO_Port,StateLED_R_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(StateLED_B_GPIO_Port,StateLED_B_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(StateLED_G_GPIO_Port,StateLED_G_Pin,GPIO_PIN_SET);

                break;
            default: //stop

                HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_2);
                star_flag = 0;  //prepare
                break;
        }

        if(State_Change_Check()==1)
        {
            if(App_State != 2)
            {
                OLED_Clear();
            }
            display_Struct();
        }
        if(display_flag || App_State==1)
        {
            display_flag = 0;
            display();
        }
    }

}
void display_Struct()
{
    if(App_State == 0 || App_State == 3)
    {
        OLED_ShowNum(1,1,Nc,2);
        OLED_ShowChar(1,3,'/');
        OLED_ShowNum(1,4,Nd,2);
        OLED_ShowString(2,1,"BPM:");
        OLED_ShowNum(2,5,BPM,3);

        OLED_ShowString(4,1,"pt:");
        OLED_ShowNum(4,4,Hour,2);
        OLED_ShowString(4,6,"h");
        OLED_ShowNum(4,8,Min,2);
        OLED_ShowString(4,10,"m");
        OLED_ShowNum(4,12,Sec,2);
        OLED_ShowString(4,14,"s");
    }
    else if(App_State == 1)
    {
        OLED_ShowNum(1,1,SettingBuff[0],2);
        OLED_ShowChar(1,3,'/');
        OLED_ShowNum(1,4,SettingBuff[1],2);
        OLED_ShowString(2,1,"BPM:");
        OLED_ShowNum(2,5,SettingBuff[2],3);
        OLED_ShowString(4,1,"Key:");
        OLED_ShowNum(4,5,SettingBuff[3]+1,2);
        OLED_ShowString(4,9,"pitch:");
        OLED_ShowChar(4,16,Str_pitch[SettingBuff[4]]);
        if(Value_Add_direction_flag)
        {
            OLED_ShowChar(3,14,'+');
        }
        else
        {
            OLED_ShowChar(3,14,'-');
        }
        switch (Setting_FixIndex) {
            case 0:
                OLED_ShowString(1,12,"  Nc ");
                break;
            case 1:
                OLED_ShowString(1,12,"  Nd ");
                break;
            case 2:
                OLED_ShowString(1,12,"  BPM");
                break;
            case 3:
                OLED_ShowString(1,12,"  Key");
                break;
            case 4:
                OLED_ShowString(1,12,"pitch");
        }
    }
    else if(App_State == 2)
    {
        OLED_ShowString(1,14,"||");
    }

}
void display()
{
    if((App_State == 0) || (App_State == 3))
    {
//        OLED_ShowNum(1,1,Nc,2);
//        OLED_ShowChar(1,3,'/');
//        OLED_ShowNum(1,4,Nd,2);
//        OLED_ShowString(2,1,"BPM:");
//        OLED_ShowNum(2,5,BPM,3);
//
//        OLED_ShowString(4,1,"pt:");
        OLED_ShowNum(4,4,Hour,2);
//        OLED_ShowString(4,6,"h");
        OLED_ShowNum(4,8,Min,2);
//        OLED_ShowString(4,10,"m");
        OLED_ShowNum(4,12,Sec,2);
//        OLED_ShowString(4,14,"s");


    }
    else if(App_State == 1)
    {
        OLED_ShowNum(1,1,SettingBuff[0],2);
//        OLED_ShowChar(1,3,'/');
        OLED_ShowNum(1,4,SettingBuff[1],2);
//        OLED_ShowString(2,1,"BPM:");
        OLED_ShowNum(2,5,SettingBuff[2],3);
//        OLED_ShowString(4,1,"Key:");
        OLED_ShowNum(4,5,SettingBuff[3]+1,2);
//        OLED_ShowString(4,9,"pitch:");
        OLED_ShowChar(4,16,Str_pitch[SettingBuff[4]]);
        if(Value_Add_direction_flag)
        {
            OLED_ShowChar(3,14,'+');
        }
        else
        {
            OLED_ShowChar(3,14,'-');
        }
        switch (Setting_FixIndex) {
            case 0:
                OLED_ShowString(1,12,"  Nc ");
                break;
            case 1:
                OLED_ShowString(1,12,"  Nd ");
                break;
            case 2:
                OLED_ShowString(1,12,"  BPM");
                break;
            case 3:
                OLED_ShowString(1,12,"  Key");
                break;
            case 4:
                OLED_ShowString(1,12,"pitch");
        }
    }
//    else if(App_State == 2)
//    {
//        OLED_ShowString(1,14,"||");
//    }


}

uint8_t State_Change_Check()
{
    static uint8_t OldState=255;
    if(OldState != App_State)
    {
        OldState = App_State;
        return 1;
    }
    else
        return 0;
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
