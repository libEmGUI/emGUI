#ifndef EMGUI_DRAW_H
#define EMGUI_DRAW_H

#include <stdint.h>
#include <stdbool.h>
#include "Fonts/Font.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct {
		void(*vRectangle)(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, uint16_t usColor, bool bFill);
		void(*vPutChar)(uint16_t usX, uint16_t usY, char ASCI, xFont pubFont, uint16_t usColor, uint16_t usBackground, bool bFillBg);
		void(*vHLine)(uint16_t usX0, uint16_t usY0, uint16_t usY1, uint16_t usColor);
		void(*vVLine)(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usColor);
		void(*bPicture)(int16_t sX0, int16_t sY0, unsigned short const* pusPicture);
	}xDraw_t;

	void vDrawSetHandler(xDraw_t * hdl);
	xDraw_t * pxDrawHDL();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !EMGUI_DRAW_H