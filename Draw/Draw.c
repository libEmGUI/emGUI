#include "Draw/Draw.h"

static xDraw_t * _HDL;

void vDrawSetHandler(xDraw_t * hdl) {
	_HDL = hdl;
}

xDraw_t * pxDrawHDL() {
	return _HDL;
}