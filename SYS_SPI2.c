#include "stm32f1xx_it.h"
#include "main.h"

#include "sys_spi2.h"
#include <string.h>

extern SPI_HandleTypeDef hspi2;

static void LCD_init_program(void);
static void LCD_Clear(uint8_t Color);

void LCD_init(void)
{

  LCD_init_program();
  LCD_Clear(0x00);   
} 


static void LCD_init_program(void)
{
   
  OLED_RST_Clr();//LCD_Reset_CLR; 
  OLED_RST_Set();//LCD_Reset_SET; 

  OLED_DC_Clr();//LCD_A0_CLR;
  LCD_Write_Command(0xae); //Display OFF
  LCD_Write_Command(0xd5); // Set Dclk
  LCD_Write_Command(0x50); //  100Hz
  LCD_Write_Command(0x20); // Set row address
  LCD_Write_Command(0x81); // Set contrast control0x81
  LCD_Write_Command(0x80);
  LCD_Write_Command(0xa0); // Segment remap
  LCD_Write_Command(0xa4); // Set Entire Display ON
  LCD_Write_Command(0xa6); // Normal display
  LCD_Write_Command(0xad); // Set external VCC
  LCD_Write_Command(0x80);
  LCD_Write_Command(0xc0); // Set Common scan direction
  LCD_Write_Command(0xd9); // Set phase leghth
  LCD_Write_Command(0x1f);
  LCD_Write_Command(0xdb); // Set Vcomh voltage
  LCD_Write_Command(0x27);
  LCD_Write_Command(0xaf); //Display ON

}

void LCD_Write_Command(uint8_t dat)
{
  OLED_CS_Clr();
  OLED_DC_Clr();

  HAL_SPI_Transmit(&hspi2,&dat,1,HAL_MAX_DELAY);
 
  OLED_CS_Set();
}


void LCD_Write_Data(uint8_t dat)
{
  OLED_CS_Clr();
  OLED_DC_Set();
	
  HAL_SPI_Transmit(&hspi2,&dat,1,HAL_MAX_DELAY); 
 
  OLED_CS_Set();
}


static void LCD_Clear(uint8_t Color)
{
  uint8_t i,j;
  for(i = 0;i < 16;i++)   
  {
    LCD_Write_Command(0xb0 + i);         //page0-page1
    LCD_Write_Command(0x00);		//low column start address
    LCD_Write_Command(0x10);		//high column start address
    for(j = 0;j < 128;j++)
    {
      LCD_Write_Data(Color);
    }    
  }
} 



void LCD_Send_date(uint8_t *dat,uint32_t length)
{
  OLED_CS_Clr();
  OLED_DC_Set();
	
  HAL_SPI_Transmit(&hspi2,dat,length,HAL_MAX_DELAY);

  OLED_CS_Set();
}

