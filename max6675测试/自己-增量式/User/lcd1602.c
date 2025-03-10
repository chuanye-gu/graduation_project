#include "lcd1602.h"

void LCD1602_GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(LCD1602_CLK, ENABLE);
	GPIO_InitTypeDef LCD1602_GPIOStruct;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_10MHz;
	LCD1602_GPIOStruct.GPIO_Pin =  LCD1602_E | LCD1602_RS | LCD1602_RW ;
	GPIO_Init(LCD1602_GPIO_PORT,&LCD1602_GPIOStruct);
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	LCD1602_GPIOStruct.GPIO_Pin =   DB0 |  DB1 | DB2 |DB3 |  DB4 | DB5|
																	DB6 |  DB7 ;     //设置为开漏输出 
	GPIO_Init(LCD1602_GPIO_PORT,&LCD1602_GPIOStruct);
}

void LCD1602_WaitReady(void) //检测忙状态
{
	uint8_t sta;

	GPIOB->ODR =0x00FF;
	RSO(0);
	RWO(1);
	EO(1);
	Delay_Us(1);
	do{
		sta=GPIO_ReadInputDataBit(LCD1602_GPIO_PORT,GPIO_Pin_7);
		EO(0);
	}while(sta);
}

void LCD1602_WriteCmd(uint8_t cmd) //写指令
{
	LCD1602_WaitReady();
	RSO(0);
	RWO(0);
	EO(0);
	Delay_Us(1);
	EO(1);
	LCD1602_GPIO_PORT->ODR &= (cmd|0xFF00);
	EO(0);
	Delay_Us(400);
}

void LCD1602_WriteDat(uint8_t dat) //写数据
{
	LCD1602_WaitReady();
	RSO(1);
	RWO(0);
	Delay_Us(30);
	EO(1);
	LCD1602_GPIO_PORT->ODR &=(dat|0xFF00);
	EO(0);
	Delay_Us(400);
}

void LCD1602_WriteOneDat(uint8_t dat) //写数据
{
	LCD1602_WaitReady();
	RSO(1);
	RWO(0);
	Delay_Us(30);
	EO(1);
	LCD1602_GPIO_PORT->ODR &=(dat|0xFF00);
	EO(0);
	Delay_Us(400);
}

void LCD1602_SetCursor(uint8_t x, uint8_t y)
{
    uint8_t addr;
    
    if (y == 0)  //由输入的屏幕坐标计算显示RAM的地址
        addr = 0x00 + x;  //第一行字符地址从0x00起始
    else
        addr = 0x40 + x;  //第二行字符地址从0x40起始
    LCD1602_WriteCmd(addr|0x80);  //设置RAM地址
}

void LCD1602_ShowStr(uint8_t x, uint8_t y, char *str)
{
		Delay_Us(20000);
    LCD1602_SetCursor(x, y);	//设置起始地址
    while (*str)         //连续写入len个字符数据
    {
        LCD1602_WriteDat(*str++);
    }
}

void LCD1602_Init(void)
{
	  LCD1602_GPIO_Config();   //开启GPIO口
    LCD1602_WriteCmd(0X38);  //16*2显示，5*7点阵，8位数据接口
    LCD1602_WriteCmd(0x0C);  //显示器开，光标关闭
    LCD1602_WriteCmd(0x06);  //文字不动，地址自动+1
    LCD1602_WriteCmd(0x01);  //清屏
}
	
	



