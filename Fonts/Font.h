#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>
#include "options/opts.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct { // Data stored PER GLYPH
		uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
		uint8_t  width, height;    // Bitmap dimensions in pixels
		uint8_t  xAdvance;         // Distance to advance cursor (x axis)
		int8_t   xOffset, yOffset; // Dist from cursor pos to UL corner
	} GFXglyph;

	typedef struct { // Data stored for FONT AS A WHOLE:
		uint8_t  *bitmap;      // Glyph bitmaps, concatenated
		GFXglyph *glyph;       // Glyph array
		uint32_t  first, last; // ASCII extents
		uint8_t   yAdvance;    // Newline distance (y axis)
	} GFXfont;

	typedef XFONT_TYPE xFont; //TODO: Add GFXFont segmented struct to allow UTF-8 fonts support!
	
	extern const GFXfont FreeSans9pt7b;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	//__FONT_H
