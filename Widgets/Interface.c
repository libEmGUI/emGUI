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

	Created on: 14.11.2012
*/

#include "emGUI/Widgets/Interface.h"
#include <stdio.h>
#include "emGUI/Draw/Draw.h"

xInterface *xInterfaceInstance;
xTouchEventType eTouchState = popTs;

typedef struct {
	xWindow xPrevious;
	xWindow xCurrent;
}xWindowList_t;

xWindow * xActiveWindow = NULL;

xWindowList_t *xWindowList = NULL;

xInterface * pxInterfaceCreate(bool(*pxOnCreateHandler)(xWidget *)) {

	xInterfaceInstance = pxWidgetCreate(0, 0, EMGUI_LCD_WIDTH, EMGUI_LCD_HEIGHT, NULL, true);
	bStatusBarCreate(EMGUI_COLOR_STATUS_BAR_BG);
	if (pxOnCreateHandler)
		pxOnCreateHandler(xInterfaceInstance);

	return xInterfaceInstance;
}

void vInterfaceDraw() {
	vWidgetDraw(xInterfaceInstance);
}

xInterface *pxInterfaceGet() {
	return xInterfaceInstance;
}

void vInterfaceInvalidate() {
	if( xInterfaceInstance )
		vWidgetInvalidate(xInterfaceInstance);
}

bool bInterfaceCheckTouchScreenEvent(xTouchEvent *pxTouchScreenEv) {
	return bWidgetCheckTouchScreenEvent(xInterfaceInstance, pxTouchScreenEv);
}

xWindow * pxInterfaceGetWindow(int eWnd) {

	xWidget *pxN = xInterfaceInstance->pxFirstChild;
	while (pxN) {
		if (iWindowGetID(pxN) == eWnd)
			return pxN;
		pxN = pxWidgetGetNextChild(pxN);
	}

	return NULL;
}

bool bInterfaceIsWindowActive(int eWnd) {
	return iWindowGetID(xActiveWindow) == eWnd;
}

inline void prvDelWndFromStack(xWindow *pxN, xWindow *pxNext) {

	xWidget * pxPrev; //previous window in the stack
	xWindowProps *xP;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxN, WidgetWindow)))
		return; //error! TODO: handler?

	pxPrev = xP->xBackWindow;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxNext, WidgetWindow)))
		return; //error! TODO: handler?

	xP->xBackWindow = pxPrev;
}

void vInterfaceOpenWindow(int eWnd) {
	xWidget * pxN,    // current window in the stack
		*pxNext = NULL; //next window in the stack
	xWindowProps *xP;

	// Если окно уже активно, то нечего его открывать
	// TODO: нужно ли генерировать события в этом случае??? openRequest???


	if (bInterfaceIsWindowActive(eWnd)) {
		vInterfaceUpdateWindow();
		return;
	}

	// window is already opened
	if ((pxN = pxInterfaceGetWindow(eWnd))) {
		//поднять окошко из стека

		prvDelWndFromStack(pxN, pxNext);

		//Кладем окно в вершину стека (делаем его Active)
		if (!(xP = (xWindowProps*)pxWidgetGetProps(pxN, WidgetWindow)))
			return; //ошибка! TODO: обработчик

		xP->xBackWindow = xActiveWindow;

		vWidgetHide(xActiveWindow);
		vWidgetShow(pxN);

		xActiveWindow = pxN;
		vInterfaceUpdateWindow();
		return;
	}

	//окно закрыто - добавляем его в стек
	//поиск всех окон в интерфейсе
	//указатель на первый объект-потомок интерфейса
	pxN = xInterfaceInstance->pxFirstChild;
	while (pxN) {

		if (!(xP = (xWindowProps*)pxWidgetGetProps(pxN, WidgetWindow))) {
			pxN = pxWidgetGetNextChild(pxN);
			continue;
		}

		if (xP->eId == eWnd) {
			//проверка что мы открываем окно, которое не явл. активным
			if (pxN != xActiveWindow) {
				if (xP->pxOnOpenRequest)
					if (!xP->pxOnOpenRequest(pxN))
						//отменяем открытие, если обработчик вернул false
						break;

				xP->xBackWindow = xActiveWindow;

				vWidgetHide(xActiveWindow);
				xActiveWindow = pxN;
				if (xP->pxOnOpen)
					xP->pxOnOpen(pxN);
				//Проверка не открылся ли диалог или окно в обработчике onOpen
				if (xActiveWindow == pxN) {
					vWidgetShow(xActiveWindow);
					vInterfaceUpdateWindow();
				}
			}
			break; //только одно окно может быть видимо.
		}
		pxN = pxWidgetGetNextChild(pxN);
	}
}

void vInterfaceCloseActiveWindow() {
	xWindowProps *xP;

	//ненормальная ситуация
	//TODO: открыть окно по умолчанию
	if (!xActiveWindow)
		return;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(xActiveWindow, WidgetWindow)))
		return;

	//проверяем возможно ли закрыть окно в данный момент
	if (xP->pxOnCloseRequest)
		if (!xP->pxOnCloseRequest(xActiveWindow))
			return;

	if (xP->xBackWindow) {

		vWidgetHide(xActiveWindow);
		xActiveWindow = xP->xBackWindow;
		xP->xBackWindow = NULL;
		vWidgetShow(xActiveWindow);

		if (xP->pxOnClose)
			xP->pxOnClose(xActiveWindow);
		vInterfaceUpdateWindow();
	} /*else { //TODO: Should we issue OnClose when there's last window on display?
		if (xP->pxOnClose)
			xP->pxOnClose(xActiveWindow);
	}*/

}

void vInterfaceCloseWindow(int eWnd) {
	xWidget * pxN = xActiveWindow,
		*pxNext = NULL;
	xWindowProps *xP;

	if (bInterfaceIsWindowActive(eWnd)) {
		vInterfaceCloseActiveWindow();
		return;
	}

	if ((pxN = pxInterfaceGetWindow(eWnd))) {
		if (!(xP = (xWindowProps*)pxWidgetGetProps(pxN, WidgetWindow)))
			return;

		//check if we can close window 
		if (xP->pxOnCloseRequest)
			if (!xP->pxOnCloseRequest(pxN)) {
				// if we are unable to close the window, we should pop it to the front
				vInterfaceOpenWindow(eWnd);
				return;
			}

		prvDelWndFromStack(pxN, pxNext);

		// check if we can close window at the moment
		if (xP->pxOnClose)
			if (!xP->pxOnClose(pxN))
				return;
	}
}

void vInterfaceUpdateWindow() {

	xWindowProps *xP;
	if (!(xP = (xWindowProps*)pxWidgetGetProps(xActiveWindow, WidgetWindow)))
		return;

	if (xP->bFullScreen) {
		vWidgetHide(pxStatusBarGet());
	}
	else {
		vWidgetShow(pxStatusBarGet());
	}
	vStatusBarSetWindowHeader(xP->strHeader);

}
