#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	extern unsigned char const* const FONT_ASCII_8_X[];
	extern unsigned char const* const FONT_ASCII_16_X[];

	typedef unsigned char const * const * xFont;

	uint16_t usFontGetStrW(const char * pcStr, xFont pubFont);

	inline char ucFontGetCharW(char cChar, xFont pubFont) {
		return *(unsigned char *)pubFont[(unsigned int)cChar];
	}

	inline uint16_t usFontGetH(xFont pubFont) {
		//uint16_t usHeight = 0;

		//TODO: implement multistring height.
		  /*while (*pcStr) {
			  usWidth += *(unsigned char *) pubFont[*pcStr];
			  pcStr++;
		  }
		  return usWidth;*/

		return *(unsigned char *)pubFont[0];
	}
	uint16_t usFontGetStrH(const char * pcStr, xFont pubFont);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	//__FONT_H
