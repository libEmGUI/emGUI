#pragma once

#include "emGUI/emGUI.h"
#include "emGUI/cpp/Widget.hpp"
#include <functional>

namespace emGUI {

	class Button : public WidgetCaster<Button>, public Widget {
	public:
		Button() {};

		~Button() {
			if (xThis) {
				vButtonSetOnClickHandler(xThis, NULL);
				vWidgetDispose(xThis);
			}
		};

		Button(uint16_t X, uint16_t Y, uint16_t W, uint16_t H, const char *text, Widget * parent) {
			xThis = pxButtonCreateFromText(X, Y, W, H, text, parent->get());
			xThis->pvUserData = this;

			vButtonSetOnClickHandler(xThis, [](xWidget *pxW) -> bool {
				if (auto o = getObject(pxW)) {
					if(o->onClick)
						o->onClick(o);
				}
				return true;
			});
		}

		std::function<void(Button *b)> onClick;
	};

	class ButtonToggle : public Button {
	public:
		ButtonToggle():_state(false) {};

		ButtonToggle(uint16_t X, uint16_t Y, uint16_t W, uint16_t H, const char *text, Widget * parent):
			Button(X, Y, W, H, text, parent) {
			
			vButtonSetOnClickHandler(xThis, [](xWidget *pxW) -> bool {
				if (auto o = (ButtonToggle *) getObject(pxW)) {
					o->click();
				}
				return true;
			});
			toggleDecorator();
		}

		void state(bool state) {
			_state = state;
			toggleDecorator();
		}

		void click() {
			if (onClick)
				onClick(this);
			_state = !_state;
			toggleDecorator();
			if (onToggle)
				onToggle(this, _state);
		};

		virtual void toggleDecorator() {
			if (_state)
				vWidgetSetBgColor(get(), EMGUI_COLOR_RED, false);
			else
				vWidgetSetBgColor(get(), EMGUI_COLOR_GREEN, false);
		}

		std::function<void(ButtonToggle *b, bool)> onToggle;
	protected:
		bool _state;
	};
}