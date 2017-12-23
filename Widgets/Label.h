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

/*
 *
 *      Проставляет \n по тексту в зависимости от длины строки !!! меняет строку на входе!!!
 *   void vAdaptTextToMultiLine(char *pcText, uint16_t usLabelWidth, xFont xLabelFont);
 *          pcText - указатель нас троку для вывода
 *          usLabelWidth - ширина Label
 *          xLabelFont - шрифт
 *
 *      Делает из Label MultiLine Label и выводит в неё текст !!! строку на входе не меняет!!!
 *   void vSetMultilineText(xWidget *pxW, char *pcText);
 *          pxW - Label-назначение
 *          pcText -
 */

#ifndef EMGUI_LABEL_H
#define EMGUI_LABEL_H

#include <stdint.h>
#include <stdbool.h>
#include "emGUI/Widgets/Widget.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef xWidget xLabel;

	typedef enum {
		LABEL_ALIGN_LEFT,
		LABEL_ALIGN_CENTER,
		LABEL_ALIGN_RIGHT,
	} eLabelTextAlign;

	typedef enum {
		LABEL_ALIGN_TOP,
		LABEL_ALIGN_MIDDLE,
		LABEL_ALIGN_BOTTOM,
	} eLabelVerticalAlign;


	xLabel *    pxLabelCreate(uint16_t usX, uint16_t usY, uint16_t usW, uint16_t usH, char const * cStr, xFont xFnt, uint16_t usMaxLength, xWidget *pxWidParent);
	char *      pcLabelSetText(xWidget *pxW, const char * pcStr);
	void        pcLabelSetTextAdaptWidth(xLabel *pxL, const char * pcStr); // замена текста и адаптированние ширины Label под длину нового текста, работает только под 16 размер
	void        vLabelSetTextColor(xWidget *pxW, uint16_t usColor);
	void        vLabelSetTextAlign(xWidget *pxW, eLabelTextAlign eAlign);
	void        vLabelSetVerticalAlign(xWidget *pxW, eLabelVerticalAlign eAlign);
	void        vLabelSetTextExt(xWidget *pxW, char * pStr, int usMaxLength);
	char *      pcLabelGetText(xWidget *pxW);
	bool        bLabelSetMultiline(xWidget *pxW, bool bMultiLine);
	bool        bLabelDrawNextPage(xLabel *pxL);
	bool        bLabelDrawPrevPage(xLabel *pxL);
	int         iLabelGetMaxLength(xLabel *pxL);
	bool        bLabelAppendChar(xWidget *pxW, char cChar, bool bSetInvalidate);
	bool        bLabelBackSpace(xWidget *pxW, bool bSetInvalidate);
	void        vLabelSetOnClickHandler(xWidget *pxW, bool(*callback)(xWidget*));
	void        vLabelSetOnEditHandler(xWidget *pxW, void(*callback)(void));
	void        vLabelSetHaveCursor(xWidget *pxW, bool bLabelHaveCursor);
	void        vLabelClear(xWidget *pxW, bool bSetInvalidate);
	int         iLabelPrintf(xWidget *pxW, char const *pcFmt, ...);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif	//__LABEL_H
