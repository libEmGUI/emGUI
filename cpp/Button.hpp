#pragma once

#include "emGUI/emGUI.h"
#include "emGUI/cpp/Widget.hpp"
#include <functional>

namespace emGUI {

	class Button : public WidgetCaster<Button>, public Widget {
	public:
		Button(uint16_t X, uint16_t Y, uint16_t W, uint16_t H, const char *text, Widget * parent) {
			xThis = pxButtonCreateFromText(X, Y, W, H, text, parent->get());
			xThis->pvUserData = this;

			vButtonSetOnClickHandler(xThis, [](xWidget *pxW) -> bool {
				if (auto o = getObject(pxW)) {
					if(o->onClick)
						o->onClick();
				}
				return true;
			});
		}

		/*Button(const Button& a) {
			xThis->pvUserData = this;
		}*/

		std::function<void()> onClick;
	};
}