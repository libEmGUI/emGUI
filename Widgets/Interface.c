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

#include "Interface.h"
#include <stdio.h>

xInterface *xInterfaceInstance;
xTouchEventType eTouchState = popTs;

xWindow * xActiveWindow = NULL;

xInterface * pxInterfaceCreate(bool(*pxOnCreateHandler)(xWidget *)) {

	xInterfaceInstance = pxWidgetCreate(0, 0, LCD_SizeX, LCD_SizeY, NULL, true);
	bStatusBarCreate(COLOR_STATUS_BAR_BG);
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
	vWidgetInvalidate(xInterfaceInstance);
}
/*
void vInterfaceDebug(bool bDebug){
  vDebugSetModuleLogLevel(MODULE_GUI_TASK, LOG_DEBUG);
  vInterfaceInvalidate();
}

bool bInterfaceGetDebug(){
  return (iDebugGetModuleLogLevel(MODULE_GUI_TASK) >= LOG_DEBUG)?true:false;
}*/

bool bInterfaceCheckTouchScreenEvent(xTouchEvent *pxTouchScreenEv) {
	return bWidgetCheckTouchScreenEvent(xInterfaceInstance, pxTouchScreenEv);
}

xWindow * pxInterfaceIsWindowOpened(eWindow eWnd, xWindow ** pxNext) {
	xWindowProps *xP;
	xWindow *xW = xActiveWindow;
	char cLimit = 100; //защита от зацикливания

	*pxNext = NULL;

	do {
		if (!(xP = (xWindowProps*)pxWidgetGetProps(xW, WidgetWindow)))
			return NULL;
		if (xP->eId == eWnd)
			return xW;
		*pxNext = xW;
	} while ((xW = pxWindowGetBack(xW)) && cLimit--);

	//TODO: проверять cLimit

	return NULL;
}

xWindow * pxInterfaceIsWindowActive(eWindow eWnd) {
	xWindowProps *xP;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(xActiveWindow, WidgetWindow)))
		return NULL;

	if (xP->eId == eWnd)
		return xActiveWindow;

	return NULL;
}

inline void prvDelWndFromStack(xWindow *pxN, xWindow *pxNext) {

	xWidget * pxPrev; //пред. окно в стеке
	xWindowProps *xP;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxN, WidgetWindow)))
		return; //ошибка! TODO: обработчик

	pxPrev = xP->xBackWindow;

	if (!(xP = (xWindowProps*)pxWidgetGetProps(pxNext, WidgetWindow)))
		return; //ошибка! TODO: обработчик

	xP->xBackWindow = pxPrev;
}

void vInterfaceOpenWindow(eWindow eWnd) {
	xWidget * pxN,    //текущее окно в стеке
		*pxNext = NULL; //следующее окно в стеке
	xWindowProps *xP;

	//Если окно уже активно, то нечего его открывать
	//TODO: нужно ли генерировать события в этом случае??? openRequest???


	if (pxInterfaceIsWindowActive(eWnd)) {
		vInterfaceUpdateWindow();
		return;
	}

	//если окно неактивно, то pxNext != NULL
	if ((pxN = pxInterfaceIsWindowOpened(eWnd, &pxNext))) {
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
	pxN = xInterfaceInstance->pxChild;
	while (pxN) {

		if (!(xP = (xWindowProps*)pxWidgetGetProps(pxN, WidgetWindow))) {
			pxN = pxWidgetGetNext(pxN);
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
		pxN = pxWidgetGetNext(pxN);
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

void vInterfaceCloseWindow(eWindow eWnd) {
	xWidget * pxN = xActiveWindow,
		*pxNext = NULL;
	xWindowProps *xP;

	if (pxInterfaceIsWindowActive(eWnd)) {
		vInterfaceCloseActiveWindow();
		return;
	}

	if ((pxN = pxInterfaceIsWindowOpened(eWnd, &pxNext))) {
		if (!(xP = (xWindowProps*)pxWidgetGetProps(pxN, WidgetWindow)))
			return;

		//проверяем возможно ли закрыть окно в данный момент
		if (xP->pxOnCloseRequest)
			if (!xP->pxOnCloseRequest(pxN)) {
				//Если невозможно, то окно должно стать активным для устранения причины
				vInterfaceOpenWindow(eWnd);
				return;
			}

		prvDelWndFromStack(pxN, pxNext);

		//проверяем возможно ли закрыть окно в данный момент
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
