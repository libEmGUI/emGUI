#ifndef OPTS_H
#define OPTS_H


// TODO: fix that path crap
#include "../emGUI-example/emGUI_opts.h"

typedef unsigned short const* xPicture;

#ifndef DEBUG_EMGUI
#define DEBUG_EMGUI 0
#endif // !DEBUG_EMGUI

#ifndef LCD_TsBtn_SIZE
#define LCD_TsBtn_SIZE 100
#endif // !LCD_TsBtn_SIZE

#ifndef LCD_SizeX
#define LCD_SizeX 240
#endif  

#ifndef LCD_SizeY
#define LCD_SizeY 240
#endif 

#ifndef LCD_STATUS_BAR_HEIGHT
#define LCD_STATUS_BAR_HEIGHT 26
#endif 

#ifndef STATUS_BAR_FILT_INFO_GAP
#define STATUS_BAR_FILT_INFO_GAP 5 ///< расстояние м/д элементами
#endif 
#ifndef STATUS_BAR_CROSS_PIC 
#define SRATUS_BAR_CROSS_PIC cross
#endif 

#ifndef WIDGET_COLOR_WHITE
#define WIDGET_COLOR_WHITE 0xFFFF
#endif

#ifndef WIDGET_COLOR_BLACK
#define WIDGET_COLOR_BLACK 0
#endif

#ifndef WINDOW_HEADER_LENGTH
#define WINDOW_HEADER_LENGTH 25
#endif

#ifndef LABEL_MAX_LENGTH
#define LABEL_MAX_LENGTH 10000
#endif


//GUI COLORS

#ifndef ColorMenuHeaderText
#define ColorMenuHeaderText WIDGET_COLOR_BLACK //black
#endif




#endif // !OPTS_H
