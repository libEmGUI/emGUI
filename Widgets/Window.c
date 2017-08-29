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

	Created on: 19.02.2013
*/

#include "Widgets/Window.h"
#include "Widgets/Interface.h"
#include "Widgets/StatusBar.h"
#include <malloc.h>
#include <string.h>
//#include "utils.h"




xWindow * pxWindowCreate(eWindow eWnd) {
	xWindowProps *xP;
	xWindow *pxW;

	pxW = malloc(sizeof(xWidget));

	if (bWidgetInit(pxW, usInterfaceGetWindowX(), usInterfaceGetWindowY(), usInterfaceGetWindowW(), usInterfaceGetWindowH(), pxInterfaceGet(), true)) {

		vWidgetSetBgColor(pxW, 65535, false); //белый фон
		vWidgetSetVisible(pxW, false);

		xP = malloc(sizeof(xWindowProps));

		if (!xP)
			return NULL;

		xP->xBackWindow = NULL;
		xP->pxOnCloseRequest = NULL;
		xP->pxOnClose = NULL;
		xP->pxOnOpenRequest = NULL;
		xP->pxOnOpen = NULL;
		xP->bFullScreen = false;
		xP->eId = eWnd;
		xP->strHeader = (char*)malloc(WINDOW_HEADER_LENGTH + 1);
		xP->strHeader[0] = '\0';
		pxW->pvProp = xP;
		pxW->eType = WidgetWindow;

		return pxW;
	}
	else {
		free(pxW);
		return NULL;
	}
}

void vWindowSetHeader(xWidget * pxW, char const* strH) {
	xWindowProps *xP;
	int iLen = MIN(strlen(strH), WINDOW_HEADER_LENGTH);
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	memcpy(xP->strHeader, strH, iLen + 1);
	xP->strHeader[iLen] = '\0';
	vInterfaceUpdateWindow();
}

void vWindowSetOnCloseRequestHandler(xWidget * pxW, bool(*pxCallback)(xWidget *)) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnCloseRequest = pxCallback;
}

void vWindowSetOnCloseHandler(xWidget * pxW, bool(*pxCallback)(xWidget *)) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnClose = pxCallback;
}

void vWindowSetOnOpenHandler(xWidget * pxW, bool(*pxCallback)(xWidget *)) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnOpen = pxCallback;
}

void vWindowSetOnOpenRequestHandler(xWidget * pxW, bool(*pxCallback)(xWidget *)) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnOpenRequest = pxCallback;
}

xWindow * pxWindowGetBack(xWidget *pxW) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return NULL;
	return xP->xBackWindow;
}

void vWindowSetFullScreen(xWidget *pxW, bool bFS) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;

	if (bFS) {
		if (bWidgetSetCoords(pxW, 0, 0, LCD_SizeX, LCD_SizeY, true))
			xP->bFullScreen = bFS;
	}
	else {
		if (bWidgetSetCoords(pxW, usInterfaceGetWindowX(), usInterfaceGetWindowY(), usInterfaceGetWindowW(), usInterfaceGetWindowH(), true))
			xP->bFullScreen = bFS;
	}
	vInterfaceUpdateWindow();
}
