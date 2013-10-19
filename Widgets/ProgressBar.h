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

#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "Widget.h"
#include "Label.h"

typedef xWidget xProgressBar;

typedef struct xProgressBarProps_t{
  u16 usBarColor;
  u16 usExProc;   // проценты выполненно
  xLabel *pxBarLabel;
} xProgressBarProps;

xProgressBar* pxProgressBarCreate(u16 usX, u16 usY, u16 usW, u16 usH, xWidget *pxWidParent);
void vProgressBarSetProcExec(xWidget *pxW, u16 usExecProc);

#ifdef __cplusplus
}
#endif

#endif /* PROGRESSBAR_H_ */
