/*********************************************************

     * Name              : Eman Megahed
	 * Data              : 6/1/2021
	 * Version           : 1.0
	 * SWC               : LCD.c

**********************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "Platform_Types.h"
#include "LCD.h"
#include "Dio.h"
#include "LCD_Cfg.h"

#if( MODE ==BIT_8_MODE)

void LCD_WriteCommand(u8 Data)
{
	Dio_WriteChannel(RS,STD_LOW);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	Dio_WritePort(PORTLCD,Data);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}


void LCD_WriteData(u8 Data)
{
	Dio_WriteChannel(RS,STD_HIGH);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	Dio_WritePort(PORTLCD,Data);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}

void LCD_init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x38);
	_delay_us(50);
	LCD_WriteCommand(0x0c);
	_delay_us(50);
	LCD_WriteCommand(0x1);
	_delay_ms(2);
	LCD_WriteCommand(0x6);
	_delay_ms(2);
}

#elif( MODE ==BIT_4_MODE)

void LCD_WriteCommand(u8 Data)
{
	Dio_WriteChannel(RS,STD_LOW);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	Dio_WriteChannel(D0,READ_BIT(Data,4));
	Dio_WriteChannel(D1,READ_BIT(Data,5));
	Dio_WriteChannel(D2,READ_BIT(Data,6));
	Dio_WriteChannel(D3,READ_BIT(Data,7));
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
	Dio_WriteChannel(D0,READ_BIT(Data,0));
	Dio_WriteChannel(D1,READ_BIT(Data,1));
	Dio_WriteChannel(D2,READ_BIT(Data,2));
	Dio_WriteChannel(D3,READ_BIT(Data,3));
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}

void LCD_WriteData(u8 Data)
{
	Dio_WriteChannel(RS,STD_HIGH);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	Dio_WriteChannel(D0,READ_BIT(Data,4));
	Dio_WriteChannel(D1,READ_BIT(Data,5));
	Dio_WriteChannel(D2,READ_BIT(Data,6));
	Dio_WriteChannel(D3,READ_BIT(Data,7));
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
	Dio_WriteChannel(D0,READ_BIT(Data,0));
	Dio_WriteChannel(D1,READ_BIT(Data,1));
	Dio_WriteChannel(D2,READ_BIT(Data,2));
	Dio_WriteChannel(D3,READ_BIT(Data,3));
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}

void LCD_init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x02);
	_delay_us(50);
	LCD_WriteCommand(0x28);
	_delay_us(50);
	LCD_WriteCommand(0x0c);
	_delay_us(50);
	LCD_WriteCommand(0x1);
	_delay_ms(2);
	LCD_WriteCommand(0x6);
	_delay_ms(2);
}

#endif

void LCD_WriteString(u8 *str)
{
	for(u8 i = 0;str[i];i++)
	{
		LCD_WriteData(str[i]);
	}
}

void LCD_CursorMove(u8 row,u8 col)
{
	if(row==1)
	{
		LCD_WriteCommand(col+0x80);
	}
	else if(row==2)
	{
		LCD_WriteCommand(col+0x40+0x80);
	}

}

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_WriteNum(s16 num)
{
	u8 rem = 0;
	u8 i = 0;
	u16 arr[16]={0};
	u8 j = 0;
	if(num>0)
	{
		while(num>0)
		{
			rem=num%10;
			arr[i]=rem+'0';
			i++;
			num=num/10;
		}
		for( j=i;j>0;j--)
		{
			LCD_WriteData(arr[j-1]);
		}
	}
	else if(num<0)
	{
		LCD_WriteData('-');
		while(num<0)
		{
			rem=num%10;
			arr[i]=-rem+'0';
			i++;
			num=num/10;
		}
		for( j=i;j>0;j--)
		{
			LCD_WriteData(arr[j-1]);
		}
	}
	else
		LCD_WriteData('0');

}

void LCD_WriteNumInBinary(u8 num)
{
	u8 rem = 0;
	u8 i = 0;
	u16 arr[16]={0};
	u8 j = 0;

	if(num>0)
	{
		while(num>0)
		{
			rem=num%2;
			arr[i]=rem+'0';
			i++;
			num=num/2;
		}
		for( j=i;j>0;j--)
		{
			LCD_WriteData(arr[j-1]);
		}
		/*for(i=8;i>0;i--)
		{
			LCD_WriteData(((num>>i)&1)+'0');
		}*/
	}

}

void LCD_WriteNum_4D(u16 num)
{
	LCD_WriteData(((num%10000)/1000)+'0');
	LCD_WriteData(((num%1000)/100)+'0');
	LCD_WriteData(((num%100)/10)+'0');
	LCD_WriteData(((num%10)/1)+'0');

}
