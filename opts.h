#ifndef OPTS_H
#define OPTS_H

#include "emGUI_opts.h"

#include "Fonts/Font.h"

#ifndef DEBUG_EMGUI
#define DEBUG_EMGUI				0
#endif // !DEBUG_EMGUI

#ifndef LCD_TsBtn_SIZE
#define LCD_TsBtn_SIZE			100
#endif // !LCD_TsBtn_SIZE

#ifndef LCD_SizeX
#define LCD_SizeX				240
#endif  

#ifndef LCD_SizeY
#define LCD_SizeY				240
#endif 

#ifndef LCD_STATUS_BAR_HEIGHT
#define LCD_STATUS_BAR_HEIGHT	26
#endif 

#ifndef STATUS_BAR_FILT_INFO_GAP
#define STATUS_BAR_FILT_INFO_GAP 5 ///< расстояние м/д элементами
#endif 


#ifndef WIDGET_COLOR_WHITE
#define WIDGET_COLOR_WHITE		0xFFFF
#endif

#ifndef WIDGET_COLOR_BLACK
#define WIDGET_COLOR_BLACK		0
#endif

#ifndef WINDOW_HEADER_LENGTH
#define WINDOW_HEADER_LENGTH	25
#endif

#ifndef LABEL_MAX_LENGTH
#define LABEL_MAX_LENGTH 10000
#endif


// DEFAULT IMAGES

#ifndef XPICTURE_TYPE
#define XPICTURE_TYPE  unsigned short const*
#endif

typedef XPICTURE_TYPE xPicture;

#ifndef OVERRIDE_DEFAULT_PICS
	#include "Images/Images.h"

	#ifndef STATUS_BAR_CROSS_PIC 
	#define STATUS_BAR_CROSS_PIC	close
	#endif 

	#ifndef PIC_LABEL_BG 
	#define PIC_LABEL_BG			label_bg
	#endif

	#ifndef PIC_YES 
	#define PIC_YES					yes
	#endif

	#ifndef PIC_NO 
	#define PIC_NO					no
	#endif

	#ifndef PIC_REFRESH 
	#define PIC_REFRESH				refresh
	#endif
	
	// TODO: MAKE RETURN BUTTON !!
	#ifndef PIC_RETURN 
	#define PIC_RETURN				refresh
	#endif
#else
	#ifndef STATUS_BAR_CROSS_PIC 
	#error "Please define STATUS_BAR_CROSS_PIC"
	#endif 

	#ifndef PIC_LABEL_BG 
	#error "Please define PIC_LABEL_BG"
	#endif
#endif // !OVERRIDE_DEFAULT_PICS


// GUI COLORS

// RGB565 definition
#define SEA_COLOR5 0x02AC	// Sea colors map from drakest to lightest
#define SEA_COLOR4 0x1B2E
#define SEA_COLOR3 0x0413
#define SEA_COLOR2 0x3599
#define SEA_COLOR1 0x5DD9 

#define EARTH_COLOR5 0xA280	// Earth colors map from drakest to lightest
#define EARTH_COLOR4 0xBBA5
#define EARTH_COLOR3 0xFBC0
#define EARTH_COLOR2 0xFCC7
#define EARTH_COLOR1 0xFDAD 


#ifndef ColorMenuHeaderText
#define ColorMenuHeaderText WIDGET_COLOR_WHITE //black
#endif

#ifndef ColorEcgBackground
#define ColorEcgBackground WIDGET_COLOR_WHITE
#endif // !ColorEcgBackground

#ifndef ColorMessageHeaderBackground
#define ColorMessageHeaderBackground EARTH_COLOR1
#endif // !ColorMessageHeaderBackground

#ifndef ColorMessageHeaderText
#define ColorMessageHeaderText WIDGET_COLOR_BLACK
#endif // !ColorMessageHeaderText

#ifndef MENU_BUTTON_LABEL_TEXT_COLOR
#define MENU_BUTTON_LABEL_TEXT_COLOR WIDGET_COLOR_BLACK
#endif // MENU_BUTTON_LABEL_TEXT_COLOR

#ifndef MENU_BUTTON_LABEL_BG_COLOR
#define MENU_BUTTON_LABEL_BG_COLOR WIDGET_COLOR_WHITE
#endif // MENU_BUTTON_LABEL_TEXT_COLOR


#ifndef STATUS_BAR_BG
#define STATUS_BAR_BG SEA_COLOR5 //light-blue
#endif


#endif // !OPTS_H
