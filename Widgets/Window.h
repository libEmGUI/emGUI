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

	Created on: 19.02.2013
*/

#ifndef WINDOW_H_
#define WINDOW_H_


#include "Widgets/Widget.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef xWidget xWindow;

	typedef enum {
		WINDOW_MENU = 0,
		WINDOW_ECG,
		WINDOW_CLOCK,
		WINDOW_GSM_CALL,
		WINDOW_TRANSFER,
		WINDOW_MODAL,
		WINDOW_ABOUT,
		WINDOW_TS_CALIB,
		WINDOW_ARCHIVE,
		WINDOW_OPINION,
		WINDOW_CONSOLE,
		WINDOW_TEXTEDITOR,
		WINDOW_NOTES,
	} eWindow;

	typedef struct xWindowProps_t {
		eWindow eId;
		xWindow *xBackWindow;
		char*   strHeader;
		bool    bFullScreen;
		bool(*pxOnCloseRequest)       (xWidget *);
		bool(*pxOnClose)              (xWidget *);
		bool(*pxOnOpenRequest)        (xWidget *);
		bool(*pxOnOpen)               (xWidget *);
	} xWindowProps;

	xWindow * pxWindowCreate(eWindow eWnd);
	void vWindowSetOnOpenHandler(xWidget * pxW, bool(*pxCallback)(xWidget *));
	void vWindowSetOnOpenRequestHandler(xWidget * pxW, bool(*pxCallback)(xWidget *));
	void vWindowSetOnCloseHandler(xWidget * pxW, bool(*pxCallback)(xWidget *));
	void vWindowSetOnCloseRequestHandler(xWidget * pxW, bool(*pxCallback)(xWidget *));
	void vWindowSetHeader(xWidget * pxW, char const* strH);
	xWindow * pxWindowGetBack(xWidget *pxW);
	void vWindowSetFullScreen(xWidget *pxW, bool bFS);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* WINDOW_H_ */
