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

#include "emGUI/Widgets/Widget.h"
#include <stdlib.h>
#include <stdio.h>
#include "emGUI/Draw/Draw.h"


xWidget * pxWidgetCreate(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, xWidget *pxWidParent, bool bUseWH) {
	xWidget *pxW;
	pxW = malloc(sizeof(xWidget));

	if (!pxW)
		return NULL;

	memset(pxW, 0, sizeof(xWidget));

	if (bWidgetInit(pxW, usX0, usY0, usX1, usY1, pxWidParent, bUseWH))
		return pxW;
	else {
		free(pxW);
		return NULL;
	}
}

void vWidgetDispose(xWidget *pxW) {
	if (!pxW || !pxW->pxOnDispose)
		return;

	vWidgetRemove(pxW);

	pxW->pxOnDispose(pxW);
	if (pxW->pvProp)
		free(pxW->pvProp);
	free(pxW);
}

bool bWidgetInit(xWidget *pxW, uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, xWidget *pxWidParent, bool bUseWH) {
	if (!pxW)
		return false;

	pxW->eType = Widget;

	pxW->pxParent = pxWidParent;

	pxW->bInvalidate = true;
	pxW->bVisible = true;
	pxW->bEnabled = true;

	pxW->bTransparent = true;
	pxW->pxDrawHandler = bWidgetDrawHandler;

	//TODO: check LCD sizes
	if (!bWidgetSetCoords(pxW, usX0, usY0, usX1, usY1, bUseWH))
		return false;

	if (pxWidParent != NULL) {
		bWidgetAdd(pxWidParent, pxW);
	}

	return true;
}

void vWidgetInvalidate(xWidget *pxW) {
	if(pxW)
		pxW->bInvalidate = true;
}

static void prvInvalidateChilds(xWidget *pxW) {
	if (pxW && pxW->pxFirstChild) {
		xWidget *pxWidChild = pxW->pxFirstChild;
		while (pxWidChild) {
			vWidgetInvalidate(pxWidChild);
			pxWidChild = pxWidChild->pxNextSibling;
		}
	}
}

/*void vWidgetEnabled(xWidget *pxW, bool bEnabled){
  pxW->bEnabled = bEnabled;

  //Disable chlidren
}*/

bool bWidgetDrawHandler(xWidget *pxW) {

	if (!pxW)
		return false;

	if (pxW->bValid)
		return false;

	if (pxW->pusBgPicture) {
		pxDrawHDL()->bPicture(pxW->usX0, pxW->usY0, pxW->pusBgPicture);
		return true;
	}

	if (!pxW->bTransparent) {
		pxDrawHDL()->vRectangle(pxW->usX0, pxW->usY0, pxW->usX1, pxW->usY1, pxW->usBgColor, true);
		return true;
	}

	return false;
}

void vWidgetDraw(xWidget *pxW) {
	if (!pxW)
		return;

	bool bRedrawed = false;

	//We don't need to redraw widget and children tree if it is not visible
	if (!pxW->bVisible)
		return;

	if (pxW->bInvalidateParent && pxW->pxParent)
		return;

	// check childs for bWidgetInvalidateParent flag
	if (pxW->pxFirstChild) {
		xWidget *pxWidChild = pxW->pxFirstChild;
		while (pxWidChild) {
			if (pxWidChild->bInvalidateParent) {
				pxWidChild->bInvalidateParent = false;
				pxW->bInvalidate = true;
			}
			pxWidChild = pxWidChild->pxNextSibling;
		}
	}

	// check invalidation
	if (pxW->bInvalidate) {
		prvInvalidateChilds(pxW);
		pxW->bValid = false;
		pxW->bInvalidate = false;
	}

	if (pxW->pxDrawHandler)
		bRedrawed = pxW->pxDrawHandler(pxW);

	if (pxW->pxFirstChild) {
		xWidget *pxWidChild = pxW->pxFirstChild;
		while (pxWidChild) {
			vWidgetDraw(pxWidChild);
			pxWidChild = pxWidChild->pxNextSibling;
		}
	}

	// validate widget
	pxW->bValid = true;

#if EMGUI_DEBUG > 0
	if (bRedrawed) {
		pxDrawHDL()->vRectangle(pxW->usX0, pxW->usY0, pxW->usX1, pxW->usY1, rand(), false);
	}
#endif
}

bool bWidgetAdd(xWidget *pxWidParent, xWidget *pxWidChild) {
	if (!pxWidChild || !pxWidParent)
		return false;
	xWidget *pxW, *pxWidLast = NULL;

	//TODO: check for duplicates via pointer address
	//TODO: check for duplicates in children to prevent recursion
	if (!pxWidParent->pxFirstChild)
		pxWidParent->pxFirstChild = pxWidChild;
	else {
		pxW = pxWidParent->pxFirstChild;
		while (pxW) { //iterate through the list of children
			pxWidLast = pxW;
			pxW = pxW->pxNextSibling;
		}
		if (pxWidLast)
			pxWidLast->pxNextSibling = pxWidChild;
	}

	return true;
}

void vWidgetRemove(xWidget * pxW) {
	if (!pxW)
		return;

	xWidget * pxChild = pxW->pxParent->pxFirstChild;

	while (pxChild) {

		xWidget *pxNext = pxWidgetGetNextChild(pxChild);
		xWidget *pxPrev = NULL;

		if (pxChild == pxW) { //first element
			if (!pxPrev)
				pxW->pxFirstChild = pxNext;
			else
				pxPrev->pxNextSibling = pxNext;
		}

		pxPrev = pxChild;
		pxChild = pxNext;
	}
}

bool bWidgetCheckKeypressEvent(xWidget *pxW, uint16_t uEv) {
	if (!pxW)
		return false;
	//By default catching an event doesn't invalidate the widget.
	//Enherited widgets should invalidate itself from bWidgetCheckKeypressEvent

	if (!pxW->bVisible)
		return false;

	if (!pxW->bEnabled)
		return false;

	if (pxW->pxFirstChild) {
		xWidget *pxWidChild = pxW->pxFirstChild;
		while (pxWidChild) {
			if (bWidgetCheckKeypressEvent(pxWidChild, uEv))
				return true;
			pxWidChild = pxWidChild->pxNextSibling;
		}
	}

	if (pxW->pxOnKeypress)
		return pxW->pxOnKeypress(pxW, uEv);

	return false;
}

bool bWidgetCheckTouchScreenEvent(xWidget *pxW, xTouchEvent *pxTouchScreenEv) {
	if (!pxW)
		return false;
	//By default catching an event doesn't invalidate the widget.
	//Enherited widgets should invalidate itself from pxCheckTSRoutine
	//bPressed state is controlled via return value of pxCheckTSRoutine

	if (!pxW->bVisible)
		return false;

	if (!pxW->bEnabled)
		return false;

	//handle popTs events when they occur out of the Widget area
	if (pxTouchScreenEv->eventTouchScreen == popTs
		&& pxW->bPushEventCaught) {
		if (pxW->pxCheckTSRoutine)
			pxW->bPressed = pxW->pxCheckTSRoutine(pxW, pxTouchScreenEv);
		else
			pxW->bPressed = false;
		pxW->bPushEventCaught = false;
		//Fire OnClick event
		if (pxW->pxOnClick && !pxW->bPressed)
			pxW->pxOnClick(pxW);

		//TODO: add timeout for releasing buttons if we lost popTs message

		/*if(bInterfaceGetDebug() && !pxW->bPressed)
		  MDEBUG("Widget release @ %x\n", pxW);*/
	}

	if (pxW->pxFirstChild) {
		xWidget *pxWidChild = pxW->pxFirstChild;
		while (pxWidChild) {
			if (bWidgetCheckTouchScreenEvent(pxWidChild, pxTouchScreenEv))
				return true;
			pxWidChild = pxWidChild->pxNextSibling;
		}
	}

	if (!pxW->bClickable)
		return false;

	//TODO: check by radius?
	if (pxW->usX0 <= pxTouchScreenEv->xTouchScreen
		&& pxW->usX1 >= pxTouchScreenEv->xTouchScreen
		&& pxW->usY0 <= pxTouchScreenEv->yTouchScreen
		&& pxW->usY1 >= pxTouchScreenEv->yTouchScreen
		&& pxTouchScreenEv->eventTouchScreen == pushTs) {
		if (pxW->pxCheckTSRoutine)
			pxW->bPressed = pxW->pxCheckTSRoutine(pxW, pxTouchScreenEv);
		else
			pxW->bPressed = true;

		pxW->bPushEventCaught = true;
		return true;
	}

	return false;
}

void vWidgetSetClickable(xWidget *pxW, bool bClickable) {
	if (!pxW)
		return;
	pxW->bClickable = bClickable;
}

void vWidgetSetBgColor(xWidget *pxW, uint16_t usBgColor, bool bTransparent) {
	if (!pxW)
		return;
	pxW->usBgColor = usBgColor;
	pxW->bTransparent = bTransparent;

	//TODO: handle transparency color???
	vWidgetInvalidate(pxW);
};

void vWidgetSetTransparency(xWidget *pxW, bool bTransparent) {
	if (!pxW)
		return;
	pxW->bTransparent = bTransparent;
	vWidgetInvalidate(pxW);
	if (bTransparent)
		pxW->bInvalidateParent = true;
};


bool bWidgetSetBgPicture(xWidget *pxW, xPicture pusBgPicture) {
	if (!pxW)
		return false;
	bool bInvalidateParent = false;

	if (pxDrawHDL()->usGetPictureW(pusBgPicture) < usWidgetGetW(pxW) || pxDrawHDL()->usGetPictureH(pusBgPicture) < usWidgetGetH(pxW))
		bInvalidateParent = true;

	if (!bWidgetResize(pxW, pxDrawHDL()->usGetPictureW(pusBgPicture), pxDrawHDL()->usGetPictureH(pusBgPicture)))
		return false;
	//do not invalidate if picture is not changed
	if (pxW->pusBgPicture != pusBgPicture) {
		pxW->pusBgPicture = pusBgPicture;
		vWidgetInvalidate(pxW);
	}
	if (!pusBgPicture || bInvalidateParent)
		pxW->bInvalidateParent = true;
	return true;
};

void vWidgetSetVisible(xWidget *pxW, bool bVisible) {
	if (!pxW)
		return;

	if (pxW->bVisible == bVisible)
		return;

	//TODO: add handling of return values
	if (bVisible && pxW->pxOnShow)
		pxW->pxOnShow(pxW);

	if (!bVisible && pxW->pxOnHide)
		pxW->pxOnHide(pxW);

	pxW->bVisible = bVisible;

	if (!bVisible)
		pxW->bInvalidateParent = true;
	else
		vWidgetInvalidate(pxW);

	//For now we are unable to hide interface instance (and any that have no parent)
	//because there's no routine to clear the LCD in that case.
}

bool bWidgetSetCoords(xWidget *pxW, uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, bool bUseWH) {
	if (!pxW)
		return false;
	//TODO: Check sizes before set!

	if (bUseWH) {
		usX1 = usX0 + usX1 - 1;
		usY1 = usY0 + usY1 - 1;
	}

	if (pxW->pxParent != NULL) {
		usX0 += pxW->pxParent->usX0;
		usY0 += pxW->pxParent->usY0;
		usX1 += pxW->pxParent->usX0;
		usY1 += pxW->pxParent->usY0;
	}

	if (pxW->usX0 != usX0 || pxW->usX1 != usX1
		|| pxW->usY0 != usY0 || pxW->usY1 != usY1) {

		pxW->usX0 = usX0;
		pxW->usY0 = usY0;
		pxW->usX1 = usX1;
		pxW->usY1 = usY1;

		pxW->bInvalidateParent = true;
	}

	return true;
}

void prvMoveDXDY(xWidget *pxW, int16_t sDX, int16_t sDY) {
	pxW->usX0 += sDX;
	pxW->usY0 += sDY;

	pxW->usX1 += sDX;
	pxW->usY1 += sDY;

	if (pxW->pxFirstChild) {
		xWidget *pxWidChild = pxW->pxFirstChild;
		while (pxWidChild) {
			prvMoveDXDY(pxWidChild, sDX, sDY);
			pxWidChild = pxWidChild->pxNextSibling;
		}
	}
}

bool bWidgetMoveTo(xWidget *pxW, uint16_t usX0, uint16_t usY0) {
	if (!pxW)
		return false;

	short dX, dY;

	//TODO: Check sizes before set!
	//TODO: decide if we have to invalidate parent (if new size is smaller than old one)

	if (pxW->pxParent != NULL) {
		usX0 += pxW->pxParent->usX0;
		usY0 += pxW->pxParent->usY0;
	}

	dX = usX0 - pxW->usX0;
	dY = usY0 - pxW->usY0;

	if (dX == 0 && dY == 0)
		return false;

	prvMoveDXDY(pxW, dX, dY);

	pxW->bInvalidateParent = true;
	return true;
}

void vWidgetSetOnClickHandler(xWidget *pxW, WidgetEvent pxCallback) {
	if (!pxW)
		return;
	vWidgetSetClickable(pxW, true);
	pxW->pxOnClick = pxCallback;
}

void vWidgetSetOnKeypressHandler(xWidget * pxW, WidgetKeyPressEventHdl pxCallback) {
	if(pxW)
		pxW->pxOnKeypress = pxCallback;
}

void vWidgetSetOnHideHandler(xWidget *pxW, WidgetEvent pxCallback) {
	if (!pxW)
		return;
	pxW->pxOnHide = pxCallback;
}
void vWidgetSetOnShowHandler(xWidget *pxW, WidgetEvent pxCallback) {
	if (!pxW)
		return;
	pxW->pxOnShow = pxCallback;
}

void vWidgetSetDrawHandler(xWidget *pxW, WidgetEvent pxCallback) {
	if (!pxW)
		return;
	pxW->pxDrawHandler = pxCallback;
}

uint16_t usWidgetGetW(xWidget *pxW) {
	if (!pxW)
		return  0;
	return pxW->usX1 - pxW->usX0 + 1;
}

uint16_t usWidgetGetH(xWidget *pxW) {
	if (!pxW)
		return  0;
	return pxW->usY1 - pxW->usY0 + 1;
}

uint16_t usWidgetGetX0(xWidget *pxW, bool bAbsolute) {
	if (!pxW)
		return  0;
	if (!pxW->pxParent)
		return pxW->usX0;

	if (bAbsolute)
		return pxW->usX0;
	else
		return pxW->usX0 - pxW->pxParent->usX0;
}

uint16_t usWidgetGetY0(xWidget *pxW, bool bAbsolute) {
	if (!pxW)
		return  0;
	if (!pxW->pxParent)
		return pxW->usY0;

	if (bAbsolute)
		return pxW->usY0;
	else
		return pxW->usY0 - pxW->pxParent->usY0;
}

uint16_t usWidgetGetX1(xWidget *pxW, bool bAbsolute) {
	if (!pxW)
		return  0;
	if (!pxW->pxParent)
		return pxW->usX1;

	if (bAbsolute)
		return pxW->usX1;
	else
		return pxW->usX1 - pxW->pxParent->usX0;
}

uint16_t usWidgetGetY1(xWidget *pxW, bool bAbsolute) {
	if (!pxW)
		return  0;
	if (!pxW->pxParent)
		return pxW->usY1;

	if (bAbsolute)
		return pxW->usY1;
	else
		return pxW->usY1 - pxW->pxParent->usY0;
}

void * pxWidgetGetProps(xWidget * pxW, eWidgetType eType) {
	if (!bWidgetIs(pxW, eType))
		return NULL;

	return pxW->pvProp;
}

xWidget *pxWidgetGetFirstChild(xWidget *pxW) {
	if (!pxW)
		return  NULL;
	return pxW->pxFirstChild;
}

xWidget *pxWidgetGetNextChild(xWidget *pxW) {
	if (!pxW)
		return  NULL;
	return pxW->pxNextSibling;
}