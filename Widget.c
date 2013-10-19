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

#ifndef __WIDGET_C
#define __WIDGET_C

#include "widget.h"
#include <stdlib.h>
#include <stdio.h>
#include "Interface.h"
#include "PictureStorage.h"
#include "framebuffer.h"
#include "Memory.h"

xWidget * pxWidgetAlloc(){
  return pvMemoryMalloc(sizeof(xWidget), MEMORY_EXT);
}

xWidget * pxWidgetCreate(u16 usX0, u16 usY0, u16 usX1, u16 usY1, xWidget *pxWidParent, bool bUseWH){
  xWidget *pxW;
  pxW = pvMemoryMalloc(sizeof(xWidget), MEMORY_EXT);
  
  if(!pxW)
    return NULL;
  
  if(bWidgetInit(pxW, usX0, usY0, usX1, usY1, pxWidParent, bUseWH))
    return pxW;
  else{
    vMemoryFree(pxW);
    return NULL;
  }
}

bool bWidgetInit(xWidget *pxW, u16 usX0, u16 usY0, u16 usX1, u16 usY1, xWidget *pxWidParent, bool bUseWH){
  if(!pxW)
    return FALSE;
  
  pxW->eType = Widget;
  
  pxW->pxParent = pxWidParent;
  
  pxW->bValid = FALSE;
  pxW->bInvalidate = TRUE;
  pxW->bInvalidateParent = FALSE;
  pxW->bClickable = FALSE;
  pxW->bVisible = TRUE;
  pxW->bEnabled = TRUE;
  pxW->bPressed = FALSE;
  pxW->bPushEventCaught = FALSE;
  
  pxW->bTransparent = TRUE;
  pxW->usBgColor = 0;
  pxW->pusBgPicture = NULL;
  
  pxW->pxDrawHandler = NULL;
  pxW->pxCheckTSRoutine = NULL;
  pxW->pxOnClick = NULL;
  pxW->pxOnShow = NULL;
  pxW->pxOnHide = NULL;
  
  pxW->pvProp = NULL;
  
  pxW->pxChild = NULL; //Виджеты - дети
  
  pxW->pxNextSibling = NULL; //Список соседей (прямых потомков одного родителя)
  
  //TODO: check LCD sizes
  if(!bWidgetSetCoords(pxW, usX0, usY0, usX1, usY1, bUseWH))
    return FALSE;
  
  if(pxWidParent != NULL) {
    bWidgetAdd(pxWidParent, pxW);
  }
  
  return TRUE;
}

void vWidgetInvalidate(xWidget *pxW){
  pxW->bInvalidate = TRUE;
}

static void prvInvalidateChilds(xWidget *pxW){
  if(pxW->pxChild){
    xWidget *pxWidChild = pxW->pxChild;
    while(pxWidChild){
      vWidgetInvalidate(pxWidChild);
      pxWidChild = pxWidChild->pxNextSibling;
    }
  }
}

/*void vWidgetEnabled(xWidget *pxW, bool bEnabled){
  pxW->bEnabled = bEnabled;
    
  //Disable chlidren
}*/

bool bWidgetDraw(xWidget *pxW){
  if(!pxW)
    return FALSE;
  
  if(pxW->bValid)
    return FALSE;
  
  if(pxW->pusBgPicture){
    bFramebufferPicture(pxW->usX0, pxW->usY0, pxW->pusBgPicture);
    return TRUE;
  } 
  
  if(!pxW->bTransparent){
    vFramebufferRectangle(pxW->usX0, pxW->usY0, pxW->usX1, pxW->usY1, pxW->usBgColor, TRUE);
    return TRUE;
  }
  
  return FALSE;
}

void vWidgetDraw(xWidget *pxW){
  if(!pxW)
    return;
  
  bool bRedrawed = FALSE;
  
  //We don't need to redraw widget and children tree if it is not visible
  if(!pxW->bVisible)
    return;
  
  if(pxW->bInvalidateParent)
    return;
  
  //Проверка ближайших детей на предмет установленного флага bWidgetInvalidateParent
  if(pxW->pxChild){
    xWidget *pxWidChild = pxW->pxChild;
    while(pxWidChild){
      if(pxWidChild->bInvalidateParent){
        pxWidChild->bInvalidateParent = FALSE;
        pxW->bInvalidate = TRUE;
      }
      pxWidChild = pxWidChild->pxNextSibling;
    }
  }
  
  //анализ флага инвалидации
  if(pxW->bInvalidate){
    prvInvalidateChilds(pxW);
    pxW->bValid = FALSE;
    pxW->bInvalidate = FALSE;
  }
  
  if(pxW->pxDrawHandler)
    bRedrawed = pxW->pxDrawHandler(pxW);
  else
    bRedrawed = bWidgetDraw(pxW);
  
  if(pxW->pxChild){
    xWidget *pxWidChild = pxW->pxChild;
    while(pxWidChild){
      vWidgetDraw(pxWidChild);
      pxWidChild = pxWidChild->pxNextSibling;
    }
  }
  
  //Валидируем виджет
  pxW->bValid = TRUE;

  if(bInterfaceGetDebug() && bRedrawed)
    vFramebufferRectangle(pxW->usX0, pxW->usY0, pxW->usX1, pxW->usY1, rand(), FALSE);
  
}

bool bWidgetAdd(xWidget *pxWidParent, xWidget *pxWidChild){
  if(!pxWidChild || !pxWidParent)
    return FALSE;
  xWidget *pxW, *pxWidLast;
  
  //TODO: check for duplicates via pointer address
  //TODO: check for duplicates in children to prevent recursion
  if(!pxWidParent->pxChild)
    pxWidParent->pxChild = pxWidChild;
  else{
    pxW = pxWidParent->pxChild;
    while(pxW){ //iterate through the list of children
      pxWidLast = pxW;
      pxW = pxW->pxNextSibling;
    }
    pxWidLast->pxNextSibling = pxWidChild;
  }
  
  return TRUE;
}

bool bWidgetCheckTouchScreenEvent(xWidget *pxW, xTouchEvent *pxTouchScreenEv){
  if(!pxW)
    return FALSE;
  //By default catching an event doesn't invalidate the widget.
  //Enherited widgets should invalidate itself from pxCheckTSRoutine
  //bPressed state is controlled via return value of pxCheckTSRoutine
  
  if(!pxW->bVisible)
    return FALSE;
  
  if(!pxW->bEnabled)
    return FALSE;
  
  //handle popTs events when they occur out of the Widget area
  if(   pxTouchScreenEv->eventTouchScreen == popTs
     && pxW->bPushEventCaught ){
    if(pxW->pxCheckTSRoutine)
     pxW->bPressed = pxW->pxCheckTSRoutine(pxW, pxTouchScreenEv);
    else
      pxW->bPressed = FALSE;
    pxW->bPushEventCaught = FALSE;
    //Fire OnClick event
    if(pxW->pxOnClick && !pxW->bPressed)
      pxW->pxOnClick(pxW);
    
    //TODO: add timeout for releasing buttons if we lost popTs message
    
    /*if(bInterfaceGetDebug() && !pxW->bPressed)
      MDEBUG("Widget release @ %x\n", pxW);*/
  }
  
  if(pxW->pxChild){
    xWidget *pxWidChild = pxW->pxChild;
    while(pxWidChild){
      if(bWidgetCheckTouchScreenEvent(pxWidChild, pxTouchScreenEv))
        return TRUE;
      pxWidChild = pxWidChild->pxNextSibling;
    }
  }
  
  if(!pxW->bClickable)
    return FALSE;
  
  //TODO: check by radius?
  if(   pxW->usX0 <= pxTouchScreenEv->xTouchScreen 
     && pxW->usX1 >= pxTouchScreenEv->xTouchScreen
     && pxW->usY0 <= pxTouchScreenEv->yTouchScreen
     && pxW->usY1 >= pxTouchScreenEv->yTouchScreen
     && pxTouchScreenEv->eventTouchScreen == pushTs ){
    if(pxW->pxCheckTSRoutine)
      pxW->bPressed = pxW->pxCheckTSRoutine(pxW, pxTouchScreenEv);
    else
      pxW->bPressed = TRUE;
    
    pxW->bPushEventCaught = TRUE;
    return TRUE;
  }
  
  return FALSE;
}

void vWidgesSetClickable(xWidget *pxW, bool bClickable){
  if(!pxW)
    return;
  pxW->bClickable = bClickable;
}

void vWidgetSetBgColor(xWidget *pxW, u16 usBgColor, bool bTransparent){
  if(!pxW)
    return;
  pxW->usBgColor = usBgColor;
  pxW->bTransparent = FALSE;
  
  //TODO: handle transparency color???
  vWidgetInvalidate(pxW);
};

void vWidgetSetTransparency(xWidget *pxW, bool bTransparent){
  if(!pxW)
    return;
  pxW->bTransparent = bTransparent;
  vWidgetInvalidate(pxW);
  if(bTransparent)
    pxW->bInvalidateParent = TRUE;
};

bool bWidgetSetBgPicture(xWidget *pxW, unsigned short const* pusBgPicture){
  if(!pxW)
    return FALSE;
  bool bInvalidateParent = FALSE;
  
  if(usPictureGetW(pusBgPicture) < usWidgetGetW(pxW) || usPictureGetH(pusBgPicture) < usWidgetGetH(pxW))
    bInvalidateParent = TRUE;
  
  if(!bWidgetResize(pxW, usPictureGetW(pusBgPicture), usPictureGetH(pusBgPicture)))
    return FALSE;
  //do not invalidate if picture is not changed
  if(pxW->pusBgPicture != pusBgPicture){
    pxW->pusBgPicture = pusBgPicture;
    vWidgetInvalidate(pxW);
  }
  if(!pusBgPicture || bInvalidateParent)
    pxW->bInvalidateParent = TRUE;
  return TRUE;
};

void vWidgetSetVisible(xWidget *pxW, bool bVisible){
  if(!pxW)
    return;
  
  if(pxW->bVisible == bVisible)
    return;
  
  //TODO: add handling of return values
  if(bVisible && pxW->pxOnShow)
    pxW->pxOnShow(pxW);
  
  if(!bVisible && pxW->pxOnHide)
    pxW->pxOnHide(pxW);
  
  pxW->bVisible = bVisible;
  
  if(!bVisible)
    pxW->bInvalidateParent = TRUE;
  else
    vWidgetInvalidate(pxW);
  
  //For now we are unable to hide interface instance (and any that have no parent)
  //because there's no routine to clear the LCD in that case.
}

void vWidgetSetClickable(xWidget *pxW, bool bClickable){
  if(!pxW)
    return;
  pxW->bClickable = bClickable;
}

bool bWidgetSetCoords(xWidget *pxW, u16 usX0, u16 usY0, u16 usX1, u16 usY1, bool bUseWH){
  if(!pxW)
    return FALSE;
  //TODO: Check sizes before set!
  
  if(bUseWH){
    usX1 = usX0 + usX1 - 1;
    usY1 = usY0 + usY1 - 1;
  }
  if(pxW->pxParent != NULL) {
    usX0 += pxW->pxParent->usX0;
    usY0 += pxW->pxParent->usY0;
    usX1 += pxW->pxParent->usX0;
    usY1 += pxW->pxParent->usY0;
  }
  
  if(pxW->usX0 != usX0 || pxW->usX1 != usX1
     ||pxW->usY0 != usY0 || pxW->usY1 != usY1){
  
    pxW->usX0 = usX0;
    pxW->usY0 = usY0;
    pxW->usX1 = usX1;
    pxW->usY1 = usY1;
    
    pxW->bInvalidateParent = TRUE;
  }
  
  return TRUE;
}

void prvMoveDXDY(xWidget *pxW, s16 sDX, s16 sDY){
  pxW->usX0 += sDX;
  pxW->usY0 += sDY;

  pxW->usX1 += sDX;
  pxW->usY1 += sDY;

  if(pxW->pxChild){
    xWidget *pxWidChild = pxW->pxChild;
    while(pxWidChild){
      prvMoveDXDY(pxWidChild, sDX, sDY);
      pxWidChild = pxWidChild->pxNextSibling;
    }
  }
}

bool bWidgetMoveTo(xWidget *pxW, u16 usX0, u16 usY0){
  if(!pxW)
    return FALSE;

  short dX, dY;

  //TODO: Check sizes before set!
  //TODO: decide if we have to invalidate parent (if new size is smaller than old one)

  if(pxW->pxParent != NULL) {
    usX0 += pxW->pxParent->usX0;
    usY0 += pxW->pxParent->usY0;
  }

  dX = usX0 - pxW->usX0;
  dY = usY0 - pxW->usY0;
  
  if(dX == 0 && dY == 0)
    return FALSE;

  prvMoveDXDY(pxW, dX, dY);
  
  pxW->bInvalidateParent = TRUE;
  return TRUE;
}

void vWidgetSetOnClickHandler(xWidget *pxW, bool (*pxCallback)(xWidget *)){
  if(!pxW)
    return;
  vWidgetSetClickable(pxW, TRUE);
  pxW->pxOnClick = pxCallback;
}
void vWidgetSetOnHideHandler(xWidget *pxW, bool (*pxCallback)(xWidget *)){
  if(!pxW)
    return;
  pxW->pxOnHide = pxCallback;
}
void vWidgetSetOnShowHandler(xWidget *pxW, bool (*pxCallback)(xWidget *)){
  if(!pxW)
    return;
  pxW->pxOnShow = pxCallback;
}

void vWidgetSetDrawHandler(xWidget *pxW, bool (*pxCallback)(xWidget *)){
  if(!pxW)
    return;
  pxW->pxDrawHandler = pxCallback;
}

#endif  //__WIDGET_C
