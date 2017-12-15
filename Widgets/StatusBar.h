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
#include "emGUI/Widgets/Interface.h"
#include "emGUI/Widgets/Button.h"
#include "emGUI/Widgets/Label.h"



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
		return LCD_SizeX;
	}

	/**
	  * @brief запраивает высоту виджета
	  *
	  * @returns высота в пикселях
	  */
	inline uint16_t usStatusBarGetH() {
		return LCD_STATUS_BAR_HEIGHT;
	}

	/**
	  * @brief запраивает дескриптор виджета
	  *
	  * @returns дескриптор виджета
	  */
	xStatusBar    *pxStatusBarGet();


	/**
	  * @brief запраивает дескриптор виджета часов
	  *
	  * @returns дескриптор виджета
	  */
	xLabel        *pxStatusBarGetClock();

	/**
	  * @brief устанавливает заголовок окна
	  *
	  * @param strH - заголовок
	  */
	void          vStatusBarSetWindowHeader(char * strH);

	/**
	  * @brief обновляет иконку качества связи
	  *
	  */
	void          vStatusBarUpdateCSQ();

	/**
	  * @brief меняет статус отображения контрола фильтра
	  *
	  * @param bShow - новый статус элемента
	  *
	  */
	void          vStatusBarFilterShow(bool bShow);

	/**
	  * @brief меняет статус отображения контрола информации о приборе
	  *
	  * @param bShow - новый статус элемента
	  *
	  */
	void          vStatusBarInfoShow(bool bShow);

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
