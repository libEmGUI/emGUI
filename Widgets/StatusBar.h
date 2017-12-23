/**
 * @file   StatusBar.h
 * @author Roman Savrulin (romeo.deepmind@gmail.com)
 * @date   10.11.2012
 * @brief  Интерфейс виджета статус-бара
 *
 * Виджет отрисовывает статус-бар интерфейса
 *
 *
 */

#ifndef __STATUS_BAR_H
#define __STATUS_BAR_H

 /** \weakgroup gui-prop-widgets
  *  @{
  */

  /** \addtogroup prop-widget-statusbar Status Bar
   *  @{
   */

#include "emGUI/Widgets/Widget.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


	typedef xWidget xStatusBar; ///< тип виджета

	/**
	* @brief создает виджет
	*
	* @param usColor - цвет фона
	*
	* @returns true - успешно создан
	* @returns false - ошибка
	*/
	bool          bStatusBarCreate(uint16_t usColor);

	/**
	* @brief запраивает ширину виджета
	*
	* @returns ширина в пикселях
	*/
	inline uint16_t usStatusBarGetW() {
		return EMGUI_LCD_WIDTH;
	}

	/**
	  * @brief запраивает высоту виджета
	  *
	  * @returns высота в пикселях
	  */
	inline uint16_t usStatusBarGetH() {
		return EMGUI_STATUS_BAR_HEIGHT;
	}

	/**
	  * @brief запраивает дескриптор виджета
	  *
	  * @returns дескриптор виджета
	  */
	xStatusBar    *pxStatusBarGet();


	/**
	  * @brief устанавливает заголовок окна
	  *
	  * @param strH - заголовок
	  */
	void          vStatusBarSetWindowHeader(const char * strH);

	/**
	 *  @}
	 */
	 /**
	  *  @}
	  */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	//__STATUS_BAR_H
