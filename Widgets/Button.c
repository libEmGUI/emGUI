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

#include "Widgets/Button.h"
#include <malloc.h>

static bool vButtonDraw(xButton *pxW) {
	xButtonProps *xP;

	if (!pxW)
		return false;

	if (pxW->eType != WidgetButton)
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

		pxDrawHDL()->vVLine(pxW->usX0 + 2, pxW->usY0 + 2, pxW->usY1 - 2, WIDGET_COLOR_BLACK);
		pxDrawHDL()->vHLine(pxW->usX0 + 2, pxW->usY0 + 2, pxW->usX1 - 2, WIDGET_COLOR_BLACK);

		pxDrawHDL()->vVLine(pxW->usX1 - 2, pxW->usY0 + 2, pxW->usY1 - 2, WIDGET_COLOR_WHITE);
		pxDrawHDL()->vHLine(pxW->usX0 + 2, pxW->usY1 - 2, pxW->usX1 - 2, WIDGET_COLOR_WHITE);

	}

	return true;
}

static bool bButtonCheckTSRoutine(xButton *pxW, xTouchEvent *pxTouchScreenEv) {
	xButtonProps *xP;

	if (!pxW)
		return false;

	xP = (xButtonProps *)pxW->pvProp;

	if (xP->bEmulatePressure)
		vWidgetInvalidate(pxW);

	return (pxTouchScreenEv->eventTouchScreen == popTs) ? false : true;
}

xButton * pxButtonCreate(uint16_t usX, uint16_t usY, xPicture pusPic, xWidget *pxWidParent) {
	xButton *pxW;
	xButtonProps *xP;

	pxW = malloc(sizeof(xWidget));

	if (bWidgetInit(pxW, usX, usY, 1, 1, pxWidParent, true)) {

		bWidgetSetBgPicture(pxW, pusPic);

		xP = malloc(sizeof(xButtonProps));

		if (!xP)
			return NULL;

		xP->pusPicDisabled = NULL;
		xP->bEmulatePressure = true;

		pxW->pvProp = xP;

		pxW->bClickable = true;

		pxW->eType = WidgetButton;

		pxW->pxDrawHandler = vButtonDraw;
		pxW->pxCheckTSRoutine = bButtonCheckTSRoutine;

		return pxW;
	}
	else {
		free(pxW);
		return NULL;
	}
}

//TODO: Test this code (should work)
bool bButtonSetPushPic(xButton *pxW, xPicture pusPic) {
	xButtonProps *xP;

	if (!pxW)
		return false;

	xP = pxW->pvProp;

	xP->bEmulatePressure = pusPic;
	//press picture must be the same size as foreground pic

	if(pxDrawHDL()->usGetPictureH(pusPic) != usWidgetGetH(pxW))
	  return false;

	if(pxDrawHDL()->usGetPictureW(pusPic) != usWidgetGetW(pxW))
	  return false;

	if(pxW->bPressed)
	  vWidgetInvalidate(pxW);

	return true;
}
