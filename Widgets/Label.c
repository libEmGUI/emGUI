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
#include "Widgets/Label.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#ifndef min
#define min(a,b) ((a < b) ? a :b)
#endif

typedef struct xLabelProps_t {
	eLabelTextAlign     eTextAlign;
	eLabelVerticalAlign eVerticalAlign;
	char *pcStr;
	uint16_t usMaxLength;
	xFont xFnt;
	uint16_t usColor;
	bool bIsMultiLine;
	bool bHaveCursor;
	char *pcPrvPage;
	char *pcNxtPage;
	char *pcCrntPage;
	void(*onEditHandler)(void);
} xLabelProps;

static char* prvCountLine(char *pcLine, uint16_t uXFrom, uint16_t uXTo, uint16_t *puXLinePosition,
	xFont pubFont, eLabelTextAlign eHorAlign) {
	uint16_t uXBefor, uMaxLineLen, uXSeparator;
	char *pcSeparator, *pcCharCount;

	if (!pcLine || uXTo <= uXFrom)
		return NULL;

	uMaxLineLen = (uint16_t)strlen(pcLine);
	pcSeparator = NULL;
	pcCharCount = pcLine;
	uXBefor = uXFrom;
	uXSeparator = uXBefor;

	while ((uXBefor + ucFontGetCharW(*pcCharCount, pubFont)) <= uXTo && uMaxLineLen) {
		if (((*pcCharCount == ' ' || *pcCharCount == '\t') && pcCharCount != pcLine) // и разделитель будет не первый символ
			|| *pcCharCount == '\n') {
			pcSeparator = pcCharCount;
			uXSeparator = uXBefor; // временное хранение, на случай если
		}                        // придётся отматывать назад до pcSeparator
		if (*pcCharCount == '\n')
			break;
		if (*pcCharCount == '\t')
			*pcCharCount = ' ';
		uXBefor += ucFontGetCharW(*pcCharCount, pubFont);
		++pcCharCount;
		--uMaxLineLen;
	}

	if (pcSeparator && uMaxLineLen) // если перенос по разделителю, то необходимо и uXBefor отсчитать назад
		uXBefor = uXSeparator;

	if (puXLinePosition)
		switch (eHorAlign) {
		case LABEL_ALIGN_CENTER:
			*puXLinePosition = uXFrom + (uXTo - uXBefor) / 2;
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

static void prvPrintLine(char *pcLine, uint16_t uCharCount, uint16_t uXFrom, uint16_t uY,
	xFont pubFont, uint16_t usColor, uint16_t usBackground) {
	char *pcCharacter;
	pcCharacter = pcLine;

	while (*pcCharacter && uCharCount) {
		if (*pcCharacter != '\n')
			pxDrawHDL()->vPutChar(uXFrom, uY, *pcCharacter, pubFont, usColor, usBackground, false);
		uXFrom += ucFontGetCharW(*pcCharacter, pubFont);
		++pcCharacter;
		--uCharCount;
	}
}

static char *prvCountPage(char *pcPage, uint16_t uXFrom, uint16_t uXTo, uint16_t uYFrom, uint16_t uYTo, uint16_t *puYPosition, uint16_t *puLineCount,
	xFont pubFont, eLabelTextAlign eHorAlign, eLabelVerticalAlign eVerAlign) {
	char *pcNxtLine;
	uint16_t uYBefor;
	uYBefor = uYFrom;
	pcNxtLine = pcPage;
	*puLineCount = 0;
	while ((uYBefor + usFontGetH(pubFont)) <= uYTo && pcNxtLine) {
		pcNxtLine = prvCountLine(pcNxtLine, uXFrom, uXTo, NULL, pubFont, eHorAlign);
		uYBefor += usFontGetH(pubFont);
		if (puLineCount)
			(*puLineCount)++;
	}

	if (puYPosition)
		switch (eVerAlign) {
		case LABEL_ALIGN_MIDDLE:
			*puYPosition = uYFrom + (uYTo - uYBefor) / 2;
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

static void prvPrintPage(char *pcPage, uint16_t uXFrom, uint16_t uXTo, uint16_t uYFrom, uint16_t uLineCount, eLabelTextAlign eHorAlign,
	xFont pubFont, uint16_t usColor, uint16_t usBackground) {
	char *pcNxtLine, *pcCrntLine;
	uint16_t uLineLen, uXPutLine;
	pcCrntLine = pcPage;
	while (pcCrntLine && uLineCount) {
		pcNxtLine = prvCountLine(pcCrntLine, uXFrom, uXTo, &uXPutLine, pubFont, eHorAlign);
		uLineLen = pcNxtLine - pcCrntLine;
		prvPrintLine(pcCrntLine, uLineLen, uXPutLine, uYFrom, pubFont, usColor, usBackground);
		uYFrom += usFontGetH(pubFont);
		pcCrntLine = pcNxtLine;
		--uLineCount;
	}
}

static bool prvDraw(xWidget *pxW) {
	xLabelProps *xP;
	uint16_t uY, uLineCount;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return false;

	if (!xP->pcStr)
		return false;

	//if (strlen(xP->pcStr) > xP->usMaxLength)
	  //return false;

	if (pxW->bValid)
		return false;

	bWidgetDraw(pxW);

	xP->pcNxtPage = prvCountPage(xP->pcCrntPage, pxW->usX0, pxW->usX1 + 1, pxW->usY0, pxW->usY1 + 1, &uY, &uLineCount,
		xP->xFnt, xP->eTextAlign, xP->eVerticalAlign);
	prvPrintPage(xP->pcCrntPage, pxW->usX0, pxW->usX1 + 1, uY, uLineCount, xP->eTextAlign,
		xP->xFnt, xP->usColor, pxW->usBgColor);

	return true;
}

static void prvSetPrvPgPntr(xLabel *pxW) {
	xLabelProps *xP;
	char *pcPageCount;
	if ((xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel))) {
		xP->pcPrvPage = NULL;
		pcPageCount = xP->pcStr;
		while (pcPageCount != xP->pcCrntPage) {
			xP->pcPrvPage = pcPageCount;
			pcPageCount = prvCountPage(pcPageCount, pxW->usX0, pxW->usX1 + 1, pxW->usY0, pxW->usY1 + 1, NULL, NULL,
				xP->xFnt, xP->eTextAlign, xP->eVerticalAlign);
		}
	}
}

bool bLabelDrawNextPage(xLabel *pxL) {
	xLabelProps *xP;
	xP = (xLabelProps *)pxL->pvProp;
	if (xP->pcNxtPage) {
		xP->pcCrntPage = xP->pcNxtPage;
		vWidgetInvalidate(pxL);
		return true;
	}
	return false;
}

bool bLabelDrawPrevPage(xLabel *pxW) {
	xLabelProps *xP;
	xP = (xLabelProps *)pxW->pvProp;
	prvSetPrvPgPntr(pxW);
	if (xP->pcPrvPage) {
		xP->pcCrntPage = xP->pcPrvPage;
		vWidgetInvalidate(pxW);
		return true;
	}
	return false;
}

//если usMaxLength = 0, то текст в метку устанавливается только сменой указателя на строку,
//т.е. он не копируется во внутреннее хранилище и под него не выделяется память. Идеально для
//реализации меток с текстом ReadOnly
xLabel * pxLabelCreate(uint16_t usX, uint16_t usY, uint16_t usW, uint16_t usH, char const * cStr, xFont xFnt, uint16_t usMaxLength, xWidget *pxWidParent) {
	xLabel *pxW;
	xLabelProps *xP;

	pxW = malloc(sizeof(xWidget));

	if (!xFnt || !cStr)
		return NULL;

	if (usH < usFontGetH(xFnt))
		usH = usFontGetH(xFnt);

	if (bWidgetInit(pxW, usX, usY, usW, usH, pxWidParent, true)) {

		vWidgetSetBgColor(pxW, WIDGET_COLOR_WHITE, false);

		xP = malloc(sizeof(xLabelProps));
		if (!xP)
			return NULL;

		usMaxLength = (usMaxLength > LABEL_MAX_LENGTH) ? LABEL_MAX_LENGTH : usMaxLength;

		//Выделяем память для внутр. хранилища
		if (usMaxLength) {
			//+ 1 //for '\0' char in the end
			xP->pcStr = malloc(usMaxLength + 1);
		}
		else
			xP->pcStr = (char *)cStr; ///WARNING!

		  //Память не выделилась, строка Read Only
		if (!xP->pcStr) {
			xP->pcStr = (char *)cStr; ///WARNING!
			usMaxLength = 0;
		}

		xP->usMaxLength = usMaxLength;

		xP->eTextAlign = LABEL_ALIGN_LEFT;
		xP->eVerticalAlign = LABEL_ALIGN_TOP;

		xP->usColor = WIDGET_COLOR_BLACK;
		xP->xFnt = xFnt;

		xP->bHaveCursor = false;

		if (usMaxLength) {
			memcpy(xP->pcStr, cStr, min(strlen(cStr), usMaxLength) + 1);
			//Terminating string
			xP->pcStr[usMaxLength] = '\0';
		}

		xP->onEditHandler = NULL;

		xP->bIsMultiLine = false;
		xP->pcCrntPage = xP->pcStr;
		xP->pcNxtPage = NULL;
		xP->pcPrvPage = NULL;

		pxW->pvProp = xP;
		pxW->eType = WidgetLabel;
		pxW->pxDrawHandler = prvDraw;

		return pxW;
	}
	else {
		free(pxW);
		return NULL;
	}
}

char * pcLabelSetText(xWidget *pxW, const char * pcStr) {
	xLabelProps *xP;
	char *pcLine;
	uint16_t  usMaxLength;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return NULL;

	//TODO: возможно ли так???
	/*if(!xP->pcStr)
	  return NULL;*/

	pcLine = xP->pcStr;
	usMaxLength = xP->usMaxLength;


	//Если возможно копирование во внутр. или внешн. память
	if (usMaxLength) {
		if (!strcmp(pcStr, pcLine))
			return NULL;

		if (pcStr != NULL) {
			memcpy(pcLine, pcStr, min(strlen(pcStr), usMaxLength) + 1);
			pcLine[usMaxLength] = '\0';
		}

	}
	else {
		/*/Не нужно обновлять
		if(pcLine == pcStr)
		  return NULL;*/
		  //если NULL, то просто инвалидируем
		if (pcStr != NULL) {
			xP->pcStr = (char*)pcStr;
			xP->pcCrntPage = xP->pcStr;
		}
	}

	if (xP->bIsMultiLine) {
		xP->pcCrntPage = xP->pcStr;
		xP->pcNxtPage = xP->pcPrvPage = NULL;
	}

	vWidgetInvalidate(pxW);
	return NULL;
}

void pcLabelSetTextAdaptWidth(xLabel *pxL, char * pcStr) {
	pcLabelSetText(pxL, pcStr);
	pxL->usX1 = pxL->usX0 + 8 * (uint16_t)strlen(pcStr);
	vWidgetInvalidate(pxL);
}

void vLabelSetTextColor(xWidget *pxW, uint16_t usColor) {
	xLabelProps *xP;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return;

	xP->usColor = usColor;
	vWidgetInvalidate(pxW);
}

void vLabelSetTextAlign(xWidget *pxW, eLabelTextAlign eAlign) {
	xLabelProps *xP;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return;

	xP->eTextAlign = eAlign;
	vWidgetInvalidate(pxW);
}

void vLabelSetVerticalAlign(xWidget *pxW, eLabelVerticalAlign eAlign) {
	xLabelProps *xP;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return;

	xP->eVerticalAlign = eAlign;
	vWidgetInvalidate(pxW);
}

void vLabelSetTextExt(xWidget *pxW, char * pStr, int usMaxLength) {
	xLabelProps *xP;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return;

	//Для сброса режима
	if (!usMaxLength) {
		pcLabelSetText(pxW, pStr);
		xP->usMaxLength = 0;
	}

	//Внешнюю строку можно устанавливать только если не было создано внутр. хранилище!
	if (xP->usMaxLength)
		return;

	if (xP->pcStr == pStr)
		return;

	xP->pcStr = pStr;
	xP->usMaxLength = usMaxLength;

	xP->pcCrntPage = xP->pcStr;
	xP->pcPrvPage = xP->pcNxtPage = NULL;

	vWidgetInvalidate(pxW);
}

char *      pcLabelGetText(xWidget *pxW) {
	xLabelProps *xP;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return NULL;

	return xP->pcStr;
}

bool bLabelSetMultiline(xWidget *pxW, bool bMultiLine) {
	xLabelProps *xP;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		return false;

	xP->bIsMultiLine = bMultiLine;

	return true;
}


int         iLabelGetMaxLength(xLabel *pxL) {
	xLabelProps *xP;

	if (!(xP = (xLabelProps *)pxWidgetGetProps(pxL, WidgetLabel)))
		return 0;

	return xP->usMaxLength;
}

bool bLabelAppendChar(xWidget *pxW, char cChar, bool bSetInvalidate) {
	xLabelProps *xP;
	if ((xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel))) {
		uint16_t usLen = (uint16_t)strlen(xP->pcStr);
		if (usLen + 1 <= xP->usMaxLength) {
			xP->pcStr[usLen] = cChar;
			xP->pcStr[usLen + 1] = '\0';
			if (bSetInvalidate)
				vWidgetInvalidate(pxW);
			return true;
		}
	}
	return false;
}

bool bLabelBackSpace(xWidget *pxW, bool bSetInvalidate) {
	xLabelProps *xP;
	if ((xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel))) {
		uint16_t usLen = (uint16_t)strlen(xP->pcStr);
		if (usLen) {
			xP->pcStr[usLen - 1] = '\0';
			if (bSetInvalidate)
				vWidgetInvalidate(pxW);
			return true;
		}
	}
	return false;
}

void vLabelSetOnClickHandler(xWidget *pxW, bool(*callback)(xWidget*)) {
	if (pxWidgetGetProps(pxW, WidgetLabel))
		vWidgetSetOnClickHandler(pxW, callback);
}

void vLabelSetOnEditHandler(xWidget *pxW, void(*callback)(void)) {
	xLabelProps *xP;
	if ((xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		xP->onEditHandler = callback;
}

void vLabelSetHaveCursor(xWidget *pxW, bool bLabelHaveCursor) {
	xLabelProps *xP;
	if ((xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel)))
		xP->bHaveCursor = bLabelHaveCursor;
}

void vLabelClear(xWidget *pxW, bool bSetInvalidate) {
	xLabelProps *xP;
	if ((xP = (xLabelProps *)pxWidgetGetProps(pxW, WidgetLabel))) {
		xP->pcStr[0] = '\0';
		if (bSetInvalidate)
			vWidgetInvalidate(pxW);
	}
}

int iLabelPrintf(xWidget *pxW, char const *pcFmt, ...) {
	xLabelProps *xP;
	int iRet = 0;

	if (!(xP = (xLabelProps*)pxWidgetGetProps(pxW, WidgetLabel)))
		return 0;

	if (!xP->usMaxLength)
		return 0;

	va_list args;
	va_start(args, pcFmt);

	iRet = vsnprintf(xP->pcStr, xP->usMaxLength, pcFmt, args);

	vWidgetInvalidate(pxW);
	return iRet;
}