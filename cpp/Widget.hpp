#pragma once

#include "emGUI/emGUI.h"

namespace emGUI {

	class Widget {
	public:
		xWidget* get() const {
			return xThis;
		};

		uint16_t W() const {
			return usWidgetGetW(xThis);
		}

		uint16_t H() const {
			return usWidgetGetH(xThis);
		}

		Widget& operator= (Widget& a) {
			xThis = a.xThis;
			a.xThis = NULL;
			if(xThis)
				xThis->pvUserData = this;

			return *this;
		}
	protected:
		xWidget* xThis;
	};

	template <class Widget_t = WidgetBase>
	class WidgetCaster {
	protected:
		static Widget_t * getObject(xWindow *pxW) {
			if (!pxW)
				return NULL;
			auto w = (Widget_t *)pxW->pvUserData;

			return w;
		}
	};
}