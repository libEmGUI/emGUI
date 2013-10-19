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
	
	Created on: 19.02.2013
*/

#include "Window.h"
#include "Interface.h"
#include "StatusBar.h"
#include "Memory.h"
#include <string.h>
#include "utils.h"

#define WINDOW_HEADER_LENGTH 25

xWindow * pxWindowCreate(eWindow eWnd){
  xWindowProps *xP;
  xWindow *pxW;

  pxW = pvMemoryMalloc(sizeof(xWidget), MEMORY_EXT);

  if(bWidgetInit(pxW, usInterfaceGetWindowX(), usInterfaceGetWindowY(), usInterfaceGetWindowW(), usInterfaceGetWindowH(), pxInterfaceGet(), TRUE)){

    vWidgetSetBgColor(pxW, 65535, FALSE); //белый фон
    vWidgetSetVisible(pxW, FALSE);

    xP        = pvMemoryMalloc(sizeof(xWindowProps), MEMORY_EXT);

    if(!xP)
      return NULL;

    xP->xBackWindow = NULL;
    xP->pxOnCloseRequest = NULL;
    xP->pxOnClose = NULL;
    xP->pxOnOpenRequest = NULL;
    xP->pxOnOpen = NULL;
    xP->bFullScreen = FALSE;
    xP->eId = eWnd;
    xP->strHeader = pvMemoryMalloc(WINDOW_HEADER_LENGTH + 1, MEMORY_EXT);
    xP->strHeader[0] = '\0';
    pxW->pvProp = xP;
    pxW->eType = WidgetWindow;

    return pxW;
  }
  else{
    vMemoryFree(pxW);
    return NULL;
  }
}

void vWindowSetHeader(xWidget * pxW, char const* strH){
  xWindowProps *xP;
  int iLen = MIN(strlen(strH), WINDOW_HEADER_LENGTH);
 if(!(xP = pxWidgetGetProps(pxW, WidgetWindow)))
   return;
  memcpy(xP->strHeader, strH, iLen + 1);
  xP->strHeader[iLen] = '\0';
  vInterfaceUpdateWindow();
}

void vWindowSetOnCloseRequestHandler(xWidget * pxW, bool (*pxCallback)(xWidget *)){
  xWindowProps *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetWindow)))
    return;
  xP->pxOnCloseRequest = pxCallback;
}

void vWindowSetOnCloseHandler(xWidget * pxW, bool (*pxCallback)(xWidget *)){
  xWindowProps *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetWindow)))
    return;
  xP->pxOnClose = pxCallback;
}

void vWindowSetOnOpenHandler(xWidget * pxW, bool (*pxCallback)(xWidget *)){
  xWindowProps *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetWindow)))
    return;
  xP->pxOnOpen = pxCallback;
}

void vWindowSetOnOpenRequestHandler(xWidget * pxW, bool (*pxCallback)(xWidget *)){
  xWindowProps *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetWindow)))
    return;
  xP->pxOnOpenRequest = pxCallback;
}

xWindow * pxWindowGetBack(xWidget *pxW){
  xWindowProps *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetWindow)))
    return NULL;
  return xP->xBackWindow;
}

void vWindowSetFullScreen(xWidget *pxW, bool bFS){
  xWindowProps *xP;
  if(!(xP = pxWidgetGetProps(pxW, WidgetWindow)))
    return;

  if(bFS){
    if(bWidgetSetCoords(pxW, 0, 0, LCD_SizeX, LCD_SizeY, TRUE))
      xP->bFullScreen = bFS;
  }else{
    if(bWidgetSetCoords(pxW, usInterfaceGetWindowX(), usInterfaceGetWindowY(), usInterfaceGetWindowW(), usInterfaceGetWindowH(), TRUE))
      xP->bFullScreen = bFS;
  }
  vInterfaceUpdateWindow();
}
