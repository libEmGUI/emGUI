#ifndef __FONT_C
#define __FONT_C

#include "Fonts/Font.h"

uint16_t usFontGetStrW(char const * pcStr, xFont pubFont) {
	uint16_t usWidth = 0;

	while (*pcStr) {
		usWidth += ucFontGetCharW(*pcStr, pubFont);
		pcStr++;
	}
	return usWidth;
}

uint16_t usFontGetStrH(const char * pcStr, xFont pubFont) {
	//uint16_t usHeight = 0;

	//TODO: implement multistring height.
	  /*while (*pcStr) {
		  usWidth += ucFontGetCharW(*pcStr);
		  pcStr++;
	  }
	  return usWidth;*/

	return *(unsigned char *)pubFont[0];
}

#endif	//__FONT_C
