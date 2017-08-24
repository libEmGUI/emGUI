#include "Draw/Draw.h"

static LCD_Glue * _LCD;

void vWidgetSetLCD(LCD_Glue * LCD) {
	_LCD = LCD;
}

LCD_Glue * pxWidgetGetLCD() {
	return _LCD;
}