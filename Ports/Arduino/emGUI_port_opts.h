#ifndef EMGUI_PORT_OPTS_H
#define EMGUI_PORT_OPTS_H


#include <stdint.h>

#ifdef __AVR__
 #include <avr/io.h>
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#else
 #define PROGMEM
#endif

#define XPICTURE_TYPE  unsigned short const*

#define EM_GUI_PICTURE_STORAGE_ATTR PROGMEM
#define EM_GUI_OVERRIDE_DEFAULT_FONTS

#endif // !ARDIUNO_OPTS_H
