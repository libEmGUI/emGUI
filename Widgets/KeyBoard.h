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
	
	Created on: 06.05.2013
*/
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#ifdef EMGUI_USE_KEYBOARD

#ifdef __cplusplus
extern "C" {
#endif

#include "KeyRow.h"

#define LETERS_ROW_COUNT 4
#define MAX_KEY_COUNT 12
#define MAX_ROW_COUNT 5

typedef xWidget xKeyBoard;

typedef struct xKeyBoardProp_t{
  xKeyRow *pxWNumsRow;
  xKeyRow *pxWLettersRow[LETERS_ROW_COUNT];
  xKeyRow *pxWSpace;
  xKeyRow *pxWBackSpace;
  xKeyRow *pxWShift;
  xKeyRow *pxWEnter;
  xKeyRow *pxWClear;
  void (*prvOnKeyPress)(xWidget*, char);
} xKeyBoardProp;

xWidget* pxKeyBoardCreate(u16 usX, u16 usY, u16 usKeyLineColor, u16 usKeyBcgColor, xWidget *pxWidParent);
void vKeyBoardSetOnKeyPressHandler(xWidget *pxW, void (*Callback)(xWidget*, char));
void vOnKeyRowPress(xKeyBoard *pxKRow, char cPress);

#ifdef __cplusplus
}
#endif

#endif

#endif /* KEYBOARD_H_ */
