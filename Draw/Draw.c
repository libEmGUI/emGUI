#include "Draw/Draw.h"
#include <string.h>

static xDraw_t * _HDL;

#ifndef EM_GUI_OVERRIDE_DEFAULT_PICS

static uint16_t usGetPictureW(xPicture pusPic) {
	return pusPic[1];
}

static uint16_t usGetPictureH(xPicture pusPic) {
	return pusPic[0];
}

#endif // !EM_GUI_OVERRIDE_DEFAULT_PICS

static void vStandartPutString(uint16_t usX, uint16_t usY, const char * pcStr, xFont pubFont, uint16_t usColor, uint16_t usBackground, bool bFillBg) {
	unsigned char charWidth;
	while (*pcStr) {
		charWidth = *pubFont[(*pcStr)];

		pxDrawHDL()->vPutChar(usX, usY, *pcStr, pubFont, usColor, usBackground, bFillBg);

		usX += charWidth;
		if (usX >= LCD_SizeX)
			break;
		pcStr++;
	}
}


void vDrawSetHandler(xDraw_t * hdl) {
	_HDL = hdl;
}

xDraw_t * pxDrawHDL() {
	return _HDL;
}

void vDrawHandlerInit(xDraw_t * hdl) {
	memset(hdl, 0, sizeof(xDraw_t));
	hdl->vPutString = &vStandartPutString;
#ifndef EM_GUI_OVERRIDE_DEFAULT_PICS
	hdl->usGetPictureH = &usGetPictureH;
	hdl->usGetPictureW = &usGetPictureW;
#endif
}