/**
 * @file   StatusBar.h
 * @author Roman Savrulin (romeo.deepmind@gmail.com)
 * @date   10.11.2012
 * @brief  Status Bar Widget interface
 *
 *
 */

#ifndef EMGUI_STATUS_BAR_H
#define EMGUI_STATUS_BAR_H

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
	* @brief creates Status Bar Widget
	*
	* @param usColor - Background color
	*
	* @returns pxW - pointer to created instance
	* @returns NULL - in case of error
	*/
	xStatusBar*         xStatusBarCreate(uint16_t usColor);

	/**
	  * @brief Sets window header
	  *
	  * @param pxW - Status  bar instance pointer
	  * @param strH - header
	  */
	void  vStatusBarSetWindowHeader(xStatusBar* pxW, const char * strH);

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
