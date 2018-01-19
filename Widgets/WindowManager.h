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

#ifndef EMGUI_WINDOW_MANAGER_H
#define EMGUI_WINDOW_MANAGER_H

#include <stdint.h>

#include "emGUI/Widgets/Widget.h"
#include "emGUI/Widgets/Window.h"
#include "emGUI/Widgets/StatusBar.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef xWidget xWindowManager;
	typedef bool(*WindowKeyPressEventHdl)      (int wndId, uint16_t uEv);

	xWindowManager * pxWindowManagerCreate(bool(*pxOnCreateHandler)(xWidget *));
	void vWindowManagerDraw();
	xWindowManager *pxWindowManagerGet();
	inline uint16_t usWindowManagerGetW() {
		return EMGUI_LCD_WIDTH;
	}
	inline uint16_t usWindowManagerGetH() {
		return EMGUI_LCD_HEIGHT;
	}
	inline uint16_t usWindowManagerGetWindowH() {
		return EMGUI_LCD_HEIGHT - EMGUI_STATUS_BAR_HEIGHT;
	}
	inline uint16_t usWindowManagerGetWindowW() {
		return EMGUI_LCD_WIDTH;
	}
	inline uint16_t usWindowManagerGetWindowX() {
		return 0;
	}
	inline uint16_t usWindowManagerGetWindowY() {
		return EMGUI_STATUS_BAR_HEIGHT;
	}
	void vWindowManagerInvalidate();
	bool bWindowManagerCheckTouchScreenEvent(xTouchEvent *pxTouchScreenEv);
	bool bWindowManagerCheckKeypressEvent(uint16_t uEv);

	xStatusBar *pxWindowManagerGetStatusBar();

	void vWindowManagerOpenWindow(int eWnd);
	void vWindowManagerCloseActiveWindow();
	void vWindowManagerCloseWindow(int eWnd);
	void vWindowManagerUpdateWindow();
	bool bWindowManagerIsWindowActive(int eWnd);
	xWindow * pxWindowManagerGetWindow(int eWnd);

	void vWindowManagerSetKeypressHandler(WindowKeyPressEventHdl pxEvenHandler);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	//__WINDOW_MANAGER_H
