#include <stdio.h> 
#include "stm32f10x.h"
#include "./lcd/bsp_ili9341_lcd.h"

void DMA_mtm(void);
void Delay(__IO u32 nCount);
uint32_t buff[20];	
uint32_t DisBuff[20];	

int main(void)
{		
	int i = 0;
	  // LCD≈‰÷√
		ILI9341_Init();    						
		ILI9341_GramScan(6);	
		LCD_SetFont(&Font16x24);
		LCD_SetColors(WHITE,BLACK);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	
	for(i=0;i<20;i++)
	{
	buff[i] = i;
	}
	DMA_mtm();
  while(1);
}

void DMA_mtm(void)	 													
{
	DMA_InitTypeDef DMA_Structure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_Structure.DMA_PeripheralBaseAddr = (uint32_t)buff;	
	DMA_Structure.DMA_MemoryBaseAddr = (uint32_t)DisBuff;
	DMA_Structure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	DMA_Structure.DMA_BufferSize = 32;
	
	DMA_Structure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_Structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_Structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Structure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	DMA_Structure.DMA_Mode = DMA_Mode_Normal;
	DMA_Structure.DMA_Priority = DMA_Priority_High;
	DMA_Structure.DMA_M2M = DMA_M2M_Enable;
	
	DMA_Init(DMA1_Channel1,&DMA_Structure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

void Delay(__IO uint32_t nCount)	 													
{
	for(; nCount != 0; nCount--);
}
