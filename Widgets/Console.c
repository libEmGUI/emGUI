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
	
	Created on: 09.12.2012
*/
#ifdef EMGUI_USE_CONSOLE_C

#include "Console.h"
#include "Font.h"
#include "framebuffer.h"
#include "Memory.h"
#include "Window.h"
#include "SysOpts.h"
#include "Fonts.h"

#define CHAR_PLACE_WIDTH  8
#define CHAR_PLACE_HEIGHT 8
#define CONSOLE_COLOR_BG  0
#define CONSOLE_COLOR_FG  65535

xConsole * xDefCon = NULL;

xWindow * xConsoleWnd = NULL;

bool prvDraw(xConsole *pxW){
  xConsoleProps *xP;
  u16 usX, usY;
  
  char cCharOffs = 0;
  u8   ucPrintChar;
  
  u16  usMaxCharPrint;
  
  bool bClearRow = FALSE;
  
  bool bRedraw = FALSE;
  
  xP = pxW->pvProp;
  
  usMaxCharPrint = xP->ucChXCount * xP->ucChXCount;
    
  if(!xP->xqConsole)
    return FALSE;
  
  while(xQueueReceive( xP->xqConsole, &( ucPrintChar ), 0 ) == pdTRUE){
        
    bRedraw = TRUE;
    
    cCharOffs = (CHAR_PLACE_WIDTH - ucFontGetCharW(ucPrintChar, CONSOLE_FONT)) / 2;
    
    usX = xP->ucCaretX * CHAR_PLACE_WIDTH + pxW->usX0;
    usY = xP->ucCaretY * CHAR_PLACE_HEIGHT + pxW->usY0;
    
    usX += cCharOffs;
    
    if(ucPrintChar != '\n' && ucPrintChar != '\r') {
      vFramebufferPutChar(usX, usY, ucPrintChar, FONT_ASCII_8_X, CONSOLE_COLOR_FG, CONSOLE_COLOR_BG, FALSE);
      xP->ucCaretX++;
    }
    else{
      xP->ucCaretX = 0;
      xP->ucCaretY++;
      bClearRow = TRUE;
    }
    
    if(xP->ucCaretX >= xP->ucChXCount){
      xP->ucCaretX = 0;
      xP->ucCaretY++;
      bClearRow = TRUE;
    }
    
    if(xP->ucCaretY >= xP->ucChYCount){
      xP->ucCaretY = 0;
      bClearRow = TRUE;
      xP->usScroll = 1;
    }
    
    if(xP->usScroll){
      xP->usScroll = CHAR_PLACE_WIDTH * (xP->ucCaretY + 1);
    }
    
    if(xP->usScroll > usWidgetGetH(pxW))
      xP->usScroll = 1;
    
    vFramebufferScroll(xP->usScroll);
    
    //Был перенос строки
    if(bClearRow){
      usX = xP->ucCaretX * CHAR_PLACE_WIDTH + pxW->usX0;
      usY = xP->ucCaretY * CHAR_PLACE_HEIGHT + pxW->usY0;
      if(xP->ucCaretY != xP->ucChXCount - 1)
        vFramebufferRectangle(pxW->usX0, usY, pxW->usX1, usY + CHAR_PLACE_HEIGHT, CONSOLE_COLOR_BG, TRUE);
      else
        vFramebufferRectangle(pxW->usX0, usY, pxW->usX1, usY + CHAR_PLACE_HEIGHT, CONSOLE_COLOR_BG, TRUE);
      bClearRow = FALSE;
    }
        
    if(!usMaxCharPrint)
      break;
    usMaxCharPrint--;
  }
  
  return bRedraw;
}

bool prvConsoleDraw(xConsole *pxW){
  
  xConsoleProps *xP;
  
  if(pxW->eType != WidgetConsole)
    return FALSE;
  
  if(!pxW->bVisible)
    return FALSE;
  
  if(pxW->bValid){
    //Do text output here, when console is already valid.
    prvDraw(pxW);
    return FALSE;
  }
  
  xP = pxW->pvProp;
  
  bWidgetDraw(pxW);
  
  xP->ucCaretX = 0;
  xP->ucCaretY = 0;
  xP->usScroll = 0;
  
  /*/if widget is invalid, then make it replot data
  pxW->xProp.xEcgPlot.usLastDrawedPos = 0;
  
  prvDrawGrid(pxW, NULL);
  //for fast redrawing without cursor*/
  pxW->bValid = FALSE;
  prvDraw(pxW);
  pxW->bValid = TRUE;
  
  return TRUE;
}

void vWriteSetCallback( void (*pxCallback) (char));

xConsole * pxConsoleCreate(){
  xConsole *pxW;
  xConsoleProps *xP;
  
  u16 usX0, usY0, usX1, usY1;

  xConsoleWnd = pxWindowCreate(WINDOW_CONSOLE);
  vWindowSetFullScreen(xConsoleWnd, TRUE);

  usX0 = 0;
  usY0 = 0;
  usX1 = usWidgetGetW(xConsoleWnd);
  usY1 = usWidgetGetH(xConsoleWnd);

  if(xDefCon)
    return NULL;  //Console is singleton ATM.
  
  if(!xConsoleWnd)
    return NULL;  //У консоли всегда должен быть родитель. Пока должен быть.
  
  pxW = pxWidgetAlloc();
  
  if(bWidgetInit(pxW, usX0, usY0, usX1, usY1, xConsoleWnd, TRUE)){
    pxW->eType = WidgetConsole;
    vWidgetSetClickable(pxW, FALSE);
    vWidgetSetBgColor(pxW, 0, FALSE);
    
    xP = pvMemoryMalloc(sizeof(xConsoleProps), MEMORY_EXT);
    
    if(!xP)
      return NULL;
    
    xP->ucChXCount = usWidgetGetW(pxW)/CHAR_PLACE_WIDTH; //TODO: Get FontHeight here
    xP->ucChYCount = usWidgetGetH(pxW)/CHAR_PLACE_HEIGHT;  //Using Monotype
    
    xP->ucCaretX = 0;
    xP->ucCaretY = 0;
    xP->usScroll = 0;
    
    xP->xqConsole = xQueueCreate(xP->ucChXCount * xP->ucChYCount, sizeof(char));
    if(!xP->xqConsole)
      return NULL;
    
    pxW->pvProp = xP;
    
    pxW->pxDrawHandler = prvConsoleDraw;
    
    vWriteSetCallback(vConsoleDefPutChar);
    
    xDefCon = pxW;
      
    return pxW;
  }
  
  vMemoryFree(pxW);
  return NULL;
}
    
void vConsoleDefPutChar(char cChar){
  vConsolePutChar(xDefCon, cChar);
}

void vConsolePutChar(xConsole *pxW, char cChar){
  xConsoleProps *xP;
  
  if(!pxW)
    return;
  
  xP = pxW->pvProp;
  
  if(xP->xqConsole && xConsoleWnd && xConsoleWnd->bVisible)
    xQueueSendToBack(xP->xqConsole, &cChar, OS_DELAY_MS(100));
}

void vConsoleSetClickHandler(bool (*pxHandler)(xWidget *)){
  vWidgetSetOnClickHandler(xDefCon, pxHandler);
}

#endif	//__CONSOLE_C
