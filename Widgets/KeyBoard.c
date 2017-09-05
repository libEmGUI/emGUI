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
#ifdef EMGUI_USE_KEYBOARD

#include "Widget.h"
#include "KeyRow.h"
#include "memory.h"
#include "KeyBoard.h"
#include <string.h>

static const u16 usKeyWidth = 25;
static const u16 usKeyHeight = 25;

static const char cpcNums[] = "1234567890";
static const char cpcLetters[LETERS_ROW_COUNT][MAX_KEY_COUNT + 1] = {"éöóêåíãøùç:;", "ôûâàïðîëäæ!?", "ÿ÷ñìèòüáþúýõ", ".,-"};
static const char cpcLettersUp[LETERS_ROW_COUNT][MAX_KEY_COUNT + 1] = {"ÉÖÓÊÅÍÃØÙÇ:;", "ÔÛÂÀÏÐÎËÄÆ!?", "ß×ÑÌÈÒÜÁÞÚÝÕ", ".,-"};
static const char cpcSpace[2] = " ";
static const char cpcBackSpace[2] = {8,0}; //char numbers from font16.c
static const char cpcShift[2] = {7,0};
static const char cpcEnter[2] = {6,0};
static const char cpcClear[2] = {5,0};

static bool bShiftIsPressed;

xWidget* pxKeyBoardCreate(u16 usX, u16 usY, u16 usKeyLineColor, u16 usKeyBcgColor, xWidget *pxWidParent){
  xWidget *pxW;
  xKeyBoardProp *xP;
  pxW = pxWidgetCreate(usX, usY, usKeyWidth * MAX_KEY_COUNT, usKeyHeight * MAX_ROW_COUNT, pxWidParent, TRUE);
  pxW->pxParent = pxWidParent;
  xP = pvMemoryMalloc(sizeof(xKeyBoardProp), MEMORY_EXT);
  pxW->pvProp = xP;
  u16 usXR = 0;
  u16 usYR = 0;
// Num Keys
  xP->pxWNumsRow = pxKeyRowCreate(usXR, usYR, usKeyHeight, usKeyWidth, strlen(cpcNums),
                                  cpcNums, usKeyLineColor, usKeyBcgColor, pxW);
  vKeyRowSetOnPressHandler(xP->pxWNumsRow, vOnKeyRowPress);
  usXR+= usWidgetGetW(xP->pxWNumsRow);
// BackSpace Key
  xP->pxWBackSpace = pxKeyRowCreate(usXR, usYR, usKeyHeight, usKeyWidth * 2, 1, cpcBackSpace, usKeyLineColor, usKeyBcgColor, pxW);
  vKeyRowSetOnPressHandler(xP->pxWBackSpace, vOnKeyRowPress);
  usXR = 0;
  usYR+= usWidgetGetH(xP->pxWBackSpace);
// Letters Keys
  for(int i = 0; i < LETERS_ROW_COUNT; ++i){
    if (i == LETERS_ROW_COUNT - 1) // îòñòóï äëÿ êëàâèøè Clear â ïîñëåäíåì ðÿäó
      usXR+= usKeyWidth;
    xP->pxWLettersRow[i] = pxKeyRowCreate(usXR, usYR, usKeyHeight, usKeyWidth, strlen(cpcLetters[i]),
                                          cpcLetters[i], usKeyLineColor, usKeyBcgColor, pxW);
    vKeyRowSetOnPressHandler(xP->pxWLettersRow[i], vOnKeyRowPress);
    if (i == LETERS_ROW_COUNT - 1)
      break;
    usYR+= usWidgetGetH(xP->pxWLettersRow[i]);
  }
  usXR = 0;
// Clear Key
  xP->pxWClear = pxKeyRowCreate(usXR, usYR, usKeyHeight, usKeyWidth, 1, cpcClear, usKeyLineColor, usKeyBcgColor, pxW);
  vKeyRowSetOnPressHandler(xP->pxWClear, vOnKeyRowPress);
  usXR+= usWidgetGetW(xP->pxWClear) + usWidgetGetW(xP->pxWLettersRow[LETERS_ROW_COUNT-1]);
// Space Key
  xP->pxWSpace = pxKeyRowCreate(usXR, usYR, usKeyHeight, usKeyWidth*4, 1, cpcSpace, usKeyLineColor, usKeyBcgColor, pxW);
  vKeyRowSetOnPressHandler(xP->pxWSpace, vOnKeyRowPress);
  usXR+= usWidgetGetW(xP->pxWSpace);
// Shift Key
  xP->pxWShift = pxKeyRowCreate(usXR, usYR, usKeyHeight, usKeyWidth * 2, 1, cpcShift, usKeyLineColor, usKeyBcgColor, pxW);
  vKeyRowSetOnPressHandler(xP->pxWShift, vOnKeyRowPress);
  usXR+= usWidgetGetW(xP->pxWShift);
// Enter Key
  xP->pxWEnter = pxKeyRowCreate(usXR, usYR, usKeyHeight, usKeyWidth * 2, 1, cpcEnter, usKeyLineColor, usKeyBcgColor, pxW);
  vKeyRowSetOnPressHandler(xP->pxWEnter, vOnKeyRowPress);

  bShiftIsPressed = FALSE;
  xP->prvOnKeyPress = NULL;
  pxW->eType = WidgetKeyBoard;
  return pxW;
}



bool prvKeyBoardSetUpLetters(xWidget *pxW){
  xKeyBoardProp *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetKeyBoard)))
    return FALSE;

  if (!bShiftIsPressed)
    if (bKeyRowSetKeysSymbols(xP->pxWLettersRow[0], cpcLettersUp[0]) && bKeyRowSetKeysSymbols(xP->pxWLettersRow[1], cpcLettersUp[1])
        && bKeyRowSetKeysSymbols(xP->pxWLettersRow[2], cpcLettersUp[2]))
      return TRUE;

  if (bShiftIsPressed)
    if (bKeyRowSetKeysSymbols(xP->pxWLettersRow[0], cpcLetters[0]) && bKeyRowSetKeysSymbols(xP->pxWLettersRow[1], cpcLetters[1])
        && bKeyRowSetKeysSymbols(xP->pxWLettersRow[2], cpcLetters[2]))
      return TRUE;

  return FALSE;
}

void vOnKeyRowPress(xWidget *pxKRow, char cPress){

  xKeyBoardProp *pxKBoardProp;
  if ((pxKBoardProp = pxWidgetGetProps(pxKRow->pxParent, WidgetKeyBoard))){
// îáðàáîòêà Shift:
    if (pxKRow == pxKBoardProp->pxWShift){
      if (prvKeyBoardSetUpLetters(pxKRow->pxParent))
        bShiftIsPressed = (bShiftIsPressed)?FALSE:TRUE;
    }
// Callback:
    if (pxKBoardProp->prvOnKeyPress)
      pxKBoardProp->prvOnKeyPress(pxKRow, cPress);
  }
}

void vKeyBoardSetOnKeyPressHandler(xWidget *pxW, void (*Callback)(xWidget*, char)){
  xKeyBoardProp *xP;
  if((xP = pxWidgetGetProps(pxW, WidgetKeyBoard)) && Callback)
    xP->prvOnKeyPress = Callback;
}

#endif // EMGUI_USE_CONSOLE_C