/*********************************************************

     * Name              : Eman Megahed
	 * Data              : 6/1/2021
	 * Version           : 1.0
	 * SWC               : LCD.h

**********************************************************/

#ifndef LCD_H_
#define LCD_H_


void LCD_WriteCommand(u8 Data);

void LCD_WriteCommand(u8 Data);

void LCD_init(void);

void LCD_WriteData(u8 Data);

void LCD_WriteData(u8 Data);

void LCD_WriteString(u8 *str);

void LCD_CursorMove(u8 col,u8 row);

void LCD_Clear(void);

void LCD_WriteNum(s16 num);

void LCD_WriteNumInBinary(u8 num);

void LCD_WriteNum_4D(u16 num);

#endif /* LCD_H_ */
