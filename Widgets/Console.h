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
#ifndef __CONSOLE_H
#define __CONSOLE_H

#ifdef EMGUI_USE_CONSOLE_C

#ifdef __cplusplus
extern "C" {
#endif
  
#include "Widget.h"

#define CONSOLE_SCROLLBACK 0
  
typedef xWidget xConsole;

typedef struct xConsoleProps_struct {
  char ucChXCount;
  char ucChYCount;
  char ucCaretX;
  char ucCaretY;
  u16  usScroll; //if 0 no scrolling is needed, if > 0 scroll to usScroll - 1;
  xQueueHandle xqConsole;
} xConsoleProps;

xConsole * pxConsoleCreate();
  
void vConsoleDefPutChar(char cChar);
void vConsolePutChar(xConsole *pxW, char cChar);
void vConsoleSetClickHandler(bool (*pxHandler)(xWidget *));

#ifdef __cplusplus
}
#endif

#endif

#endif	//__CONSOLE_H
