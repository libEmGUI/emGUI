#pragma once

#include "emGUI/emGUI.h"
#include <memory>

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

	protected:
		xWidget* xThis;
		Widget() {};

	private:
		Widget(const Widget &) = delete; // if needed, put as private
		Widget & operator=(const Widget &) = delete; // if needed, put as private
		Widget(Widget &&) = delete; // if needed, put as private
		Widget & operator=(Widget &&) = delete; // if needed, put as private
	};

	template <class WidgetCaster_t = Widget>
	class WidgetCaster {
	public:
		using uniquePtr = std::unique_ptr<WidgetCaster_t>;
		static WidgetCaster_t * getObject(xWindow *pxW) {
			if (!pxW)
				return NULL;
			auto w = (WidgetCaster_t *)pxW->pvUserData;

			return w;
		}
	};
}

#if __cplusplus <= 201103L && !defined(_MSC_VER)

namespace std {

  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }

}

#endif