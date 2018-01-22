#pragma once

#include "emGUI/emGUI.h"
#include "emGUI/cpp/Widget.hpp"

namespace emGUI {

	template <int ID, class Widget_t> class DisposableWindow :
		public WidgetCaster<Widget_t>, public Widget {
	public:
		static Widget_t* getInstance(bool create = true) {

			if (!create) { //only check if instance exists
				return WidgetCaster<Widget_t>::getObject(pxWindowManagerGetWindow(ID));
			}

			auto winWidget = pxWindowCreate(ID);

			if (!winWidget) { // maybe already opened?
				vWindowManagerOpenWindow(ID);
				return NULL;
			}

			vWindowSetDisposable(winWidget, true);

			auto w = new Widget_t();
			w->xThis = winWidget;
			w->thisWndID = ID;
			w->xThis->pvUserData = w;
			w->create();

			vWindowSetOnCloseHandler(winWidget, [](xWindow *pxW) -> bool {
				if (auto w = WidgetCaster<Widget_t>::getObject(pxW)) {
					auto close = w->onClose();
					if (close && bWindowisDisposable(pxW))
						delete w;
					return close;
				}

				return false;
			});

			vWindowSetOnCloseRequestHandler(winWidget, [](xWindow *pxW) -> bool {
				if (auto w = WidgetCaster<Widget_t>::getObject(pxW))
					return w->onCloseRequest();

				return true;
			});

			vWindowSetOnOpenHandler(winWidget, [](xWindow *pxW) -> bool {
				if (auto w = WidgetCaster<Widget_t>::getObject(pxW))
					return w->onOpen();

				return true;
			});

			vWindowSetOnOpenRequestHandler(winWidget, [](xWindow *pxW) -> bool {
				if (auto w = WidgetCaster<Widget_t>::getObject(pxW))
					return w->onOpenRequest();

				return true;
			});

			vWidgetSetOnKeypressHandler(winWidget, [](xWidget *pxW, uint16_t uEv) -> bool {
				if (auto w = WidgetCaster<Widget_t>::getObject(pxW))
					return w->onKeypress(uEv);

				return false;
			});

			winWidget->pxDrawHandler = [](xWindow *pxW) -> bool {
				if (auto w = WidgetCaster<Widget_t>::getObject(pxW))
					w->onDrawUpdate();

				return bWidgetDrawHandler(pxW);
			};

			return w;
		}

		void open() {
			vWindowManagerOpenWindow(ID);
		}

		void close() {
			vWindowManagerCloseWindow(ID);
		}

		virtual bool onClose() { return true; }
		virtual bool onCloseRequest() { return true; }

		virtual bool onOpen() { return true; }
		virtual bool onOpenRequest() { return true; }

		virtual bool onDrawUpdate() { return true; }

		virtual bool onKeypress(uint16_t uEv) {
			return false;
		}

	protected:
		int thisWndID;
	};

}