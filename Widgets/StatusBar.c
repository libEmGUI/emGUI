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

#include "emGUI/Widgets/Interface.h"
#include "emGUI/Widgets/Button.h"
#include "emGUI/Widgets/Label.h"

#include "emGUI/Widgets/StatusBar.h"
#include "emGUI/Draw/Draw.h"
 /** @weakgroup prop-widget-statusbar
 *  @{
 */



typedef struct xStatusBarProps_struct {
	uint16_t usColor;          ///< цвет статус-бара
} xStatusBarProps;

static xWidget             *xStatusBarInstance; ///< дескриптор виджета
static xButton             *xCloseButton;       ///< дескриптор крестика
static xLabel              *xWndHeader;         ///< дескриптор заголовка окна

 /**
  * @brief обработчик щелчка на кнопке крестика
  *
  * @returns true - событие обработано
  */
static bool prvCloseClickHandler(xWidget* pxW) {
	vInterfaceCloseActiveWindow();
	return true;
}


bool bStatusBarCreate(uint16_t usColor) {

	xPicture xCross = pxDrawHDL()->xGetPicture("cross"); //TODO: Check for null?

	xFont xFnt = pxDrawHDL()->xGetDefaultFont();

	xStatusBarInstance = pxWidgetCreate(0, 0, usInterfaceGetW(), EMGUI_STATUS_BAR_HEIGHT, pxInterfaceGet(), true);
	xStatusBarInstance->eType = WidgetStatusBar;
	vWidgetSetBgColor(xStatusBarInstance, usColor, false);

	uint16_t usX, usY, usW;

	usY = (EMGUI_STATUS_BAR_HEIGHT - pxDrawHDL()->usGetPictureH(xCross)) / 2;
	usX = EMGUI_LCD_WIDTH - pxDrawHDL()->usGetPictureW(xCross) - usY;

	xCloseButton = pxButtonCreate(usX, usY, xCross, xStatusBarInstance);
	vWidgetSetOnClickHandler(xCloseButton, prvCloseClickHandler);

	usY = (usStatusBarGetH() - pxDrawHDL()->usFontGetH(xFnt)) / 2;
	usW = pxDrawHDL()->usFontGetStrW("Default", xFnt) + 10;
	usX = usStatusBarGetW() / 2 - usW / 2;

	xWndHeader = pxLabelCreate(usX, usY, usW, 0, "Default", xFnt, 100, xStatusBarInstance);
	vWidgetSetBgColor(xWndHeader, usColor, false);
	vLabelSetTextColor(xWndHeader, EMGUI_COLOR_MENU_HEADER_TEXT);
	vLabelSetTextAlign(xWndHeader, LABEL_ALIGN_CENTER);


	//vGuiSendEvent(GuiEventRefreshPb, 0);

	return true;
}

void  vStatusBarSetWindowHeader(const char * strH) {
	pcLabelSetText(xWndHeader, strH);
}

xWidget *pxStatusBarGet() {
	return xStatusBarInstance;
}



/**
 *  @}
 */
