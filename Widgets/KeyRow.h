/*
	emGUI Library V1.0.0 - Copyright (C) 2013 Lemeshev K <konstantin.lemeshev@gmail.com>

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
	
	Created on: 01.05.2013
*/
#include "Widget.h"

#ifdef EMGUI_USE_KEYBOARD

#ifndef EMGUI_KEYROW_H
#define EMGUI_KEYROW_H

#ifdef __cplusplus
extern "C" {
#endif

typedef xWidget xKeyRow;


typedef struct xKeyRowProp_t{
  u16 usKeyCount;
  u16 usKeyWidth;
  u16 usKeyHeight; // высоту хранить не надо? - она есть в виджете и постоянна
  const char *pcKeys;
  u16 usKeyClicked;    // порядковый номер клавишы с событием клик
  u16 usKeyLinesColor;
  void (*prvOnKeyPress)(xWidget*, char);
} xKeyRowProp;

xWidget* pxKeyRowCreate(u16 usX, u16 usY, u16 usKeyHeight, u16 usKeyWidth, u16 usKeyCount, const char *pcKeysChar, u16 usKeyLinesColor, u16 usKeyBcgColor, xWidget *pxWidParent);
void vKeyRowSetOnPressHandler(xKeyRow *pxW, void (*pxCallback)(xWidget*, char));
bool bKeyRowSetKeysSymbols(xWidget* pxW, const char *cpcNewKeys);

#ifdef __cplusplus
}
#endif

#endif

#endif /* _H_ */
