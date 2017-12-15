#include "emGUI/Draw/Draw.h"
#include <string.h>

static xDraw_t * _HDL;

void vDrawSetHandler(xDraw_t * hdl) {
	_HDL = hdl;
}

xDraw_t * pxDrawHDL() {
	return _HDL;
}

void vDrawHandlerInit(xDraw_t * hdl) {
	memset(hdl, 0, sizeof(xDraw_t));
}