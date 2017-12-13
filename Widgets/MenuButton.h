/**
* @file   MenuButton.h
* @author Lemeshev K (konstantin.lemeshev@gmail.com)
* @date   21.02.2014
* @brief  Реализация виджета кнопки для меню и диалогов
*
*/
#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_


/** \weakgroup gui-prop-widgets
*  @{
*/

/** \addtogroup prop-widget-menu-button Menu Button
*  @{
*/

#include "Widgets/Widget.h"
#include "Widgets/Button.h"
#include "Widgets/Label.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef xWidget xMenuButton; ///< тип для кнопки меню

  /**
   * @brief создает виджет кнопки
   *
   * @param uX - положение по горизонтали относительно родительского элемента
   * @param uY - положение по веркикали относительно родительского элемента
   * @param xPicFG - указатель на картинку
   * @param strLabel - подпись под кнопкой
   * @param pvClickHanlder - обработчик нажатия
   * @param pxWidParent - родитель виджета
   *
   * @returns указатель на созданную кнопку
   */
	xMenuButton * pxMenuButtonCreate(uint16_t usX, uint16_t usY, xPicture pusPic, const char* strLabel, bool(*pvClickHanlder) (xWidget *), xWidget *pxWidParent);


  /**
   * @brief устанавливает картинку на кнопке
   *
   * @param pxW - виджет
   * @param xPic - указатель на картинку
   *
   */
	void pxMenuButtonSetMainPic(xWidget * pxW, xPicture  pusPic);

  /**
   * @brief устанавливает подпись под кнопкой
   *
   * @param pxW - виджет
   * @param xPic - указатель строку
   *
   */
	void pxMenuButtonSetLabelText(xWidget * pxW, char const* strL);

	/**
	*  @}
	*/
	/**
	*  @}
	*/
#ifdef __cplusplus
}
#endif // __cplusplus
#endif /* MENUBUTTON_H_ */
