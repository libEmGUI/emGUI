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

#include "emGUI/Widgets/Window.h"
#include "emGUI/Widgets/WindowManager.h"
#include "emGUI/Widgets/StatusBar.h"
#include <malloc.h>
#include <string.h>
#include "emGUI/Draw/Draw.h"

typedef struct xWindowProps_t {
	int eId;
	char* strHeader;
	bool bFullScreen;
	//bool bModal;
	WidgetEvent pxOnCloseRequest;
	WidgetEvent pxOnClose;
	WidgetEvent pxOnOpenRequest;
	WidgetEvent pxOnOpen;

	WidgetEvent pxOnDispose;
} xWindowProps;

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif // !MIN

static bool prvDispose(xWindow * pxW) {
	xWindowProps *xP;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return false;

	if (xP->pxOnDispose)
		xP->pxOnDispose(pxW);

	if (xP->strHeader)
		free(xP->strHeader);

	return true;
}

int iWindowGetID(xWindow * pxW) {
	xWindowProps *xP;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return -1;

	return xP->eId;
}

xWindow * pxWindowCreate(int eWnd) {
	xWindowProps *xP;

	if (pxWindowManagerGetWindow(eWnd)) // window with such id is already created
		return NULL;

	xWindow *pxW = pxWidgetCreate(usWindowManagerGetWindowX(), usWindowManagerGetWindowY(), usWindowManagerGetWindowW(), usWindowManagerGetWindowH(), pxWindowManagerGet(), true);

	if (pxW) {

		pxW->eType = WidgetWindow;
		pxW->pxOnDispose = prvDispose;

		vWidgetSetBgColor(pxW, EMGUI_COLOR_WHITE, false);
		vWidgetSetVisible(pxW, false);

		xP = malloc(sizeof(xWindowProps));

		if (!xP) {
			vWidgetDispose(pxW);
			return NULL;
		}

		memset(xP, 0, sizeof(xWindowProps));

		pxW->pvProp = xP;

		xP->eId = eWnd;
		xP->strHeader = (char*)malloc(EMGUI_WINDOW_HEADER_LENGTH + 1);
		xP->strHeader[0] = '\0';

	}
	
	return pxW;
}

void vWindowSetHeader(xWindow * pxW, char const* strH) {
	xWindowProps *xP;
	int iLen = MIN(strlen(strH), EMGUI_WINDOW_HEADER_LENGTH);
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	memcpy(xP->strHeader, strH, iLen + 1);
	xP->strHeader[iLen] = '\0';
	vWindowManagerUpdateWindow();
}

void vWindowSetOnCloseRequestHandler(xWindow * pxW, WidgetEvent pxCallback) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnCloseRequest = pxCallback;
}

void vWindowSetOnCloseHandler(xWindow * pxW, WidgetEvent pxCallback) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnClose = pxCallback;
}

void vWindowSetOnOpenHandler(xWindow * pxW, WidgetEvent pxCallback) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnOpen = pxCallback;
}

void vWindowSetOnOpenRequestHandler(xWindow * pxW, WidgetEvent pxCallback) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;
	xP->pxOnOpenRequest = pxCallback;
}

void vWindowSetFullScreen(xWindow *pxW, bool bFS) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return;

	if (bFS) {
		if (bWidgetSetCoords(pxW, 0, 0, EMGUI_LCD_WIDTH, EMGUI_LCD_HEIGHT, true))
			xP->bFullScreen = bFS;
	}
	else {
		if (bWidgetSetCoords(pxW, usWindowManagerGetWindowX(), usWindowManagerGetWindowY(), usWindowManagerGetWindowW(), usWindowManagerGetWindowH(), true))
			xP->bFullScreen = bFS;
	}
	vWindowManagerUpdateWindow();
}

bool bWindowClose(xWindow *pxW) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return false;

	if (xP->pxOnCloseRequest)
		if (!xP->pxOnCloseRequest(pxW))
			return false;

	vWidgetHide(pxW);

	if (xP->pxOnClose)
		xP->pxOnClose(pxW);

	return true;
}

bool bWindowOpen(xWindow *pxW) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return false;

	if (xP->pxOnOpenRequest)
		if (!xP->pxOnOpenRequest(pxW))
			return false;

	vWidgetShow(pxW);

	if (xP->pxOnOpen)
		xP->pxOnOpen(pxW);

	return true;
}

bool bWindowGetFullScreen(xWindow *pxW) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return false;

	return xP->bFullScreen;
}

const char* pcWindowGetHeader(xWindow *pxW) {
	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxW, WidgetWindow)))
		return NULL;

	return xP->strHeader;
}
