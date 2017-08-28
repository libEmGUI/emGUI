/**
* @file   MenuButton.c
* @author Lemeshev K (konstantin.lemeshev@gmail.com)
* @date   21.02.2014
* @brief  Реализация виджета кнопки для меню и диалогов
*
*/

#include "Memory.h"
#include "MenuButton.h"
#include "PictureStorage.h"
#include "Label.h"
#include "Fonts.h"

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

xMenuButton * pxMenuButtonCreate(u16 usX, u16 usY, xPicture xPicFG, char* strLabel, bool(*pvClickHanlder) (xWidget *), xWidget *pxWidParent) {
	xMenuButton *pxW;
	xMenuButtonProps *xP;

	xPicture xPicText;

	// memory for MenuButton

	pxW = (xMenuButton*)pvMemoryMalloc(sizeof(xWidget), MEMORY_EXT);

	//инициализация виджета

	u16 usW, usH;

	xPicText = pxPictureGet(Pic_b2_bg);
	usW = usPictureGetW(xPicFG); // ширина
	usH = usPictureGetH(xPicFG) + usPictureGetH(xPicText);

	if (bWidgetInit(pxW, usX, usY, usW, usH, pxWidParent, true)) {

		xP = (xMenuButtonProps*)pvMemoryMalloc(sizeof(xMenuButtonProps), MEMORY_EXT);

		if (!xP)
			return NULL;

		pxW->pvProp = xP;
		pxW->eType = WidgetMenuButton;
		vWidgetSetOnClickHandler(pxW, pvClickHanlder);
		//Внешний контейнер этой кнопки не должен быть кликабельным.
		//Обработка щелчка происходит через прокси-метод prvButtonClick
		pxW->bClickable = false;

		// ----
		xP->xButton = pxButtonCreate(0, 0, xPicFG, pxW);
		bButtonSetOnClickHandler(xP->xButton, prvButtonClick);

		xP->xText = pxLabelCreate(0, usWidgetGetH(xP->xButton), 1, 1, "", FONT_ASCII_8_X, 10, pxW);
		bWidgetSetBgPicture(xP->xText, xPicText);
		vLabelSetVerticalAlign(xP->xText, LABEL_ALIGN_MIDDLE);
		vLabelSetTextAlign(xP->xText, LABEL_ALIGN_CENTER);
		vLabelSetTextColor(xP->xText, 65535);
		pcLabelSetText(xP->xText, strLabel);

		// ----
		return pxW;
	}

	else {

		vMemoryFree(pxW);
		return NULL;

	}
}

void pxMenuButtonSetMainPic(xWidget * pxW, xPicture xPic) {
	xMenuButtonProps *xP;

	if (!(xP = (xMenuButtonProps*)pxWidgetGetProps(pxW, WidgetMenuButton)))
		return;

	bWidgetSetBgPicture(xP->xButton, xPic);

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
