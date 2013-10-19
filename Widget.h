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

#ifndef __WIDGET_H
#define __WIDGET_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include "include.h"
#include "TouchScreen.h"
#include "GuiConfig.h"
  
  typedef enum {
    Widget,
    #include "eWidgetType.def"
  } eWidgetType;

  typedef struct xWidget_struct xWidget;
  
  //The size of each widget is 60 bytes.
  struct xWidget_struct {
    eWidgetType eType;
    
    //Absolute Position and dimentions
    u16 usX0;
    u16 usY0;
    u16 usX1;
    u16 usY1;
    
    //Visibility and behavior
    unsigned bValid           : 1; //0      
    unsigned bClickable       : 1;
    unsigned bVisible         : 1; //2
    unsigned bEnabled         : 1;
    unsigned bPressed         : 1; //4
    unsigned bPushEventCaught : 1;
    unsigned bTransparent     : 1; //6
    unsigned bInvalidate      : 1; //0
    unsigned bInvalidateParent: 1;
    
    //background
    u16 usBgColor;
    unsigned short const* pusBgPicture;
    
    //Child object properties   
    void* pvProp;
    
    xWidget *pxParent;
    xWidget *pxChild;
    xWidget *pxNextSibling;
    
    bool (*pxDrawHandler)   (xWidget *);
    bool (*pxCheckTSRoutine)(xWidget *, xTouchEvent *);
    bool (*pxOnClick)       (xWidget *);
    bool (*pxOnShow)        (xWidget *);
    bool (*pxOnHide)        (xWidget *);
    
  };
  
  xWidget * pxWidgetAlloc();
  
  xWidget * pxWidgetCreate(u16 usX0, u16 usY0, u16 usX1, u16 usY1, xWidget *pxWidParent, bool bUseWH);
  
  xWidget inline *pxWidgetGetChild(xWidget *pxW){
    return pxW->pxChild;
  }

  xWidget inline *pxWidgetGetNext(xWidget *pxW){
    return pxW->pxNextSibling;
  }

  bool bWidgetInit(xWidget *pxW, u16 usX, u16 usY, u16 usW, u16 usH, xWidget *pxWidParent, bool bUseWH);
  void vWidgetInvalidate(xWidget *pxW);
  void vWidgetDraw(xWidget *pxW);
  bool bWidgetAdd(xWidget *pxW, xWidget *pxWidChild);
  bool bWidgetCheckTouchScreenEvent(xWidget *pxW, xTouchEvent *pxTouchScreenEv);
  
  bool bWidgetMoveTo(xWidget *pxW, u16 usX0, u16 usY0);
  //Setters
  
  void vWidgetSetOnClickHandler(xWidget *pxW, bool (*pxCallback)(xWidget *));
  void vWidgetSetOnHideHandler(xWidget *pxW, bool (*pxCallback)(xWidget *));
  void vWidgetSetOnShowHandler(xWidget *pxW, bool (*pxCallback)(xWidget *));
  void vWidgetSetDrawHandler(xWidget *pxW, bool (*pxCallback)(xWidget *));
  void vWidgesSetClickable(xWidget *pxW, bool bClickable);
  void vWidgetSetBgColor(xWidget *pxW, u16 usBgColor, bool bTransparent);
  void vWidgetSetTransparency(xWidget *pxW, bool bTransparent);
  bool bWidgetSetBgPicture(xWidget *pxW, unsigned short const* pusBgPicture);
  void vWidgetSetVisible(xWidget *pxW, bool bVisible);
  void vWidgetSetClickable(xWidget *pxW, bool bClickable);
  void vWidgetSetEnabled(xWidget *pxW, bool bEnabled);
  bool bWidgetSetCoords(xWidget *pxW, u16 usX0, u16 usY0, u16 usX1, u16 usY1, bool bUseWH);
  
  //Commands
  bool bWidgetDraw(xWidget *pxW);

  void inline vWidgetShow(xWidget *pxW){
    vWidgetSetVisible(pxW, TRUE);
  }

  void inline vWidgetHide(xWidget *pxW){
    vWidgetSetVisible(pxW, FALSE);
  }
  
  //Getters
  u16 inline usWidgetGetW(xWidget *pxW){
    return pxW->usX1 - pxW->usX0 + 1;
  }

  u16 inline usWidgetGetH(xWidget *pxW){
    return pxW->usY1 - pxW->usY0 + 1;
  }

  u16 inline usWidgetGetX0(xWidget *pxW, bool bAbsolute){
    if(!pxW->pxParent)
      return pxW->usX0;
    
    if(bAbsolute)
      return pxW->usX0;
    else 
      return pxW->usX0 - pxW->pxParent->usX0;
  }

  u16 inline usWidgetGetY0(xWidget *pxW, bool bAbsolute){
    if(!pxW->pxParent)
      return pxW->usY0;
    
    if(bAbsolute)
      return pxW->usY0;
    else 
      return pxW->usY0 - pxW->pxParent->usY0;
  }

  u16 inline usWidgetGetX1(xWidget *pxW, bool bAbsolute){
    if(!pxW->pxParent)
      return pxW->usX1;
    
    if(bAbsolute)
      return pxW->usX1;
    else 
      return pxW->usX1 - pxW->pxParent->usX0;
  }

  u16 inline usWidgetGetY1(xWidget *pxW, bool bAbsolute){
    if(!pxW->pxParent)
      return pxW->usY1;
    
    if(bAbsolute)
      return pxW->usY1;
    else 
      return pxW->usY1 - pxW->pxParent->usY0;
  }
  
  bool inline bWidgetResize(xWidget *pxW, u16 usW, u16 usH){
    return bWidgetSetCoords(pxW, usWidgetGetX0(pxW, FALSE), usWidgetGetY0(pxW, FALSE), usW, usH, TRUE);
  }
  
  bool inline bWidgetIs(xWidget * pxW, eWidgetType eType){
    return (pxW->eType == eType && pxW)?TRUE:FALSE;
  }

  void inline * pxWidgetGetProps(xWidget * pxW, eWidgetType eType){
    if(!bWidgetIs(pxW, eType))
      return NULL;

    return pxW->pvProp;
  }

#ifdef __cplusplus
}
#endif

#endif	//__WIDGET_H
