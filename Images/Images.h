#ifndef __IMAGES_H
#define __IMAGES_H

#include "options/opts.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef XPICTURE_TYPE xPicture;

#ifndef ARDUINO
	#include "emGUI_static_images.h"
#else
	#include "Ports/Arduino/emGUI_static_images.h"
#endif


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__IMAGES_H
