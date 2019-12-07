/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "adc.h"
#include "semphr.h"
#include "queue.h"
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
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
osThreadId_t defaultTaskHandle;
osThreadId_t DanielTaskHandle;
uint32_t DanielTaskBuffer[ 1024 ];
osStaticThreadDef_t DanielTaskControlBlock;
osThreadId_t ZhiTaskHandle;
uint32_t ZhiTaskBuffer[ 128 ];
osStaticThreadDef_t ZhiTaskControlBlock;
osMessageQueueId_t locationHandle;
uint8_t myQueue01BufferBuffer[ 1 * 4 ];
osStaticMessageQDef_t myQueue01BufferControlBlock;
osSemaphoreId_t DMA_CompleteHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void DSPTask(void *argument);
void DisplayTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of DMA_Complete */
  const osSemaphoreAttr_t DMA_Complete_attributes = {
    .name = "DMA_Complete"
  };
  DMA_CompleteHandle = osSemaphoreNew(1, 1, &DMA_Complete_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of location */
  const osMessageQueueAttr_t location_attributes = {
    .name = "location",
    .cb_mem = &myQueue01BufferControlBlock,
    .cb_size = sizeof(myQueue01BufferControlBlock),
    .mq_mem = &myQueue01BufferBuffer,
    .mq_size = sizeof(myQueue01BufferBuffer)
  };
  locationHandle = osMessageQueueNew (1, 4, &location_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of DanielTask */
  const osThreadAttr_t DanielTask_attributes = {
    .name = "DanielTask",
    .stack_mem = &DanielTaskBuffer[0],
    .stack_size = sizeof(DanielTaskBuffer),
    .cb_mem = &DanielTaskControlBlock,
    .cb_size = sizeof(DanielTaskControlBlock),
    .priority = (osPriority_t) osPriorityHigh,
  };
  DanielTaskHandle = osThreadNew(DSPTask, NULL, &DanielTask_attributes);

  /* definition and creation of ZhiTask */
  const osThreadAttr_t ZhiTask_attributes = {
    .name = "ZhiTask",
    .stack_mem = &ZhiTaskBuffer[0],
    .stack_size = sizeof(ZhiTaskBuffer),
    .cb_mem = &ZhiTaskControlBlock,
    .cb_size = sizeof(ZhiTaskControlBlock),
    .priority = (osPriority_t) osPriorityLow,
  };
  ZhiTaskHandle = osThreadNew(DisplayTask, NULL, &ZhiTask_attributes);

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
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_DSPTask */
/**
* @brief Function implementing the DanielTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DSPTask */
void DSPTask(void *argument)
{
  /* USER CODE BEGIN DSPTask */
	DMA_Configuration();
	uint8_t decision;
	int16_t location[2];

  /* Infinite loop */
  for(;;)
  {
	osSemaphoreAcquire(DMA_CompleteHandle,osWaitForever);

	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0) == GPIO_PIN_SET){
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_SET);
	}

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_SET);
	classification_Algorithm(&decision);

	if(decision == 1){
		location_Algorithm(location);
		osMessageQueuePut(locationHandle, location,0, 0);
	}else{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_RESET);
	}

  }
  /* USER CODE END DSPTask */
}

/* USER CODE BEGIN Header_DisplayTask */
/**
* @brief Function implementing the ZhiTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DisplayTask */
void DisplayTask(void *argument)
{
  /* USER CODE BEGIN DisplayTask */
	// Local Variables
	int16_t location[2];
	char charloc[9];
	int16_t cx;
	int16_t cy;
	int16_t sx;
	int16_t sy;

	// Initialize Screen
	ILI9341_Init();
	ILI9341_setRotation(4);
	ILI9341_Fill(COLOR_CYAN);
	ILI9341_printText("A.R.C.H.E.R.", 60, 0, COLOR_RED, COLOR_RED, 3);
	ILI9341_printText("Sound position", 15, 218, COLOR_ORANGE, COLOR_ORANGE, 2);
	ILI9341_fillCircle(190,221, 2, COLOR_ORANGE);
	ILI9341_fillCircle(190,231, 2, COLOR_ORANGE);
	printgrid();
	drawgridline();
	drawmic();


	//uint8_t data[] = {0x01,0x02,0x03,0x04,0x05,0x0a,0x0b,0x0c};
	//ILI9341_Init();
  /* Infinite loop */
  for(;;)
  {
	osMessageQueueGet(locationHandle, &location, NULL, osWaitForever);



	// Clear Screen
	ILI9341_Fill_Rect(6,26,316,210,COLOR_CYAN);
	drawmic();
	drawgridline();
	ILI9341_Fill_Rect(200,210,300,239,COLOR_CYAN);
	//242*148 = x*y, yinput = i, xinput = x

	// Update Screen
	cy = location[1];	//length
	cx = location[0]; //width
	sx = 8+cx*1.3; //length
	sy = 208-cy*1.2;	//width
	printlocation(sx,sy); //image
	loc_cor(cx,cy,charloc);
	ILI9341_printText(charloc, 200, 218, COLOR_RED, COLOR_RED, 2); //coordinate output
	if(sx>314) sx=314;
	if(sy>208) sy=208;
	ILI9341_fillCircle(sx,sy, 1, COLOR_RED); //exact location
	ILI9341_Fill_Rect(308,210,320,239,COLOR_CYAN);
	drawmic();

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET);
  }
  /* USER CODE END DisplayTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void DMA_Semaphore_Release() {

	osSemaphoreRelease(DMA_CompleteHandle);

}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
