/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "TicPlay.h"
#include "multi_button.h"
#include "OLED.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define Motor_Pin GPIO_PIN_15
#define Motor_GPIO_Port GPIOC
#define TickLED_0_Pin GPIO_PIN_4
#define TickLED_0_GPIO_Port GPIOA
#define TickLED_1_Pin GPIO_PIN_5
#define TickLED_1_GPIO_Port GPIOA
#define TickLED_2_Pin GPIO_PIN_6
#define TickLED_2_GPIO_Port GPIOA
#define TickLED_3_Pin GPIO_PIN_7
#define TickLED_3_GPIO_Port GPIOA
#define StateLED_B_Pin GPIO_PIN_1
#define StateLED_B_GPIO_Port GPIOB
#define StateLED_G_Pin GPIO_PIN_10
#define StateLED_G_GPIO_Port GPIOB
#define StateLED_R_Pin GPIO_PIN_11
#define StateLED_R_GPIO_Port GPIOB
#define Btn1_Pin GPIO_PIN_9
#define Btn1_GPIO_Port GPIOA
#define SettingKey_Pin GPIO_PIN_12
#define SettingKey_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern uint8_t display_flag;
extern uint8_t Practice_TIM_Res_Flag;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
