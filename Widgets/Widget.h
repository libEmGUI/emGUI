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

#ifndef EMGUI_WIDGET_H
#define EMGUI_WIDGET_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "emGUI/options/opts.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef enum {
		Widget,
		WidgetLabel,
		WidgetButton,
		WidgetWindow,
		WidgetStatusBar,
		WidgetPlot
	} eWidgetType;

	typedef enum {
		popTs,
		pushTs,
		updateTs
	} xTouchEventType;

	typedef struct xPoint_t {
		uint16_t usX;
		uint16_t usY;
	}xPoint;

	typedef struct xTouchEvent_t {
		xTouchEventType eventTouchScreen;
		uint16_t xTouchScreen;
		uint16_t yTouchScreen;
		uint32_t touchScreenEventTime;
	} xTouchEvent;


	typedef struct xWidget_struct xWidget;

	typedef bool(*WidgetEvent)        (xWidget *);
	typedef bool(*WidgetKeyPressEventHdl)      (xWidget *, uint16_t uEv);

	//The size of each widget is 60 bytes.
	struct xWidget_struct {
		eWidgetType eType;

		//Absolute Position and dimentions
		uint16_t usX0;
		uint16_t usY0;
		uint16_t usX1;
		uint16_t usY1;

		//Visibility and behavior
		uint16_t bValid : 1; //0      
		uint16_t bClickable : 1;
		uint16_t bVisible : 1; //2
		uint16_t bEnabled : 1;
		uint16_t bPressed : 1; //4
		uint16_t bPushEventCaught : 1;
		uint16_t bTransparent : 1; //6
		uint16_t bInvalidate : 1; //0
		uint16_t bInvalidateParent : 1;

		//background
		uint16_t usBgColor;
		xPicture pusBgPicture;

		//Child object properties   
		void* pvProp;

		xWidget *pxParent;
		xWidget *pxFirstChild;
		xWidget *pxNextSibling;

		WidgetEvent pxDrawHandler;
		bool(*pxCheckTSRoutine)(xWidget *, xTouchEvent *);
		WidgetEvent pxOnClick;
		WidgetEvent pxOnShow;
		WidgetEvent pxOnHide;

		WidgetEvent pxOnDispose;

		WidgetKeyPressEventHdl pxOnKeypress;

		void *pvUserData;

	};

	xWidget * pxWidgetCreate(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, xWidget *pxWidParent, bool bUseWH);

	void vWidgetDispose(xWidget *pxW); //TODO: check, experimental

	bool bWidgetInit(xWidget *pxW, uint16_t usX, uint16_t usY, uint16_t usW, uint16_t usH, xWidget *pxWidParent, bool bUseWH);
	void vWidgetInvalidate(xWidget *pxW);
	void vWidgetDraw(xWidget *pxW);

	bool bWidgetAdd(xWidget *pxW, xWidget *pxWidChild);
	void vWidgetRemove(xWidget * pxW); //TODO: check, experimental
	
	bool bWidgetCheckTouchScreenEvent(xWidget *pxW, xTouchEvent *pxTouchScreenEv);
	bool bWidgetCheckKeypressEvent(xWidget *pxW, uint16_t uEv);

	bool bWidgetMoveTo(xWidget *pxW, uint16_t usX0, uint16_t usY0);
	
	// Setters
	void vWidgetSetOnClickHandler(xWidget *pxW, WidgetEvent pxCallback);
	void vWidgetSetOnKeypressHandler(xWidget * pxW, WidgetKeyPressEventHdl pxCallback);

	void vWidgetSetOnHideHandler(xWidget *pxW, WidgetEvent pxCallback);
	void vWidgetSetOnShowHandler(xWidget *pxW, WidgetEvent pxCallback);
	void vWidgetSetDrawHandler(xWidget *pxW, WidgetEvent pxCallback);

	void vWidgetSetClickable(xWidget *pxW, bool bClickable);
	void vWidgetSetBgColor(xWidget *pxW, uint16_t usBgColor, bool bTransparent);
	void vWidgetSetTransparency(xWidget *pxW, bool bTransparent);
	bool bWidgetSetBgPicture(xWidget *pxW, xPicture pusBgPicture);
	void vWidgetSetVisible(xWidget *pxW, bool bVisible);
	bool bWidgetSetCoords(xWidget *pxW, uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, bool bUseWH);

	// Commands
	bool bWidgetDrawHandler(xWidget *pxW);
	bool bWidgetCheckTSHandler(xWidget *pxW, xTouchEvent *pxTouchScreenEv);

	// Getters
	uint16_t usWidgetGetW(xWidget *pxW);
	uint16_t usWidgetGetH(xWidget *pxW);

	uint16_t usWidgetGetX0(xWidget *pxW, bool bAbsolute);
	uint16_t usWidgetGetY0(xWidget *pxW, bool bAbsolute);
	uint16_t usWidgetGetX1(xWidget *pxW, bool bAbsolute);
	uint16_t usWidgetGetY1(xWidget *pxW, bool bAbsolute);

	xWidget *pxWidgetGetFirstChild(xWidget *pxW);
	xWidget *pxWidgetGetNextChild(xWidget *pxW);

	void *   pxWidgetGetProps(xWidget * pxW, eWidgetType eType);

	// One-line helpers
	inline bool bWidgetResize(xWidget *pxW, uint16_t usW, uint16_t usH) {
		return bWidgetSetCoords(pxW, usWidgetGetX0(pxW, false), usWidgetGetY0(pxW, false), usW, usH, true);
	}

	inline bool bWidgetIs(xWidget * pxW, eWidgetType eType) {
		return (pxW && pxW->eType == eType) ? true : false;
	}

	inline void vWidgetShow(xWidget *pxW) {
		vWidgetSetVisible(pxW, true);
	}

	inline void vWidgetHide(xWidget *pxW) {
		vWidgetSetVisible(pxW, false);
	}


#ifdef __cplusplus
}
#endif // __cplusplus

#endif	//__WIDGET_H
