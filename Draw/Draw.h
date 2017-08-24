#ifndef EMGUI_DRAW_H
#define EMGUI_DRAW_H

#include <stdint.h>
#include <stdbool.h>
#include "Fonts/Font.h"

typedef struct {
	void(*vFramebufferRectangle)(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, uint16_t usColor, bool bFill);
	void(*vFramebufferPutChar)(uint16_t usX, uint16_t usY, char ASCI, xFont pubFont, uint16_t usColor, uint16_t usBackground, bool bFillBg);
	void(*vFramebufferHLine)(uint16_t usX0, uint16_t usY0, uint16_t usY1, uint16_t usColor);
	void(*vFramebufferVLine)(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usColor);
	void(*bFramebufferPicture)(int16_t sX0, int16_t sY0, unsigned short const* pusPicture);
}LCD_Glue;

void vWidgetSetLCD(LCD_Glue * LCD);
LCD_Glue * pxWidgetGetLCD();


#endif // !EMGUI_DRAW_H