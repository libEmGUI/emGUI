/*
	emGUI Library V1.0.0 - Copyright (C) 2013 
	Roman Savrulin <romeo.deepmind@gmail.com>
	

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
	
	Created on: 24.12.2012
*/
#ifdef EMGUI_USE_PICTURE_STACK_C

#include "PictureStack.h"
#include "StatusBar.h"
#include "PictureStorage.h"
#include "framebuffer.h"
#include "Memory.h"

bool static prvDraw(xPictureStack *pxW){
  xPictureStackProps *xP;
  
  if(!pxW)
    return FALSE;
  
  if(pxW->eType != WidgetPictureStack)
    return FALSE;
  
  if(pxW->bValid)
    return FALSE;
  
  xP = pxW->pvProp;
  
  bFramebufferPicture(pxW->usX0, pxW->usY0, xPictureStackGetItem(pxW, xP->cItemNumber));
  return TRUE;
}

xPictureStack *pxPictureStackCreate(u16 usX, u16 usY, xPicture xPic, xWidget *pxWidParent){
  xPictureStack *pxW;
  xPictureStackProps *xP;
  xPictureStackItem *xI;
  
  pxW = pvMemoryMalloc(sizeof(xWidget), MEMORY_EXT);
  
  if(bWidgetInit(pxW, usX, usY, 1, 1, pxWidParent, TRUE)){
    
    bWidgetSetBgPicture(pxW, xPic);
    
    xI = pvMemoryMalloc(sizeof(xPictureStackItem), MEMORY_EXT);

    if(!xI)
      return NULL;

    xI->xPic = xPic;
    xI->pxNext = NULL;

    xP = pvMemoryMalloc(sizeof(xPictureStackProps), MEMORY_EXT);
    
    if(!xP)
      return NULL;

    xP->cItemNumber = 0;
    xP->cItemCount = 1;

    xP->xItems = xI;
    
    pxW->pvProp = xP;
        
    pxW->eType = WidgetPictureStack;
      
    pxW->pxDrawHandler = prvDraw;
    
    return pxW;
  }
  else{
    vMemoryFree(pxW);
    return NULL;
  }
}

bool bPictureStackSelect(xWidget *pxW, char cItemNumber){
  xPictureStackProps *xP;
  
  if(!pxW)
    return FALSE;
  
  if(pxW->eType != WidgetPictureStack)
    return FALSE;
  
  xP = pxW->pvProp;
  
  if(cItemNumber >= xP->cItemCount)
    return FALSE;
  
  if(cItemNumber == xP->cItemNumber)
    return TRUE;
  
  xP->cItemNumber = cItemNumber;
  vWidgetInvalidate(pxW);
  
  return TRUE;
}

bool bPictureStackAddItem(xWidget *pxW, xPicture xPic){
  xPictureStackProps *xP;
  xPictureStackItem *xI;
  xPictureStackItem *xNext;
  
  if(!pxW)
    return FALSE;
  
  if(pxW->eType != WidgetPictureStack)
    return FALSE;
  
  xP = pxW->pvProp;
  
  if(xP->cItemCount == PICTURE_STACK_MAX_SIZE)
    return FALSE;
  
  //Находим последний элемент в списке
  xNext = xP->xItems;

  while(xNext){
    xI = xNext;
    xNext = xI->pxNext;
  }

  //Allocate memory for new Item
  xNext = pvMemoryMalloc(sizeof(xPictureStackItem), MEMORY_EXT);

  if(!xNext)
    return NULL;

  xNext->xPic = xPic;
  xNext->pxNext = NULL;

  //TODO: Check Picture Dimensions here
  xI->pxNext = xNext;
  xP->cItemCount++;

  return TRUE;
}

xPicture xPictureStackGetItem(xWidget *pxW, char cItemNumber){
  xPictureStackProps *xP;
  xPictureStackItem *xI;
  xPictureStackItem *xNext;
  
  if(!pxW)
    return NULL;
  
  if(pxW->eType != WidgetPictureStack)
    return NULL;
  
  xP = pxW->pvProp;
  
  if(cItemNumber >= xP->cItemCount)
    return NULL;
  
  xNext = xP->xItems;

  do{
    xI = xNext;
    xNext = xI->pxNext;
  }while(cItemNumber-- && xNext);

  return xI->xPic;
}


#endif	//__PICTURE_STACK_C
