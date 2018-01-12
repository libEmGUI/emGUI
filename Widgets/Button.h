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

#ifndef EMGUI_BUTTON_H
#define EMGUI_BUTTON_H


#include "emGUI/Widgets/Widget.h"
#include <stdint.h> 

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef xWidget xButton;

	xButton * pxButtonCreateFromText(uint16_t usX, uint16_t usY, uint16_t usW, uint16_t usH, const char *text, xWidget *pxWidParent);
	xButton * pxButtonCreateFromImage(uint16_t usX, uint16_t usY, xPicture pusPic, xWidget *pxWidParent);
	xButton * pxButtonCreateFromImageWithText(uint16_t usX, uint16_t usY, xPicture pusPic, const char *text, xWidget *pxWidParent);

	void vButtonSetOnClickHandler(xWidget *pxW, WidgetEvent pxCallback);

	void vButtonSetText(xWidget * pxW, char const* strL);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	//__BUTTON_H
