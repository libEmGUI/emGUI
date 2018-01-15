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
	static xButton    *xButtons[MODAL_DIALOG_MAX_BUTTONS] = { 0 }; // y(ok)/n/c Максимум в диалоге видно 4 кнопки.

	//автонумерация для автоматических диалогов
	uint16_t usDlgID = EMGUI_MODAL_AUTO + 1;

	typedef struct xModalDialog_t xModalDialog;

	struct xModalDialog_t {
		void(*pxClickHandlers[MODAL_DIALOG_MAX_BUTTONS])   ();

		void(*pxDefaultHandler)   ();

		//bool bActive
		char sDialogConfig[MODAL_DIALOG_MAX_BUTTONS + 1];
		uint16_t  usDlgID;
		char * sHdr;
		char * sMsg;
		signed char cProgress;
		bool bCanClose;
		xModalDialog * pxPrev;
	};

	xModalDialog *xMDActive = NULL;

	static void prvDlgShowActive();

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
		prvDlgShowActive();
		return true;
	}

	static bool prvOnOpenRequestHandler(xWidget *pxW) {
		if (xMDActive)
			return true;
		else
			return false;
	}

	static bool prvOnCloseHandler(xWidget *pxW) {
		return true;
	}

	static bool prvOnCloseRequestHandler(xWidget *pxW) {
		if (xMDActive)
			vModalDialogClose(xMDActive->usDlgID, true);

		if (xMDActive)
			return false;
		else
			return true;
	}

	static bool prvButtonHandler(xWidget *pxW) {
		//диалог в обработчике может открыть еще один диалог.
		//при этом ID актовного изменяется. Для сохранения используем
		//эту переменную.
		int usDlgId = xMDActive->usDlgID;
		if (!xMDActive)
			return false;
		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++) {
			if (xButtons[c] == pxW && xMDActive->pxClickHandlers[c]) {
				xMDActive->pxClickHandlers[c]();
				break;
			}
		}
		vModalDialogClose(usDlgId, false);
		return true;
	}

	static xWidget * pxModalDialogWindowCreate() {

		// X0, Y0 - координаты расположения виджетов
		uint16_t usX, usY;

		if (xThisWnd)
			return xThisWnd;

		xThisWnd = pxWindowCreate(EMGUI_MODAL_WINDOW_ID);
		vWidgetSetBgColor(xThisWnd, EMGUI_COLOR_PLOT_BACKGROUND, false);
		vWindowSetOnOpenHandler(xThisWnd, prvOnOpenHandler);
		vWindowSetOnOpenRequestHandler(xThisWnd, prvOnOpenRequestHandler);
		vWindowSetOnCloseHandler(xThisWnd, prvOnCloseHandler);
		vWindowSetOnCloseRequestHandler(xThisWnd, prvOnCloseRequestHandler);

		usY = (usWindowManagerGetWindowH() * 4) / 10;

		xFont xFnt = pxDrawHDL()->xGetDefaultFont();

		xMessage = pxLabelCreate(0, 0, usWidgetGetW(xThisWnd), usY, "", xFnt, MODAL_DIALOG_MAX_MSG_LENGTH, xThisWnd);
		bLabelSetMultiline(xMessage, true);
		vLabelSetTextAlign(xMessage, LABEL_ALIGN_CENTER);
		vLabelSetVerticalAlign(xMessage, LABEL_ALIGN_MIDDLE);

		usY = usWidgetGetY1(xMessage, false);

		//xPBar = pxProgressBarCreate(PB_BORDER, usY, usWidgetGetW(xThisWnd) - PB_BORDER * 2, 30, xThisWnd);
		//vProgressBarSetProcExec(xPBar, 55);

		//TODO: get rid of picture dimensions check on create and position buttons on show!
		usY = (usWindowManagerGetWindowH() / 2 + pxDrawHDL()->usGetPictureH(pxDrawHDL()->xGetDialogPictureSet(' ').xPicMain) / 3);
		usX = 0;

		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++) {
			xButtons[c] = pxButtonCreateFromImageWithText(usX, usY, pxDrawHDL()->xGetDialogPictureSet(' ').xPicMain, "", xThisWnd);
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

	static void prvDlgShowActive() {
		xModalDialog * xDlg = xMDActive;

		if (!xDlg) {
			//return;
			vWindowManagerCloseWindow(EMGUI_MODAL_WINDOW_ID);
			return;
			//TODO: выставить кол-во активных диалогов в 0
		}

		uint16_t cBtnCnt = (uint16_t)strlen(xDlg->sDialogConfig);
		xModalDialogPictureSet xPicSet;

		char * sBtns = xDlg->sDialogConfig;

		xButton * xBtn;

		uint16_t betweenBtnsX,
			usX, usY;

		prvResetDlgWnd();

		betweenBtnsX = (usWindowManagerGetW() - cBtnCnt * usWidgetGetW(xButtons[0])) / (cBtnCnt + 1);
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

			bWidgetSetBgPicture(xBtn, xPicSet.xPicMain);
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
		if (!xMDActive)
			return NULL;

		if (xMDActive->usDlgID == iDlgId)
			return xMDActive;

		return NULL;
	}

	static xModalDialog *prvDlgIsOpened(int iDlgId, xModalDialog ** pxNext) {
		xModalDialog * xDlg = xMDActive;

		*pxNext = NULL;

		while (xDlg) {
			if (xDlg->usDlgID == iDlgId)
				return xDlg;
			*pxNext = xDlg;
			xDlg = prvGetNextDlg(xDlg);
		}

		return NULL;
	}

	static xModalDialog *prvDelDlgFromStack(xModalDialog *pxN, xModalDialog *pxNext) {

		xModalDialog * pxPrev; //пред. диалог в стеке
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
		memcpy(xDlg->sDialogConfig, sBtns, strLen);
		xDlg->sDialogConfig[strLen - 1] = '\0';

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

		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++)
			xDlg->pxClickHandlers[c] = NULL;

		xDlg->pxDefaultHandler = NULL;
	}

	int iModalDialogOpen(int iDlgId, char const * sBtns, char const * sHdr, char const* sMsg) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		pxModalDialogWindowCreate();

		/*/Проверка ограничения макс. количества открытых диалогов
		if(cDialogCount >= MODAL_DIALOG_MAX_COUNT){
		  vWindowManagerOpenWindow(EMGUI_MODAL_WINDOW_ID);
		  return -1;
		}*/

		//Если такой диалог уже активен - Сбросить его обработчики и конфигурацию.
		if ((xDlg = prvDlgIsActive(iDlgId))) {
			prvDlgRefresh(xDlg, sBtns, sHdr, sMsg);
			prvDlgShowActive();
			vWindowManagerOpenWindow(EMGUI_MODAL_WINDOW_ID);
			return -1;
		}

		//Диалог есть где-то в стеке, его надо поднять
		if ((xDlg = prvDlgIsOpened(iDlgId, &xDlgNext))) {
			prvDlgRefresh(xDlg, sBtns, sHdr, sMsg);
			prvDelDlgFromStack(xDlg, xDlgNext);
		}
		else {
			size_t strLen = 0;

			//Диалога в стеке нет, создаем новую структуру
			xDlg = malloc(sizeof(xModalDialog));
			memset(xDlg, 0, sizeof(xModalDialog));
			//cDialogCount ++;
			
			prvDlgRefresh(xDlg, sBtns, sHdr, sMsg);
			//Выставляем идентификатор диалога, по которому
			//будет возможность дальнейшей работы с этим диалогом.
			if (iDlgId != EMGUI_MODAL_AUTO)
				xDlg->usDlgID = iDlgId;
			else {
				xDlg->usDlgID = usDlgID;
				prvIncDlgId();
			}
		}

		//делаем диалог активным
		xDlg->pxPrev = xMDActive;
		xMDActive = xDlg;

		prvDlgShowActive();

		vWindowManagerOpenWindow(EMGUI_MODAL_WINDOW_ID);
		vWidgetInvalidate(xThisWnd);

		return xDlg->usDlgID;
	}

	void vModalDialogSetHandler(int iDlgID, char cHandler, void(*pxHandler)()) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		pxModalDialogWindowCreate();

		if (!(xDlg = prvDlgIsOpened(iDlgID, &xDlgNext)))
			return;

		for (int c = 0; c < MODAL_DIALOG_MAX_BUTTONS; c++) {
			if (xDlg->sDialogConfig[c] == cHandler) {
				xDlg->pxClickHandlers[c] = pxHandler;
				return;
			}
		}
		xDlg->pxDefaultHandler = pxHandler;
	}

	void vModalDialogSetCloseable(int iDlgID, bool bCanClose) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		pxModalDialogWindowCreate();

		if (!(xDlg = prvDlgIsOpened(iDlgID, &xDlgNext)))
			return;

		xDlg->bCanClose = bCanClose;
	}


	void vModalDialogSetProgress(int iDlgID, int iProgress) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		pxModalDialogWindowCreate();

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

	void vModalDialogClose(int iDlgID, bool bFireDefault) {
		xModalDialog * xDlg;
		xModalDialog * xDlgNext;

		pxModalDialogWindowCreate();

		xDlg = prvDlgIsOpened(iDlgID, &xDlgNext);

		//такой диалог не был в стеке
		if (!xDlg)
			return;

		//если диалог нельзя закрывать
		if (!xDlg->bCanClose)
			return;

		//если диалог активный, то ставим активным предыдущий.
		if (prvDlgIsActive(iDlgID)) {
			xMDActive = xMDActive->pxPrev;
		}
		else
			prvDelDlgFromStack(xDlg, xDlgNext);

		//генерируем событие по умолчанию, если надо и оно есть.
		if (bFireDefault) {
			if (xDlg->pxDefaultHandler)
				xDlg->pxDefaultHandler(NULL);
		}
		free(xDlg->sHdr);
		free(xDlg->sMsg);
		free(xDlg);
		prvDlgShowActive();
	}
