#ifndef __FONT_C
#define __FONT_C

#include "Font.h"

u16 usFontGetStrW(const char * pcStr, xFont pubFont){
  u16 usWidth = 0;

	while (*pcStr) {
		usWidth += ucFontGetCharW(*pcStr, pubFont);
		pcStr++;
	}
	return usWidth;
}

u16 usFontGetStrH(const char * pcStr, xFont pubFont){
  //u16 usHeight = 0;

  //TODO: implement multistring height.
	/*while (*pcStr) {
		usWidth += ucFontGetCharW(*pcStr);
		pcStr++;
	}
	return usWidth;*/
  
  return *(unsigned char *) pubFont[0];
}

u16 usFontGetH(xFont pubFont){
  //u16 usHeight = 0;

  //TODO: implement multistring height.
	/*while (*pcStr) {
		usWidth += *(unsigned char *) pubFont[*pcStr];
		pcStr++;
	}
	return usWidth;*/
  
  return *(unsigned char *) pubFont[0];
}

#endif	//__FONT_C
