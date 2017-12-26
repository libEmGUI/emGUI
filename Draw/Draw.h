#ifndef EMGUI_DRAW_H
#define EMGUI_DRAW_H

#include <stdint.h>
#include <stdbool.h>
#include "emGUI/options/opts.h"
#include "emGUI/Widgets/ModalDialog.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct {
		void     (*vRectangle)(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, uint16_t usColor, bool bFill);
		
		void     (*vHLine)(uint16_t usX0, uint16_t usY0, uint16_t usY1, uint16_t usColor);
		void     (*vVLine)(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usColor);

		void     (*bPicture)(int16_t sX0, int16_t sY0, xPicture pusPicture);
		uint16_t (*usGetPictureH)(xPicture pusPic);
		uint16_t (*usGetPictureW)(xPicture pusPic);

		void     (*vPutChar)(uint16_t usX, uint16_t usY, char ASCI, xFont pubFont, uint16_t usColor, uint16_t usBackground, bool bFillBg);
		uint16_t (*ucFontGetCharW)(char cChar, xFont pubFont);
		uint16_t (*usFontGetH)(xFont pubFont);
		uint16_t (*usFontGetStrW)(const char * pcStr, xFont pubFont);
		uint16_t (*usFontGetStrH)(const char * pcStr, xFont pubFont);

		xModalDialogPictureSet (*xGetDialogPictureSet)(char cType);
		xPicture (*xGetPicture)(const char *pxPicName);
		xFont    (*xGetDefaultFont)(); //TODO: getFontByName?
	}xDraw_t;

	void vDrawSetHandler(xDraw_t * hdl);
	xDraw_t * pxDrawHDL();
	void vDrawHandlerInit(xDraw_t * hdl);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !EMGUI_DRAW_H