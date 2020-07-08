/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "stdio.h"
#include "KeyBoard.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId KEY_SCANHandle;
osThreadId KEY_MENUHandle;
osMessageQId keyNumHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void KeyScanTask02(void const * argument);
void Key_MenuTask03(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of keyNum */
  osMessageQDef(keyNum, 16, uint16_t);
  keyNumHandle = osMessageCreate(osMessageQ(keyNum), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of KEY_SCAN */
  osThreadDef(KEY_SCAN, KeyScanTask02, osPriorityNormal, 0, 128);
  KEY_SCANHandle = osThreadCreate(osThread(KEY_SCAN), NULL);

  /* definition and creation of KEY_MENU */
  osThreadDef(KEY_MENU, Key_MenuTask03, osPriorityBelowNormal, 0, 128);
  KEY_MENUHandle = osThreadCreate(osThread(KEY_MENU), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_KeyScanTask02 */
/**
* @brief Function implementing the KEY_SCAN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KeyScanTask02 */
void KeyScanTask02(void const * argument)
{
  /* USER CODE BEGIN KeyScanTask02 */
  u16 key_num;
    osStatus test;
  /* Infinite loop */
  for(;;)
  {
//      LED0_Tog;
//      printf("1111111\r\n");
      key_num = KeyScan();
      if(key_num)
      {
          test =  osMessagePut (keyNumHandle,key_num, 0);
          if(test != osOK){
              printf("Could not send to the queue\r\n");
          }
          key_num = 0;
      }
      osDelay(20);
  }
  /* USER CODE END KeyScanTask02 */
}

/* USER CODE BEGIN Header_Key_MenuTask03 */
/**
* @brief Function implementing the KEY_MENU thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Key_MenuTask03 */
void Key_MenuTask03(void const * argument)
{
  /* USER CODE BEGIN Key_MenuTask03 */
    osEvent ev;
  /* Infinite loop */
  for(;;)
  {
    if(osMessageWaiting(keyNumHandle) != 0){
        printf("Queue should have benne empty\r\n");
    }

    ev =osMessageGet(keyNumHandle,100);
    if(ev.status == osEventMessage){
        printf("rec = %d\r\n",ev.value.v);
    }
    else{
        printf("Could not recviced from the quueue\r\n");
    }
  }
  /* USER CODE END Key_MenuTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
