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

   Created on: 06.03.2013
*/


#include "emGUI/Widgets/Label.h"
#include "emGUI/Widgets/Button.h"
#include "emGUI/Widgets/Window.h"
#include "emGUI/Widgets/Button.h"
#include "emGUI/Widgets/WindowManager.h"
//#include "Widgets/ProgressBar.h"

#include "emGUI/Draw/Draw.h"

#include "emGUI/Widgets/ModalDialog.h"
#include <stdlib.h>

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#define MODAL_DIALOG_MAX_BUTTONS    3
#define MODAL_DIALOG_MAX_COUNT      10
#define MODAL_DIALOG_MAX_MSG_LENGTH 255
#define PB_BORDER                   20

	static xWindow *xThisWnd = NULL;

	static xLabel         *xMessage = NULL;
	//static xProgressBar   *xPBar;
	static xButton    *xButtons[MODAL_DIALOG_MAX_BUTTONS] = { 0 }; // y/n/c maximum visible is 4 buttons

	//auto-increment counter for auto dialogs (id = 0)
	static uint16_t usDlgID = EMGUI_MODAL_AUTO + 1;

	typedef struct xModalDialog_t xModalDialog;

	struct xModalDialog_t {

		ModalDialogHandler pxDefaultHandler;

		//bool bActive
		char sDialogButtons[MODAL_DIALOG_MAX_BUTTONS + 1];
		uint16_t  usDlgID;
		char * sHdr;
		char * sMsg;
		signed char cProgress;
		bool bCanClose;

		void * pvCtx;

		xModalDialog * pxPrev;
	};

	xModalDialog *xMDActive = NULL;

	static void prvDlgShowActive(bool);

	static xModalDialog *prvGetNextDlg(xModalDialog *xDlg) {
		if (!xDlg)
			return NULL;
		return xDlg->pxPrev;
	}

	static void prvResetDlgWnd() {
		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++) {
			vWidgetHide(xButtons[c]);
		}

		vWindowSetHeader(xThisWnd, "");
		pcLabelSetText(xMessage, "");
		//vWidgetHide(xPBar);
	}

	static bool prvOnOpenHandler(xWidget *pxW) {
		(void)pxW;
		prvDlgShowActive(false);
		return true;
	}

	static bool prvOnOpenRequestHandler(xWidget *pxW) {
		(void)pxW;
		if (xMDActive)
			return true;
		else
			return false;
	}

	static bool prvOnCloseHandler(xWidget *pxW) {
		
		xThisWnd = NULL;
		xMessage = NULL;
		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++) {
			xButtons[c] = NULL;
		}
		return true;
	}

	static bool prvOnCloseRequestHandler(xWidget *pxW) {
		(void)pxW;
		xModalDialog * xMDCurrent = xMDActive;
		if (xMDCurrent)
			vModalDialogClose(xMDActive->usDlgID, 0, true); //xMDActive can change during this call, so store it in xMDCurrent

		if (xMDCurrent)
			return false;
		else
			return true;
	}

	static bool prvButtonHandler(xWidget *pxW) {
		
		if (!xMDActive)
			return false;

		// dialog can open another dialog in its handler.
		// xMDActive is changed in that case. store previous value
		int usDlgId = xMDActive->usDlgID;

		char cButton = 0;

		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++) {
			if (xButtons[c] == pxW) {
				cButton = xMDActive->sDialogButtons[c];
				break;
			}
		}

		if (xMDActive->pxDefaultHandler) {
			if (xMDActive->pxDefaultHandler(cButton, xMDActive->pvCtx))
				vModalDialogClose(usDlgId, 0, false);
		}else
			vModalDialogClose(usDlgId, 0, false);

		return true;
	}

	static xWidget * pxModalDialogWindowCreate() {

		// X0, Y0 - widget placement coords
		uint16_t usX, usY;

		if (xThisWnd)
			return xThisWnd;

		xThisWnd = pxWindowCreate(EMGUI_MODAL_WINDOW_ID);
		vWindowSetDisposable(xThisWnd, true);
		vWidgetSetBgColor(xThisWnd, EMGUI_COLOR_PLOT_BACKGROUND, false);
		vWindowSetOnOpenHandler(xThisWnd, prvOnOpenHandler);
		vWindowSetOnOpenRequestHandler(xThisWnd, prvOnOpenRequestHandler);
		vWindowSetOnCloseHandler(xThisWnd, prvOnCloseHandler);
		vWindowSetOnCloseRequestHandler(xThisWnd, prvOnCloseRequestHandler);

		usY = (usWidgetGetH(xThisWnd) * 6) / 10;

		xFont xFnt = pxDrawHDL()->xGetDefaultFont();

		xMessage = pxLabelCreate(0, 0, usWidgetGetW(xThisWnd), usY, "", xFnt, MODAL_DIALOG_MAX_MSG_LENGTH, xThisWnd);
		bLabelSetMultiline(xMessage, true);
		vLabelSetTextAlign(xMessage, LABEL_ALIGN_CENTER);
		vLabelSetVerticalAlign(xMessage, LABEL_ALIGN_MIDDLE);

		usY = usWidgetGetY1(xMessage, false);

		//xPBar = pxProgressBarCreate(PB_BORDER, usY, usWidgetGetW(xThisWnd) - PB_BORDER * 2, 30, xThisWnd);
		//vProgressBarSetProcExec(xPBar, 55);

		//TODO: get rid of picture dimensions check on create and position buttons on show!
		//usY = (usWindowManagerGetWindowH() / 2 + pxDrawHDL()->usGetPictureH(pxDrawHDL()->xGetDialogPictureSet(' ').xPicMain) / 3);
		usX = 0;

		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++) {
			xButtons[c] = pxButtonCreateFromImageWithText(usX, usY, NULL, "", xThisWnd);
			vButtonSetOnClickHandler(xButtons[c], prvButtonHandler);
			usX += EMGUI_MODAL_DLG_BTN_SPACING;
			vWidgetHide(xButtons[c]);
		}
		return xThisWnd;
	}

	static void prvShowPB(xModalDialog * xDlg) {
		if (xDlg->cProgress >= 0) {
			//vWidgetShow(xPBar);
			//vProgressBarSetProcExec(xPBar, xDlg->cProgress);
		}
		else {
			//vWidgetHide(xPBar);
		}
	}

	static void prvDlgShowActive(bool bBringWindowBack) {
		xModalDialog * xDlg = xMDActive;

		if (!xDlg) {
			//return;
			vWindowManagerCloseWindow(EMGUI_MODAL_WINDOW_ID);
			return;
			//TODO: set active dialog count to 0?
		}
		else if(bBringWindowBack && !bWindowManagerIsWindowActive(EMGUI_MODAL_WINDOW_ID))
			vWindowManagerOpenWindow(EMGUI_MODAL_WINDOW_ID);

		uint16_t cBtnCnt = (uint16_t)strlen(xDlg->sDialogButtons);
		xModalDialogPictureSet xPicSet;

		char * sBtns = xDlg->sDialogButtons;

		xButton * xBtn;

		uint16_t betweenBtnsX,
			usX, usY;

		prvResetDlgWnd();

		betweenBtnsX = (usWidgetGetW(xThisWnd) - cBtnCnt * usWidgetGetW(xButtons[0])) / (cBtnCnt + 1);
		usY = usWidgetGetY0(xButtons[0], false);
		usX = betweenBtnsX;

		vWindowSetHeader(xThisWnd, xDlg->sHdr);
		pcLabelSetText(xMessage, xDlg->sMsg);

		prvShowPB(xDlg);

		for (int c = 0; c < cBtnCnt; c++) {
			xBtn = xButtons[c];
			xPicSet = pxDrawHDL()->xGetDialogPictureSet(sBtns[c]);

			bWidgetMoveTo(xBtn, usX, usY);
			vWidgetShow(xBtn);

			vButtonSetPicture(xBtn, xPicSet.xPicMain);
			vButtonSetText(xBtn, xPicSet.strLabel);

			usX += betweenBtnsX + usWidgetGetW(xBtn);
		}

	}

	static void prvIncDlgId() {
		//TODO: thread protection???
		usDlgID++;
		if (usDlgID <= EMGUI_MODAL_AUTO)
			usDlgID = EMGUI_MODAL_AUTO + 1;
	}

	static xModalDialog *prvDlgIsActive(int iDlgId) {
		if (iDlgId == EMGUI_MD_CUR)
			return xMDActive;

		if (xMDActive && xMDActive->usDlgID == iDlgId)
			return xMDActive;

		return NULL;
	}

	static xModalDialog *prvDlgIsOpened(int iDlgId, xModalDialog ** pxNext) {
		xModalDialog * xDlg = xMDActive;

		*pxNext = NULL;

		if (iDlgId == EMGUI_MD_CUR)
			return xMDActive;

		while (xDlg) {
			if (xDlg->usDlgID == iDlgId)
				return xDlg;
			*pxNext = xDlg;
			xDlg = prvGetNextDlg(xDlg);
		}

		return NULL;
	}

	static xModalDialog *prvDelDlgFromStack(xModalDialog *pxN, xModalDialog *pxNext) {

		xModalDialog * pxPrev; // prev dialog in the stack
		pxPrev = pxN->pxPrev;
		pxNext->pxPrev = pxPrev;

		return pxN;
	}

	static void prvDlgRefresh(xModalDialog * xDlg, char const* sBtns, char const* sHdr, char const* sMsg) {
		if (!xDlg)
			return;

		size_t strLen = 0;

		if(xDlg->sHdr)
			free(xDlg->sHdr); // reallocating space for new strings
		if(xDlg->sMsg)
			free(xDlg->sMsg);

		strLen = MIN(strlen(sBtns), MODAL_DIALOG_MAX_BUTTONS) + 1;
		memcpy(xDlg->sDialogButtons, sBtns, strLen);
		xDlg->sDialogButtons[strLen - 1] = '\0';

		strLen = MIN(strlen(sHdr), EMGUI_WINDOW_HEADER_LENGTH) + 1;
		xDlg->sHdr = malloc(strLen);
		memcpy(xDlg->sHdr, sHdr, strLen);
		xDlg->sHdr[strLen - 1] = '\0';

		strLen = MIN(strlen(sMsg), MODAL_DIALOG_MAX_MSG_LENGTH) + 1;
		xDlg->sMsg = malloc(strLen);
		memcpy(xDlg->sMsg, sMsg, strLen);
		xDlg->sMsg[strLen - 1] = '\0';

		xDlg->cProgress = -1;
		xDlg->bCanClose = true;

		xDlg->pxDefaultHandler = NULL;
	}

	int iModalDialogOpen(int iDlgId, char const * sBtns, char const * sHdr, char const* sMsg) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		pxModalDialogWindowCreate();

		/*/ check max dialog count
		if(cDialogCount >= MODAL_DIALOG_MAX_COUNT){
		  vWindowManagerOpenWindow(EMGUI_MODAL_WINDOW_ID);
		  return -1;
		}*/

		// if dialog with that ID is already opened, just refresh its data
		if ((xDlg = prvDlgIsActive(iDlgId))) {
			prvDlgRefresh(xDlg, sBtns, sHdr, sMsg);
			prvDlgShowActive(false);
			vWindowManagerOpenWindow(EMGUI_MODAL_WINDOW_ID);
			return -1;
		}

		// dialog is in the background, pop it to the front
		if ((xDlg = prvDlgIsOpened(iDlgId, &xDlgNext))) {
			prvDlgRefresh(xDlg, sBtns, sHdr, sMsg);
			prvDelDlgFromStack(xDlg, xDlgNext);
		}
		else {
			// this is a new dialog, create it
			xDlg = malloc(sizeof(xModalDialog));
			memset(xDlg, 0, sizeof(xModalDialog));
			//cDialogCount ++;
			
			prvDlgRefresh(xDlg, sBtns, sHdr, sMsg);
			// set dialog ID to make it possible set handlers, etc...
			if (iDlgId == EMGUI_MD_NEW) {
				xDlg->usDlgID = usDlgID;
				prvIncDlgId();
			}
			else
				xDlg->usDlgID = iDlgId;
		}

		// make dialog active
		xDlg->pxPrev = xMDActive;
		xMDActive = xDlg;

		prvDlgShowActive(false);

		vWindowManagerOpenWindow(EMGUI_MODAL_WINDOW_ID);
		vWidgetInvalidate(xThisWnd);

		return xDlg->usDlgID;
	}

	void vModalDialogSetHandler(int iDlgID, void *pvCtx, ModalDialogHandler pxHandler) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		if (!xThisWnd)
			return;

		if (!(xDlg = prvDlgIsOpened(iDlgID, &xDlgNext)))
			return;

		xDlg->pxDefaultHandler = pxHandler;
		xDlg->pvCtx = pvCtx;
	}

	void vModalDialogSetCloseable(int iDlgID, bool bCanClose) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		if (!xThisWnd)
			return;

		if (!(xDlg = prvDlgIsOpened(iDlgID, &xDlgNext)))
			return;

		xDlg->bCanClose = bCanClose;
	}


	void vModalDialogSetProgress(int iDlgID, int iProgress) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		if (!xThisWnd)
			return;

		if (!(xDlg = prvDlgIsOpened(iDlgID, &xDlgNext)))
			return;

		if (iProgress < 0)
			iProgress = -1;

		if (iProgress > 100)
			iProgress = 100;

		if (xDlg->cProgress == iProgress)
			return;

		xDlg->cProgress = iProgress;

		if (prvDlgIsActive(iDlgID)) {
			prvShowPB(xDlg);
		}
	}

	void vModalDialogClose(int iDlgID, char cBtn, bool bFireHandler) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		if (!xThisWnd)
			return;

		xDlg = prvDlgIsOpened(iDlgID, &xDlgNext);

		// this dialog wasn't in the list
		if (!xDlg)
			return;

		// we cannot close this dialog
		if (!xDlg->bCanClose)
			return;

		// this dialog is active! pop previous dialog
		if (prvDlgIsActive(iDlgID)) {
			xMDActive = xMDActive->pxPrev;
		}
		else
			prvDelDlgFromStack(xDlg, xDlgNext);

		uint16_t cBtnCnt = (uint16_t)strlen(xDlg->sDialogButtons);
		
		char fireArg = 0;
		for (int i = 0; i < cBtnCnt; i++) {
			if (xDlg->sDialogButtons[i] == cBtn) {
				fireArg = cBtn;
				break;
			}
		}

		// fire default event
		if (bFireHandler) {
			if (xDlg->pxDefaultHandler)
				xDlg->pxDefaultHandler(fireArg, xDlg->pvCtx);
		}
		free(xDlg->sHdr);
		free(xDlg->sMsg);
		free(xDlg);
		prvDlgShowActive(true);
	}