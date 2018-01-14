/**
 * @file   StatusBar.c
 * @author Roman Savrulin (romeo.deepmind@gmail.com)
 * @date   10.11.2012
 * @brief  Реализация виджета статус-бара
 *
 * Это - виджет синглтон
 *
 */

#include <stdint.h>
#include <malloc.h>

#include "emGUI/Widgets/Interface.h"
#include "emGUI/Widgets/Button.h"
#include "emGUI/Widgets/Label.h"

#include "emGUI/Widgets/StatusBar.h"
#include "emGUI/Draw/Draw.h"
 /** @weakgroup prop-widget-statusbar
 *  @{
 */


typedef struct xStatusBarProps_struct {
	xButton             *xCloseButton;
	xLabel              *xWndHeader;
} xStatusBarProps;


 /**
  * @brief close button handler
  *
  * @returns true - event is handled
  */
static bool prvCloseClickHandler(xWidget* pxW) {
	vInterfaceCloseActiveWindow();
	return true;
}

static void prvDispose(xWidget* pxW) {
	xStatusBarProps *xP;
	if (!(xP = (xStatusBarProps *)pxWidgetGetProps(pxW, WidgetStatusBar)))
		return;

	vWidgetDispose(xP->xCloseButton);
	vWidgetDispose(xP->xWndHeader);
}


xStatusBar* xStatusBarCreate(uint16_t usColor) {

	xStatusBar * pxW;
	xStatusBarProps * xP;
	uint16_t usX, usY, usW;

	xFont xFnt = pxDrawHDL()->xGetDefaultFont();

	pxW = (xStatusBar *) pxWidgetCreate(0, 0, usInterfaceGetW(), EMGUI_STATUS_BAR_HEIGHT, pxInterfaceGet(), true);

	if(!pxW){
		vWidgetDispose(pxW);
		return NULL;
	}

	xP = malloc(sizeof(xStatusBarProps));

	if (!xP) {
		free(pxW);
		return NULL;
	}

	memset(xP, 0, sizeof(xStatusBarProps));

	pxW->pvProp = xP;

	pxW->eType = WidgetStatusBar;
	vWidgetSetBgColor(pxW, usColor, false);

	usY = 2;
	usW = usWidgetGetH(pxW) - usY * 2;
	usX = usWidgetGetW(pxW) - usWidgetGetH(pxW);

	xP->xCloseButton = pxButtonCreateFromText(usX, usY, usW, usW, "X", pxW);
	vWidgetSetTransparency(xP->xCloseButton, true);
	vWidgetSetOnClickHandler(xP->xCloseButton, prvCloseClickHandler);

	usY = (usWidgetGetH(pxW) - pxDrawHDL()->usFontGetH(xFnt)) / 2;
	usW = pxDrawHDL()->usFontGetStrW("Default", xFnt) + 10;
	usX = usWidgetGetW(pxW) / 2 - usW / 2;

	xP->xWndHeader = pxLabelCreate(usX, usY, usW, 0, "Default", xFnt, EMGUI_WINDOW_HEADER_LENGTH, pxW);
	vWidgetSetBgColor(xP->xWndHeader, usColor, false);
	vLabelSetTextColor(xP->xWndHeader, EMGUI_COLOR_MENU_HEADER_TEXT);
	vLabelSetTextAlign(xP->xWndHeader, LABEL_ALIGN_CENTER);

	return pxW;
}

void  vStatusBarSetWindowHeader(xStatusBar* pxW, const char * strH) {
	xStatusBarProps *xP;
	if (!(xP = (xStatusBarProps *)pxWidgetGetProps(pxW, WidgetStatusBar)))
		return;

	pcLabelSetText(xP->xWndHeader, strH);
}

/**
 *  @}
 */
