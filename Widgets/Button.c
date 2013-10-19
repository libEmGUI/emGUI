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
	
	Created on: 15.11.2012
*/

#ifndef __BUTTON_C
#define __BUTTON_C

#include "StatusBar.h"
#include "PictureStorage.h"
#include "framebuffer.h"
#include "Memory.h"

bool static vButtonDraw(xButton *pxW){
  xButtonProps *xP;
  
  if(!pxW)
    return FALSE;
   
  if(pxW->eType != WidgetButton)
    return FALSE;
  
  if(pxW->bValid)
    return FALSE;
  
  xP = pxW->pvProp;
  
  if(!pxW->bPressed){
    if(pxW->pusBgPicture)
      bFramebufferPicture(pxW->usX0, pxW->usY0, pxW->pusBgPicture);
  }
  else if(xP->bEmulatePressure){
    
    if(pxW->pusBgPicture)
      bFramebufferPicture(pxW->usX0, pxW->usY0, pxW->pusBgPicture);
    
    vFramebufferVLine(pxW->usX0 + 2, pxW->usY0 + 2, pxW->usY1 - 2, 0);
    vFramebufferHLine(pxW->usX0 + 2, pxW->usY0 + 2, pxW->usX1 - 2, 0);

    vFramebufferVLine(pxW->usX1 - 2, pxW->usY0 + 2, pxW->usY1 - 2, 65535);
    vFramebufferHLine(pxW->usX0 + 2, pxW->usY1 - 2, pxW->usX1 - 2, 65535);
  }
  
  return TRUE;
}

bool static bButtonCheckTSRoutine(xButton *pxW, xTouchEvent *pxTouchScreenEv){
  xButtonProps *xP;
  
  if(!pxW)
    return FALSE;
  
  xP = pxW->pvProp;

  if(xP->bEmulatePressure)
    vWidgetInvalidate(pxW);
  
  return (pxTouchScreenEv->eventTouchScreen == popTs)?FALSE:TRUE;
}

xButton * pxButtonCreate(u16 usX, u16 usY, unsigned short const* pusPic, xWidget *pxWidParent){
  xButton *pxW;
  xButtonProps *xP;
  
  pxW = pvMemoryMalloc(sizeof(xWidget), MEMORY_EXT);
  
  if(bWidgetInit(pxW, usX, usY, 1, 1, pxWidParent, TRUE)){
    
    bWidgetSetBgPicture(pxW, pusPic);
    
    xP = pvMemoryMalloc(sizeof(xButtonProps), MEMORY_EXT);
    
    if(!xP)
      return NULL;
    
    xP->pusPicDisabled = NULL;
    xP->bEmulatePressure = TRUE;
    
    pxW->pvProp = xP;
    
    pxW->bClickable = TRUE;
    
    pxW->eType = WidgetButton;
      
    pxW->pxDrawHandler = vButtonDraw;
    pxW->pxCheckTSRoutine = bButtonCheckTSRoutine;
    
    return pxW;
  }
  else{
    vMemoryFree(pxW);
    return NULL;
  }
}

bool bButtonSetPushPic(xButton *pxW, unsigned short const* pusPic){
  //xButtonProps *xP;
 
  if(!pxW)
    return NULL;
  
  //xP = pxW->pvProp;
   
  /*xP->bEmulatePressure = pusPic;
  //press picture must be the same size as foreground pic
  
  if(usPictureGetH(pusPic) != usWidgetGetH(pxW))
    return FALSE;
  
  if(usPictureGetW(pusPic) != usWidgetGetW(pxW))
    return FALSE;
  
  if(pxW->bPressed)
    vWidgetInvalidate(pxW);*/
  
  return TRUE;
}

#endif	//__BUTTON_C
