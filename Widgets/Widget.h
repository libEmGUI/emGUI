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

#ifndef __WIDGET_H
#define __WIDGET_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "emGUI/Fonts/Font.h"
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
		WidgetMenuButton,
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
		xWidget *pxChild;
		xWidget *pxNextSibling;

		bool(*pxDrawHandler)   (xWidget *);
		bool(*pxCheckTSRoutine)(xWidget *, xTouchEvent *);
		bool(*pxOnClick)       (xWidget *);
		bool(*pxOnShow)        (xWidget *);
		bool(*pxOnHide)        (xWidget *);

	};

	xWidget * pxWidgetCreate(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, xWidget *pxWidParent, bool bUseWH);

	inline xWidget *pxWidgetGetChild(xWidget *pxW) {
		return pxW->pxChild;
	}

	inline xWidget *pxWidgetGetNext(xWidget *pxW) {
		return pxW->pxNextSibling;
	}

	bool bWidgetInit(xWidget *pxW, uint16_t usX, uint16_t usY, uint16_t usW, uint16_t usH, xWidget *pxWidParent, bool bUseWH);
	void vWidgetInvalidate(xWidget *pxW);
	void vWidgetDraw(xWidget *pxW);
	bool bWidgetAdd(xWidget *pxW, xWidget *pxWidChild);
	bool bWidgetCheckTouchScreenEvent(xWidget *pxW, xTouchEvent *pxTouchScreenEv);

	bool bWidgetMoveTo(xWidget *pxW, uint16_t usX0, uint16_t usY0);
	//Setters

	void vWidgetSetOnClickHandler(xWidget *pxW, bool(*pxCallback)(xWidget *));
	void vWidgetSetOnHideHandler(xWidget *pxW, bool(*pxCallback)(xWidget *));
	void vWidgetSetOnShowHandler(xWidget *pxW, bool(*pxCallback)(xWidget *));
	void vWidgetSetDrawHandler(xWidget *pxW, bool(*pxCallback)(xWidget *));
	void vWidgetSetClickable(xWidget *pxW, bool bClickable);
	void vWidgetSetBgColor(xWidget *pxW, uint16_t usBgColor, bool bTransparent);
	void vWidgetSetTransparency(xWidget *pxW, bool bTransparent);
	bool bWidgetSetBgPicture(xWidget *pxW, xPicture pusBgPicture);
	void vWidgetSetVisible(xWidget *pxW, bool bVisible);
	bool bWidgetSetCoords(xWidget *pxW, uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, bool bUseWH);

	//Commands
	bool bWidgetDraw(xWidget *pxW);

	inline void vWidgetShow(xWidget *pxW) {
		vWidgetSetVisible(pxW, true);
	}

	inline void vWidgetHide(xWidget *pxW) {
		vWidgetSetVisible(pxW, false);
	}

	//Getters
	inline uint16_t usWidgetGetW(xWidget *pxW) {
		return pxW->usX1 - pxW->usX0 + 1;
	}

	inline uint16_t usWidgetGetH(xWidget *pxW) {
		return pxW->usY1 - pxW->usY0 + 1;
	}

	inline uint16_t usWidgetGetX0(xWidget *pxW, bool bAbsolute) {
		if (!pxW->pxParent)
			return pxW->usX0;

		if (bAbsolute)
			return pxW->usX0;
		else
			return pxW->usX0 - pxW->pxParent->usX0;
	}

	inline uint16_t usWidgetGetY0(xWidget *pxW, bool bAbsolute) {
		if (!pxW->pxParent)
			return pxW->usY0;

		if (bAbsolute)
			return pxW->usY0;
		else
			return pxW->usY0 - pxW->pxParent->usY0;
	}

	inline uint16_t usWidgetGetX1(xWidget *pxW, bool bAbsolute) {
		if (!pxW->pxParent)
			return pxW->usX1;

		if (bAbsolute)
			return pxW->usX1;
		else
			return pxW->usX1 - pxW->pxParent->usX0;
	}

	inline uint16_t usWidgetGetY1(xWidget *pxW, bool bAbsolute) {
		if (!pxW->pxParent)
			return pxW->usY1;

		if (bAbsolute)
			return pxW->usY1;
		else
			return pxW->usY1 - pxW->pxParent->usY0;
	}

	inline bool bWidgetResize(xWidget *pxW, uint16_t usW, uint16_t usH) {
		return bWidgetSetCoords(pxW, usWidgetGetX0(pxW, false), usWidgetGetY0(pxW, false), usW, usH, true);
	}

	inline bool bWidgetIs(xWidget * pxW, eWidgetType eType) {
		return (pxW && pxW->eType == eType) ? true : false;
	}

	inline void * pxWidgetGetProps(xWidget * pxW, eWidgetType eType) {
		if (!bWidgetIs(pxW, eType))
			return NULL;

		return pxW->pvProp;
	}


	bool bInterfaceGetDebug();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	//__WIDGET_H
