/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define inUDS_ECHO_Pin GPIO_PIN_5
#define inUDS_ECHO_GPIO_Port GPIOA
#define outUDS_TRIG_Pin GPIO_PIN_6
#define outUDS_TRIG_GPIO_Port GPIOA
#define outGSM_DTR_Pin GPIO_PIN_7
#define outGSM_DTR_GPIO_Port GPIOA
#define inLORA_AUX_Pin GPIO_PIN_0
#define inLORA_AUX_GPIO_Port GPIOB
#define outLORA_M0_Pin GPIO_PIN_1
#define outLORA_M0_GPIO_Port GPIOB
#define outLORA_M1_Pin GPIO_PIN_2
#define outLORA_M1_GPIO_Port GPIOB
#define COMM_UART_TX_Pin GPIO_PIN_10
#define COMM_UART_TX_GPIO_Port GPIOB
#define COMM_UART_RX_Pin GPIO_PIN_11
#define COMM_UART_RX_GPIO_Port GPIOB
#define DEBUG_UART_TX_Pin GPIO_PIN_9
#define DEBUG_UART_TX_GPIO_Port GPIOA
#define DEBUG_UART_RX_Pin GPIO_PIN_10
#define DEBUG_UART_RX_GPIO_Port GPIOA
#define outSTATUS_LED_Pin GPIO_PIN_5
#define outSTATUS_LED_GPIO_Port GPIOB
#define I2C_EEPROM_SCL_Pin GPIO_PIN_6
#define I2C_EEPROM_SCL_GPIO_Port GPIOB
#define I2C_EEPROM_SDA_Pin GPIO_PIN_7
#define I2C_EEPROM_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
