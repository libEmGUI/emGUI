/*
	emGUI Library V1.0.0 - Copyright (C) 2013 Roman Savrulin <romeo.deepmind@gmail.com>

	This file is part of the emGUI Library distribution.

	emGUI Library is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License (version 2) as published by the
	Roman Savrulin AND MODIFIED BY the emGUI Library exception.

	>>>NOTE<<< The modification to the GPL is included to allow you to
	distribute a combined work that includes emGUI Library without being obliged to
	provide the source code for proprietary components outside of the emGUI Library.
	emGUI Library is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
	more details. You should have received a copy of the GNU General Public
	License and the emGUI Library license exception along with emGUI Library; if not it
	can be obtained by writing to Roman Savrulin <romeo.deepmind@gmail.com>.

	Created on: 15.11.2012
*/

#include "emGUI/Widgets/Button.h"
#include "emGUI/Widgets/Label.h"

#include <malloc.h>
#include "emGUI/Draw/Draw.h"

typedef struct xButtonProps_struct {
	bool bEmulatePressure;
	xPicture pusPicDisabled;
	xWidget *xText;       ///< Label widget for Pictured button with text
} xButtonProps;

static bool prvButtonDraw(xButton *pxW) {
	xButtonProps *xP = pxWidgetGetProps(pxW, WidgetButton);

	if (!xP)
		return false;

	if (pxW->bValid)
		return false;

	xP = (xButtonProps *)pxW->pvProp;

	if (!pxW->bPressed) {
		if (pxW->pusBgPicture)
			pxDrawHDL()->bPicture(pxW->usX0, pxW->usY0, pxW->pusBgPicture);
	}
	else if (xP->bEmulatePressure) {

		if (pxW->pusBgPicture)
			pxDrawHDL()->bPicture(pxW->usX0, pxW->usY0, pxW->pusBgPicture);

		pxDrawHDL()->vVLine(pxW->usX0 + 2, pxW->usY0 + 2, pxW->usY1 - 2, EMGUI_WIDGET_COLOR_BLACK);
		pxDrawHDL()->vHLine(pxW->usX0 + 2, pxW->usY0 + 2, pxW->usX1 - 2, EMGUI_WIDGET_COLOR_BLACK);

		pxDrawHDL()->vVLine(pxW->usX1 - 2, pxW->usY0 + 2, pxW->usY1 - 2, EMGUI_WIDGET_COLOR_WHITE);
		pxDrawHDL()->vHLine(pxW->usX0 + 2, pxW->usY1 - 2, pxW->usX1 - 2, EMGUI_WIDGET_COLOR_WHITE);

	}

	return true;
}

static bool bButtonCheckTSRoutine(xButton *pxW, xTouchEvent *pxTouchScreenEv) {
	xButtonProps *xP = pxWidgetGetProps(pxW, WidgetButton);

	if (!xP)
		return false;
	
	if (xP->bEmulatePressure)
		vWidgetInvalidate(pxW);

	return (pxTouchScreenEv->eventTouchScreen == popTs) ? false : true;
}

static bool prvDispose(xWidget *pxW) {
	xButtonProps *xP = pxWidgetGetProps(pxW, WidgetButton);

	if (!xP)
		return false;

	vWidgetDispose(xP->xText);
	free(xP);
	free(pxW);
	return true; //means nothing
}

static xButton * prvAlloc() {
	xButton *pxW;
	xButtonProps *xP;

	pxW = malloc(sizeof(xWidget));

	if (!pxW)
		return NULL;

	memset(pxW, 0, sizeof(xWidget));

	xP = malloc(sizeof(xButtonProps));

	if (!xP) {
		free(pxW);
		return NULL;
	}

	memset(xP, 0, sizeof(xButtonProps));
	pxW->pvProp = xP;

	return pxW;
};

static bool prvInit(xWidget * pxW) {
	if (!pxW)
		return false;

	pxW->eType = WidgetButton;

	xButtonProps *xP = pxWidgetGetProps(pxW, WidgetButton);

	if (!xP)
		return false;

	
	pxW->pxOnDispose = prvDispose;

	pxW->pxDrawHandler = prvButtonDraw;
	pxW->pxCheckTSRoutine = bButtonCheckTSRoutine;

	xP->bEmulatePressure = true;
	pxW->bClickable = true;

	return true;
}

void vButtonSetOnClickHandler(xWidget *pxW, WidgetEvent pxCallback) {
	xButtonProps *xP = pxWidgetGetProps(pxW, WidgetButton);

	if (!xP)
		return false;

	vWidgetSetOnClickHandler(pxW, pxCallback);

	if(xP->xText)
		vWidgetSetOnClickHandler(xP->xText, pxCallback);
}

xButton * pxButtonCreateSimple(uint16_t usX, uint16_t usY, uint16_t usW, uint16_t usH, const char *text, xWidget *pxWidParent) {
	xButton * pxW = prvAlloc();

	if (pxW && bWidgetInit(pxW, usX, usY, usW, usH, pxWidParent, true)) {

		prvInit(pxW);

		xButtonProps *xP = pxWidgetGetProps(pxW, WidgetButton);

		xP->xText = pxLabelCreate(usX, usY, usW, usH, text, pxDrawHDL()->xGetDefaultFont(), 0, pxW);

		vLabelSetTextAlign(xP->xText, LABEL_ALIGN_CENTER);
		vLabelSetVerticalAlign(xP->xText, LABEL_ALIGN_MIDDLE);

		return pxW;
	}
	else {
		vWidgetDispose(pxW);
		return NULL;
	}
}

xButton * pxButtonCreateFromImage(uint16_t usX, uint16_t usY, xPicture pusPic, xWidget *pxWidParent) {
	xButton * pxW = prvAlloc();

	if (pxW && bWidgetInit(pxW, usX, usY, 1, 1, pxWidParent, true)) {

		prvInit(pxW);

		bWidgetSetBgPicture(pxW, pusPic); // this updates button W and H from given picture

		return pxW;
	} else {
		vWidgetDispose(pxW);
		return NULL;
	}

	return pxW;
}

xButton * pxButtonCreateFromImageWithText(uint16_t usX, uint16_t usY, xPicture pusPic, const char *text, xWidget *pxWidParent) {
	xButton *pxW = pxButtonCreateSimple(usX, usY, 1, 1, text, pxWidParent);

	if(!pxW)
		return NULL;

	xButtonProps *xP = pxWidgetGetProps(pxW, WidgetButton);

	if (!xP) {
		prvDispose(pxW);
		return false;
	}

	bWidgetSetBgPicture(pxW, pusPic); // this updates button W and H from given picture

	bWidgetSetCoords(xP->xText, 
		0, 
		pxDrawHDL()->usGetPictureH(pusPic), 
		pxDrawHDL()->usGetPictureW(pusPic),
		pxDrawHDL()->usFontGetH(pxDrawHDL()->xGetDefaultFont()) + 3,
		true);

	bWidgetSetCoords(pxW,
		usWidgetGetX0(pxW, false),
		usWidgetGetY0(pxW, false),
		usWidgetGetX1(pxW, false),
		usWidgetGetY1(pxW, false) + usWidgetGetH(xP->xText),
		false);

	return pxW;
}

void vButtonSetText(xWidget * pxW, char const* strL) {
	xButtonProps *xP;

	if (!(xP = (xButtonProps*)pxWidgetGetProps(pxW, WidgetButton)))
		return;

	pcLabelSetText(xP->xText, strL);

	return;
}