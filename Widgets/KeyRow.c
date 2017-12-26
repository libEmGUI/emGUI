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
#ifdef EMGUI_USE_KEYBOARD

#include "Widget.h"
#include "color.h"
#include "Fonts.h"
#include "memory.h"
#include "framebuffer.h"
#include "KeyRow.h"
#include "TouchScreen.h"
#include <string.h>

#define FONT_SIZE EM_GUI_MIDDLE_FONT
#define KEY_BACKSPACE "backspace"
#define KEY_SHIFT "shift"

bool bKeyRowCheckRoutine(xWidget *pxW, xTouchEvent *pxT){
  xKeyRowProp *xP;
  if (!(xP = pxWidgetGetProps(pxW, WidgetKeyRow)))
    return FALSE;
  if (pxT->eventTouchScreen == pushTs) // Determ Num of Cliked Key pushTs turn pxW->bPressed TRUE
    xP->usKeyClicked = (pxT->xTouchScreen - pxW->usX0)/xP->usKeyWidth;
  if (pxT->eventTouchScreen == popTs && xP->prvOnKeyPress)
    xP->prvOnKeyPress(pxW, xP->pcKeys[xP->usKeyClicked]);
  vWidgetInvalidate(pxW);
  return (pxT->eventTouchScreen == pushTs)?TRUE:FALSE;
}

static void prvDrawCharKey(u16 usX, u16 usY, u16 usKeyW, u16 usKeyH, char character, u16 usColor, u16 usBcgColor){
  vFramebufferVLine(usX, usY, usY + usKeyH, usColor);
  vFramebufferVLine(usX + usKeyW, usY, usY + usKeyH, usColor);
  vFramebufferHLine(usX, usY, usX + usKeyW, usColor);
  vFramebufferHLine(usX, usY + usKeyH, usX + usKeyW, usColor);
  u16 usCharH =  usFontGetStrH(&character, FONT_SIZE);
  u16 usCharW = usFontGetStrW(&character, FONT_SIZE);
if(usCharH < usKeyH && usCharW < usKeyW)
  vFramebufferPutChar(usX + (usKeyW - usCharW)/2, usY + (usKeyH - usCharH), character, FONT_SIZE, usColor, usBcgColor, TRUE);
}

static void prvFillPressedKey(xWidget *pxW){
  xKeyRowProp *xP;
  if ((xP = pxWidgetGetProps(pxW, WidgetKeyRow))){
    u16 usX = pxW->usX0 + xP->usKeyWidth * xP->usKeyClicked;
    vFramebufferRectangle(usX, pxW->usY0, usX + xP->usKeyWidth, pxW->usY0 + xP->usKeyHeight, xP->usKeyLinesColor, TRUE);
    prvDrawCharKey(usX, pxW->usY0, xP->usKeyWidth, xP->usKeyHeight, xP->pcKeys[xP->usKeyClicked], pxW->usBgColor, xP->usKeyLinesColor);
  }
}

static bool prvDrawKeyRow(xWidget *pxW){
  xKeyRowProp *xP;
  if (!(xP = pxWidgetGetProps(pxW, WidgetKeyRow)))
    return FALSE;

  if(pxW->bValid)
    return FALSE;
// Draw:
  bWidgetDraw(pxW);
  u16 usX = pxW->usX0;
  for(int i = 0; i != xP->usKeyCount && i*xP->usKeyWidth < EMGUI_LCD_WIDTH ; ++i){
    prvDrawCharKey(usX, pxW->usY0, xP->usKeyWidth, xP->usKeyHeight, xP->pcKeys[i], xP->usKeyLinesColor, pxW->usBgColor);
    usX+= xP->usKeyWidth;
  }
  if (pxW->bPressed)
    prvFillPressedKey(pxW);
  return TRUE;
}

xWidget* pxKeyRowCreate(u16 usX, u16 usY, u16 usKeyHeight, u16 usKeyWidth, u16 usKeyCount, const char *pcKeysChar, u16 usKeyLinesColor, u16 usKeyBcgColor, xWidget *pxWidParent){
  xWidget *pxW;
  xKeyRowProp *xP;
  pxW = pxWidgetCreate(usX, usY, usKeyCount * usKeyWidth, usKeyHeight, pxWidParent, TRUE);
  pxW->pxParent = pxWidParent;
  xP = pvMemoryMalloc(sizeof(xKeyRowProp), MEMORY_EXT);
  pxW->pvProp = (xKeyRowProp*)xP;
  xP->usKeyLinesColor = usKeyLinesColor;
  xP->usKeyWidth = usKeyWidth;
  xP->usKeyHeight = usKeyHeight;
  xP->pcKeys = pcKeysChar;
  xP->pcKeys = pcKeysChar;
  xP->usKeyCount = usKeyCount;
  xP->prvOnKeyPress = NULL;
  pxW->eType =  WidgetKeyRow;
  pxW->usBgColor = usKeyBcgColor;
  pxW->bTransparent = FALSE;
  pxW->bClickable = TRUE;
  pxW->pxCheckTSRoutine = bKeyRowCheckRoutine;
  pxW->pxDrawHandler = prvDrawKeyRow;
  return pxW;
}

void vKeyRowSetOnPressHandler(xKeyRow *pxW, void (*pxCallback)(xWidget*, char)){
  xKeyRowProp *xP;
  if((xP = pxWidgetGetProps(pxW, WidgetKeyRow))){
    xP->prvOnKeyPress = pxCallback;
  }
}

bool bKeyRowSetKeysSymbols(xWidget* pxW, const char *cpcNewKeys){
  xKeyRowProp *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetKeyRow)))
      return FALSE;

  if(strlen(cpcNewKeys) != strlen(xP->pcKeys))
    return FALSE;
// Set Keys Symbols:
  xP->pcKeys = cpcNewKeys;
  vWidgetInvalidate(pxW);
  return TRUE;
}


#endif 