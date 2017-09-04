/**
* @file   MenuButton.c
* @author Lemeshev K (konstantin.lemeshev@gmail.com)
* @date   21.02.2014
* @brief  Реализация виджета кнопки для меню и диалогов
*
*/

#include "MenuButton.h"
#include <stdlib.h>


/** @weakgroup prop-widget-menu-button
*  @{
*/

typedef struct xMenuButton_t {
	xButton *xButton;     ///< виджет - кнопка
	xWidget *xText;       ///< виджет - лейбочка (подпись под кнопкой)
}xMenuButtonProps;

/**
* @brief Обработчик события от внутренней кнопки
*
* Перехватывает событие нажатия и генерирует нажатие на внешнем контейнере
* Таким образом, получается, что событие как-будто бы исходит от контейнера @ref xMenuButton.
*
* @param pxW - не используется
*
*/
static bool prvButtonClick(xWidget *pxW) {
	if (bWidgetIs(pxW, WidgetButton)) {
		if (bWidgetIs(pxW->pxParent, WidgetMenuButton) && pxW->pxParent->pxOnClick) {
			pxW->pxParent->pxOnClick(pxW->pxParent);
		}
	}
	return true;
}

xMenuButton * pxMenuButtonCreate(uint16_t usX, uint16_t usY, xPicture pusPic, char* strLabel, bool(*pvClickHanlder) (xWidget *), xWidget *pxWidParent) {
	xMenuButton *pxW;
	xMenuButtonProps *xP;

	// memory for MenuButton

	pxW = (xMenuButton*)malloc(sizeof(xWidget));
	//инициализация виджета

	uint16_t usW, usH;

	usW = pxDrawHDL()->usGetPictureW(pusPic); // ширина
	usH = pxDrawHDL()->usGetPictureH(pusPic); // +pxDrawHDL()->usGetPictureH(pusPicText);

	if (bWidgetInit(pxW, usX, usY, usW, usH, pxWidParent, true)) {

		xP = (xMenuButtonProps*)malloc(sizeof(xMenuButtonProps));
		if (!xP)
			return NULL;

		pxW->pvProp = xP;
		pxW->eType = WidgetMenuButton;
		vWidgetSetOnClickHandler(pxW, pvClickHanlder);
		//Внешний контейнер этой кнопки не должен быть кликабельным.
		//Обработка щелчка происходит через прокси-метод prvButtonClick
		pxW->bClickable = false;

		// ----
		xP->xButton = pxButtonCreate(0, 0, pusPic, pxW);
		bButtonSetOnClickHandler(xP->xButton, prvButtonClick);

		xP->xText = pxLabelCreate(0, usWidgetGetH(xP->xButton), usW, usFontGetH(FONT_ASCII_8_X) + 3, "", FONT_ASCII_8_X, 10, pxW);
		vWidgetSetBgColor(xP->xText, MENU_BUTTON_LABEL_BG_COLOR, false);
		vLabelSetVerticalAlign(xP->xText, LABEL_ALIGN_MIDDLE);
		vLabelSetTextAlign(xP->xText, LABEL_ALIGN_CENTER);
		vLabelSetTextColor(xP->xText, MENU_BUTTON_LABEL_TEXT_COLOR);
		pcLabelSetText(xP->xText, strLabel);

		// ----
		return pxW;
	}

	else {
		free(pxW);
		return NULL;

	}
}

void pxMenuButtonSetMainPic(xWidget * pxW, xPicture pusPic) {
	xMenuButtonProps *xP;

	if (!(xP = (xMenuButtonProps*)pxWidgetGetProps(pxW, WidgetMenuButton)))
		return;

	bWidgetSetBgPicture(xP->xButton, pusPic);

	return;
}

void pxMenuButtonSetLabelText(xWidget * pxW, char const* strL) {
	xMenuButtonProps *xP;

	if (!(xP = (xMenuButtonProps*)pxWidgetGetProps(pxW, WidgetMenuButton)))
		return;

	pcLabelSetText(xP->xText, strL);

	return;
}

/**
*  @}
*/
