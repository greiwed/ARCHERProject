#include "main.h"
#include "DMA_Configuration.h"

static volatile int16_t buffer1[SMALL_BUFF_SIZE];
static volatile int16_t buffer2[SMALL_BUFF_SIZE];

void DMA_Configuration(){
	
	
	// Enable ADC Stream
	LL_ADC_Enable(ADC1);
	
	// Configure DMA settings
	LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_0, LL_DMA_CHANNEL_0);
	LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_0, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_0, LL_DMA_PRIORITY_LOW);
	MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMA2 + STREAM_OFFSET_TAB[LL_DMA_STREAM_0])))->CR, 0, DMA_SxCR_DBM);
	LL_DMA_SetMode(DMA2, LL_DMA_STREAM_0, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_0, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_0, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_0, LL_DMA_PDATAALIGN_HALFWORD);
	LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_0, LL_DMA_MDATAALIGN_HALFWORD);
	LL_DMA_DisableFifoMode(DMA2, LL_DMA_STREAM_0);
	LL_DMA_ConfigAddresses(DMA2,LL_DMA_STREAM_0,LL_ADC_DMA_GetRegAddr(ADC1,LL_ADC_DMA_REG_REGULAR_DATA),(uint32_t)buffer1,LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetMemory1Address(DMA2,LL_DMA_STREAM_0,(uint32_t)buffer2);
	LL_DMA_SetDataLength(DMA2,LL_DMA_STREAM_0, sizeof(buffer1)/sizeof(buffer1[0]));
	LL_DMA_EnableIT_TC(DMA2,LL_DMA_STREAM_0);
	
	// Enable DMA Steam
	LL_DMA_EnableStream(DMA2,LL_DMA_STREAM_0);
	WRITE_REG(ADC1->SR, ~LL_ADC_FLAG_OVR);

	// Enable Timer
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_CC_EnableChannel(TIM2,LL_TIM_CHANNEL_CH1);

}
