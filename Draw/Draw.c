#include "Draw/Draw.h"
#include <memory.h>

static xDraw_t * _HDL;

#ifndef OVERRIDE_DEFAULT_PICS

static uint16_t usGetPictureW(xPicture pusPic) {
	return pusPic[1];
}

static uint16_t usGetPictureH(xPicture pusPic) {
	return pusPic[0];
}

#endif // !OVERRIDE_DEFAULT_PICS



void vDrawSetHandler(xDraw_t * hdl) {
	_HDL = hdl;
}

xDraw_t * pxDrawHDL() {
	return _HDL;
}

void vDrawHandlerInit(xDraw_t * hdl) {
	memset(hdl, 0, sizeof(xDraw_t));
#ifndef OVERRIDE_DEFAULT_PICS
	hdl->usGetPictureH = usGetPictureH;
	hdl->usGetPictureW = usGetPictureW;
#endif
}