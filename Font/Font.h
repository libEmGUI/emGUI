#ifndef __FONT_H
#define __FONT_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include "stm32f10x.h"
  
typedef unsigned char const * const * xFont;
  
u16 usFontGetStrW(const char * pcStr, xFont pubFont);

inline char ucFontGetCharW(char cChar, xFont pubFont){
  return *(unsigned char *) pubFont[cChar];
}

u16 usFontGetH(xFont pubFont);
u16 usFontGetStrH(const char * pcStr, xFont pubFont);

#ifdef __cplusplus
}
#endif

#endif	//__FONT_H
