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

#ifndef EM_GUI_OVERRIDE_DEFAULT_FONTS
#error fix default font handlers!

static void vStandartPutString(uint16_t usX, uint16_t usY, const char * pcStr, xFont pubFont, uint16_t usColor, uint16_t usBackground, bool bFillBg) {
	
}

static uint16_t usFontGetH(xFont pubFont) {
	
}

static char ucFontGetCharW(char cChar, xFont pubFont) {
	
}

static uint16_t usFontGetStrW(char const * pcStr, xFont pubFont) {
	
}

static uint16_t usFontGetStrH(const char * pcStr, xFont pubFont) {
	
}
#endif // !EM_GUI_OVERRIDE_DEFAULT_FONTS


void vDrawSetHandler(xDraw_t * hdl) {
	_HDL = hdl;
}

xDraw_t * pxDrawHDL() {
	return _HDL;
}

void vDrawHandlerInit(xDraw_t * hdl) {
	memset(hdl, 0, sizeof(xDraw_t));
	
#ifndef EM_GUI_OVERRIDE_DEFAULT_PICS
	hdl->usGetPictureH = &usGetPictureH;
	hdl->usGetPictureW = &usGetPictureW;
#endif

#ifndef EM_GUI_OVERRIDE_DEFAULT_FONTS
	hdl->vPutString = &vStandartPutString;
	hdl->usFontGetH = &usFontGetH;
	hdl->ucFontGetCharW = &ucFontGetCharW;
	hdl->usFontGetStrW = &usFontGetStrW;
	hdl->usFontGetStrH = &usFontGetStrH;
#endif

}