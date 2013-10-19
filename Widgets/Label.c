/*
	emGUI Library V1.0.0 - Copyright (C) 2013 
	Lemeshev K <konstantin.lemeshev@gmail.com>, 
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
#include "Label.h"
#include "Framebuffer.h"
#include <string.h>
#include "Memory.h"
#include <stdio.h>
#ifndef min
#define min(a,b) ((a < b) ? a :b)
#endif

#define LABEL_MAX_LENGTH 10000

static char* prvCountLine(char *pcLine, u16 uXFrom, u16 uXTo, u16 *puXLinePosition,
                   xFont pubFont, eLabelTextAlign eHorAlign){
  u16 uXBefor, uMaxLineLen, uXSeparator;
  char *pcSeparator, *pcCharCount;

  if (!pcLine || uXTo <= uXFrom)
    return NULL;

  uMaxLineLen = strlen(pcLine);
  pcSeparator = NULL;
  pcCharCount = pcLine;
  uXBefor = uXFrom;

  while((uXBefor + ucFontGetCharW(*pcCharCount, pubFont)) <= uXTo && uMaxLineLen){
    if ( ( (*pcCharCount == ' '||  *pcCharCount == '\t') && pcCharCount != pcLine) // и разделитель будет не первый символ
         || *pcCharCount == '\n'){
      pcSeparator = pcCharCount;
      uXSeparator = uXBefor; // временное хранение, на случай если
    }                        // придётся отматывать назад до pcSeparator
    if (*pcCharCount == '\n')
      break;
    if (*pcCharCount == '\t')
      *pcCharCount = ' ';
    uXBefor+= ucFontGetCharW(*pcCharCount, pubFont);
    ++pcCharCount;
    --uMaxLineLen;
  }

  if (pcSeparator && uMaxLineLen) // если перенос по разделителю, то необходимо и uXBefor отсчитать назад
    uXBefor = uXSeparator;

  if (puXLinePosition)
    switch (eHorAlign){
      case LABEL_ALIGN_CENTER:
        *puXLinePosition = uXFrom + (uXTo - uXBefor)/2;
        break;
      case LABEL_ALIGN_RIGHT:
        *puXLinePosition = uXFrom + (uXTo - uXBefor);
        break;
      default:
        *puXLinePosition = uXFrom;
        break;
    }

  if (!uMaxLineLen || !(*pcCharCount))
    return NULL;

  return !pcSeparator ? pcCharCount : pcSeparator == '\0' ? pcSeparator : pcSeparator + 1;
}

static void prvPrintLine(char *pcLine, u16 uCharCount, u16 uXFrom, u16 uY,
                  xFont pubFont, u16 usColor, u16 usBackground){
  char *pcCharacter;
  pcCharacter = pcLine;

  while (*pcCharacter && uCharCount){
    if (*pcCharacter != '\n')
      vFramebufferPutChar(uXFrom, uY, *pcCharacter, pubFont, usColor, usBackground, FALSE);
    uXFrom+= ucFontGetCharW(*pcCharacter, pubFont);
    ++pcCharacter;
    --uCharCount;
  }
}

static char *prvCountPage(char *pcPage, u16 uXFrom, u16 uXTo, u16 uYFrom, u16 uYTo, u16 *puYPosition, u16 *puLineCount,
                  xFont pubFont, eLabelTextAlign eHorAlign, eLabelVerticalAlign eVerAlign){
  char *pcNxtLine;
  u16 uYBefor;
  uYBefor = uYFrom;
  pcNxtLine = pcPage;
  *puLineCount = 0;
  while ((uYBefor + usFontGetH(pubFont)) <= uYTo && pcNxtLine){
    pcNxtLine = prvCountLine(pcNxtLine, uXFrom, uXTo, NULL, pubFont, eHorAlign);
    uYBefor+= usFontGetH(pubFont);
    if (puLineCount)
      (*puLineCount)++;
  }

  if (puYPosition)
    switch(eVerAlign){
      case LABEL_ALIGN_MIDDLE:
        *puYPosition = uYFrom + (uYTo - uYBefor)/2;
        break;
      case LABEL_ALIGN_BOTTOM:
        *puYPosition = uYFrom + (uYTo - uYBefor);
        break;
      default:
        *puYPosition = uYFrom;
        break;
    }
  return pcNxtLine;
}

static void prvPrintPage(char *pcPage, u16 uXFrom, u16 uXTo, u16 uYFrom, u16 uLineCount, eLabelTextAlign eHorAlign,
                  xFont pubFont, u16 usColor, u16 usBackground){
  char *pcNxtLine, *pcCrntLine;
  u16 uLineLen, uXPutLine;
  pcCrntLine = pcPage;
  while (pcCrntLine && uLineCount){
    pcNxtLine = prvCountLine(pcCrntLine, uXFrom, uXTo, &uXPutLine, pubFont, eHorAlign);
    uLineLen = pcNxtLine - pcCrntLine;
    prvPrintLine(pcCrntLine, uLineLen, uXPutLine, uYFrom, pubFont, usColor, usBackground);
    uYFrom+= usFontGetH(pubFont);
    pcCrntLine = pcNxtLine;
    --uLineCount;
  }
}

bool static prvDraw(xWidget *pxW){
  xLabelProps *xP;
  u16 uY, uLineCount;

  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return FALSE;
  
  if (!xP->pcStr)
    return FALSE;

  //if (strlen(xP->pcStr) > xP->iMaxLength)
    //return FALSE;

  if(pxW->bValid)
    return FALSE;

  bWidgetDraw(pxW);
  
  xP->pcNxtPage = prvCountPage(xP->pcCrntPage, pxW->usX0, pxW->usX1 + 1, pxW->usY0, pxW->usY1 + 1, &uY, &uLineCount,
                      xP->xFnt, xP->eTextAlign, xP->eVerticalAlign);
  prvPrintPage(xP->pcCrntPage, pxW->usX0, pxW->usX1 + 1, uY, uLineCount, xP->eTextAlign,
        xP->xFnt, xP->usColor, pxW->usBgColor);

  return TRUE;
}

static void prvSetPrvPgPntr(xLabel *pxW){
  xLabelProps *xP;
  char *pcPageCount;
  if((xP = pxWidgetGetProps(pxW, WidgetLabel))){
    xP->pcPrvPage = NULL;
    pcPageCount = xP->pcStr;
    while (pcPageCount != xP->pcCrntPage){
      xP->pcPrvPage = pcPageCount;
      pcPageCount = prvCountPage(pcPageCount, pxW->usX0, pxW->usX1 + 1, pxW->usY0, pxW->usY1 + 1, NULL, NULL,
        xP->xFnt, xP->eTextAlign, xP->eVerticalAlign);
    }
  }
}

bool bLabelDrawNextPage(xLabel *pxL){
  xLabelProps *xP;
  xP = pxL->pvProp;
  if(xP->pcNxtPage){
    xP->pcCrntPage = xP->pcNxtPage;
    vWidgetInvalidate(pxL);
    return TRUE;
  }
  return FALSE;
}

bool bLabelDrawPrevPage(xLabel *pxW){
  xLabelProps *xP;
  xP = pxW->pvProp;
  prvSetPrvPgPntr(pxW);
  if(xP->pcPrvPage){
    xP->pcCrntPage = xP->pcPrvPage;
    vWidgetInvalidate(pxW);
    return TRUE;
  }
  return FALSE;
}

//если iMaxLength = 0, то текст в метку устанавливается только сменой указателя на строку,
//т.е. он не копируется во внутреннее хранилище и под него не выделяется память. Идеально для
//реализации меток с текстом ReadOnly
xLabel * pxLabelCreate(u16 usX, u16 usY, u16 usW, u16 usH, char * cStr, xFont xFnt, int iMaxLength, xWidget *pxWidParent){
  xLabel *pxW;
  xLabelProps *xP;
    
  pxW = pvMemoryMalloc(sizeof(xWidget), MEMORY_EXT);
  
  if(!xFnt || !cStr)
    return NULL;
  
  if(usH < usFontGetH(xFnt))
    usH = usFontGetH(xFnt);
  
  if(bWidgetInit(pxW, usX, usY, usW, usH, pxWidParent, TRUE)){
    
    vWidgetSetBgColor(pxW, 65535, FALSE);
    
    xP        = pvMemoryMalloc(sizeof(xLabelProps), MEMORY_EXT);
    if(!xP)
      return NULL;

    iMaxLength = (iMaxLength > LABEL_MAX_LENGTH)?LABEL_MAX_LENGTH:iMaxLength;

    //Выделяем память для внутр. хранилища
    if(iMaxLength){
      //+ 1 //for '\0' char in the end
      xP->pcStr = pvMemoryMalloc(sizeof(*(xP->pcStr))*iMaxLength + 1, MEMORY_EXT);
    }
    else
      xP->pcStr = cStr;
    
    //Память не выделилась, строка Read Only
    if(!xP->pcStr){
      xP->pcStr = cStr;
      iMaxLength = 0;
    }

    xP->iMaxLength = iMaxLength;

    xP->eTextAlign = LABEL_ALIGN_LEFT;
    xP->eVerticalAlign = LABEL_ALIGN_TOP;

    xP->usColor = 0;
    xP->xFnt = xFnt;
    
    xP->bHaveCursor = FALSE;

    if(iMaxLength){
      memcpy ( xP->pcStr, cStr, min(strlen(cStr), iMaxLength) + 1 );
      //Terminating string
      xP->pcStr[iMaxLength] = '\0';
    }
    
    xP->onEditHandler = NULL;

    xP->bIsMultiLine = FALSE;
    xP->pcCrntPage = xP->pcStr;
    xP->pcNxtPage = NULL;
    xP->pcPrvPage = NULL;

    pxW->pvProp = xP;    
    pxW->eType = WidgetLabel;
    pxW->pxDrawHandler = prvDraw;
    
    return pxW;
  }
  else{
    vMemoryFree(pxW);
    return NULL;
  }
}

char * pcLabelSetText(xWidget *pxW, const char * pcStr){
  xLabelProps *xP;
  char *pcLine;
  int  iMaxLength;
  
  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return NULL;
  
  //TODO: возможно ли так???
  /*if(!xP->pcStr)
    return NULL;*/

  pcLine = xP->pcStr;
  iMaxLength = xP->iMaxLength;

  
  //Если возможно копирование во внутр. или внешн. память
  if(iMaxLength){
    if(!strcmp(pcStr, pcLine))
      return NULL;

    if (pcStr != NULL){
      memcpy ( pcLine, pcStr, min(strlen(pcStr), iMaxLength) + 1 );
      pcLine[iMaxLength] = '\0';
    }

  }else{
    /*/Не нужно обновлять
    if(pcLine == pcStr)
      return NULL;*/
    //если NULL, то просто инвалидируем
    if(pcStr != NULL){
      xP->pcStr = (char*)pcStr;
      xP->pcCrntPage = xP->pcStr;
    }
  }

  if (xP->bIsMultiLine){
    xP->pcCrntPage = xP->pcStr;
    xP->pcNxtPage = xP->pcPrvPage = NULL;
  }

  vWidgetInvalidate(pxW);
  return NULL;
}

void pcLabelSetTextAdaptWidth(xLabel *pxL, char * pcStr){
  pcLabelSetText(pxL, pcStr);
  pxL->usX1 = pxL->usX0 + 8*strlen(pcStr);
  vWidgetInvalidate(pxL);
}

void vLabelSetTextColor(xWidget *pxW, u16 usColor){
  xLabelProps *xP;
  
  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return;

  xP->usColor = usColor;
  vWidgetInvalidate(pxW);
}

void vLabelSetTextAlign(xWidget *pxW, eLabelTextAlign eAlign){
  xLabelProps *xP;
  
  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return;

  xP->eTextAlign = eAlign;
  vWidgetInvalidate(pxW);
}

void vLabelSetVerticalAlign(xWidget *pxW, eLabelVerticalAlign eAlign){
  xLabelProps *xP;
  
  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return;

  xP->eVerticalAlign = eAlign;
  vWidgetInvalidate(pxW);
}

void vLabelSetTextExt(xWidget *pxW, char * pStr, int iMaxLength){
  xLabelProps *xP;

  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return;

  //Для сброса режима
  if(!iMaxLength){
    pcLabelSetText(pxW, pStr);
    xP->iMaxLength = 0;
  }
  
  //Внешнюю строку можно устанавливать только если не было создано внутр. хранилище!
  if(xP->iMaxLength)
    return;

  if(xP->pcStr == pStr)
    return;

  xP->pcStr = pStr;
  xP->iMaxLength = iMaxLength;
  
  xP->pcCrntPage = xP->pcStr;
  xP->pcPrvPage = xP->pcNxtPage = NULL;

  vWidgetInvalidate(pxW);
}

char *      pcLabelGetText(xWidget *pxW){
  xLabelProps *xP;

  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return NULL;

  return xP->pcStr;
}

bool bLabelSetMultiline(xWidget *pxW, bool bMultiLine){
  xLabelProps *xP;

  if(!(xP = pxWidgetGetProps(pxW, WidgetLabel)))
    return FALSE;

  xP->bIsMultiLine = bMultiLine;

  return TRUE;
}


int         iLabelGetMaxLength(xLabel *pxL){
  xLabelProps *xP;

  if(!(xP = pxWidgetGetProps(pxL, WidgetLabel)))
    return 0;

  return xP->iMaxLength;
}

bool bLabelAppendChar(xWidget *pxW, char cChar, bool bSetInvalidate){
  xLabelProps *xP;
  if((xP = pxWidgetGetProps(pxW, WidgetLabel))){
    u16 usLen = strlen(xP->pcStr);
    if (usLen + 1 <= xP->iMaxLength){
      xP->pcStr[usLen] = cChar;
      xP->pcStr[usLen + 1] = '\0';
      if (bSetInvalidate)
        vWidgetInvalidate(pxW);
      return TRUE;
    }
  }
  return FALSE;
}

bool bLabelBackSpace(xWidget *pxW, bool bSetInvalidate){
  xLabelProps *xP;
  if((xP = pxWidgetGetProps(pxW, WidgetLabel))){
    u16 usLen = strlen(xP->pcStr);
    if (usLen){
      xP->pcStr[usLen - 1] = '\0';
      if (bSetInvalidate)
        vWidgetInvalidate(pxW);
      return TRUE;
    }
  }
  return FALSE;
}

void vLabelSetOnClickHandler(xWidget *pxW, bool (*callback)(xWidget*)){
  if(pxWidgetGetProps(pxW, WidgetLabel))
    vWidgetSetOnClickHandler(pxW, callback);
}

void vLabelSetOnEditHandler(xWidget *pxW, void (*callback)(void)){
  xLabelProps *xP;
  if((xP = pxWidgetGetProps(pxW, WidgetLabel)))
    xP->onEditHandler = callback;
}

void vLabelSetHaveCursor(xWidget *pxW, bool bLabelHaveCursor){
  xLabelProps *xP;
  if((xP = pxWidgetGetProps(pxW, WidgetLabel)))
    xP->bHaveCursor = bLabelHaveCursor;
}

void vLabelClear(xWidget *pxW, bool bSetInvalidate){
  xLabelProps *xP;
  if((xP = pxWidgetGetProps(pxW, WidgetLabel))){
    xP->pcStr[0] = '\0';
    if (bSetInvalidate)
      vWidgetInvalidate(pxW);
  }
}
