/*
	emGUI Library V1.0.0 - Copyright (C) 2013 
	Lemeshev K <konstantin.lemeshev@gmail.com>, 
	

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
	
	Created on: 14.06.2013
*/


#ifdef EMGUI_USE_PROGRESS_BAR

#include "ProgressBar.h"
#include "Widget.h"
#include "Memory.h"
#include "Fonts.h"
#include "framebuffer.h"
#include "Color.h"
#include <string.h>
#include <stdio.h>
  #include "Draw/Draw.h"

static char *pcBarText = "Выполнено";

static bool prvDraw(xWidget *pxW){
  xProgressBarProps *xP;

  if (!(xP = pxWidgetGetProps(pxW, WidgetProgressBar)))
    return FALSE;

  if(pxW->bValid)
    return FALSE;
// Draw:
  bWidgetDrawHandler(pxW);

  u16 usXfrom = pxW->usX0 + 1;
  u16 usXto = pxW->usX0 + ((pxW->usX1 - 1 - pxW->usX0) * xP->usExProc) / 100;
  u16 usYfrom = pxW->usY0 + usWidgetGetH(xP->pxBarLabel);
  u16 usYto = pxW->usY1 - 1;

  vFramebufferRectangle(pxW->usX0, usYfrom, pxW->usX1 - 1, usYto, 0, FALSE);

  usYfrom++;
  usYto--;
  while (usXfrom <= usXto - 1){
    vFramebufferVLine(usXfrom, usYfrom, usYto, xP->usBarColor);
    ++usXfrom;
  }

  return TRUE;
}

xProgressBar* pxProgressBarCreate(u16 usX, u16 usY, u16 usW, u16 usH, xWidget *pxWidParent){
  xProgressBar *pxW;
  xProgressBarProps *xP;

  if (usH < usFontGetStrH(pcBarText, EM_GUI_MIDDLE_FONT) + 4)
    usH = usFontGetStrH(pcBarText, EM_GUI_MIDDLE_FONT) + 4;

  pxW = pxWidgetCreate(usX, usY, usW, usH, pxWidParent, TRUE);
  pxW->eType = WidgetProgressBar;
  vWidgetSetBgColor(pxW, 65535, FALSE);
  vWidgetSetTransparency(pxW, FALSE);
  vWidgesSetClickable(pxW, FALSE);
  pxW->pxDrawHandler = prvDraw;

  xP = pvMemoryMalloc(sizeof(xProgressBarProps), MEMORY_EXT);
  xP->usBarColor = ColorMessageHeaderBackground;
  xP->usExProc = 0;

  xP->pxBarLabel = pxLabelCreate(0, 0, usW, usFontGetStrH(pcBarText, EM_GUI_MIDDLE_FONT) + 2, pcBarText, EM_GUI_MIDDLE_FONT, strlen(pcBarText) + 5, pxW);
  vLabelSetTextAlign(xP->pxBarLabel, LABEL_ALIGN_CENTER);
  vLabelSetVerticalAlign(xP->pxBarLabel, LABEL_ALIGN_MIDDLE);

  pxW->pvProp = xP;

  return pxW;
}

void vProgressBarSetProcExec(xWidget *pxW, u16 usExecProc){
  xProgressBarProps *xP;
  char pcText[strlen(pcBarText) + 5];

  if (!(xP = pxWidgetGetProps(pxW, WidgetProgressBar)))
    return ;

  if (usExecProc > 100)
    usExecProc = 100;
  
  if(xP->usExProc == usExecProc)
    return;

  sprintf(pcText, "%s %d%c", pcBarText, usExecProc, '%');
  pcLabelSetText(xP->pxBarLabel, pcText);
  xP->usExProc = usExecProc;
  
  vWidgetInvalidate(pxW);
}

#endif

