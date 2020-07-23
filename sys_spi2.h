#ifndef __sys_spi2_H
#define __sys_spi2_H


#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)//A0
#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)

#define OLED_RST_Clr() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET)//RES
#define OLED_RST_Set() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET)
 		     
#define OLED_CS_Clr()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)


void LCD_init(void);
void LCD_Send_date(uint8_t *dat,uint32_t length);
void LCD_Write_Command(uint8_t dat);

#endif /* __sys_spi2_H */


