#pragma once

#include "emGUI/emGUI.h"

template <int ID, class Window_t> class DisposableWindow {
public:
	static Window_t* open() {
		auto winWidget = pxWindowCreate(ID);

		if (!winWidget) { // maybe already opened?
			vWindowManagerOpenWindow(ID);
			return NULL;
		}

		vWindowSetDisposable(winWidget, true);

		auto w = new Window_t();
		w->thisWnd = winWidget;
		w->thisWndID = ID;
		w->thisWnd->pvUserData = w;
		w->create();

		vWindowSetOnCloseHandler(winWidget, [](xWindow *pxW) -> bool {
			if (auto w = getUserData(pxW)) {
				auto close = w->onClose();
				if (close && bWindowisDisposable(pxW))
					delete w;
				return close;
			}

			return false;
		});

		vWindowSetOnCloseRequestHandler(winWidget, [](xWindow *pxW) -> bool {
			if (auto w = getUserData(pxW))
				return w->onCloseRequest();

			return true;
		});

		vWindowSetOnOpenHandler(winWidget, [](xWindow *pxW) -> bool {
			if (auto w = getUserData(pxW))
				return w->onOpen();

			return true;
		});

		vWindowSetOnOpenRequestHandler(winWidget, [](xWindow *pxW) -> bool {
			if (auto w = getUserData(pxW))
				return w->onOpenRequest();

			return true;
		});

		vWidgetSetOnKeypressHandler(winWidget, [](xWidget *pxW, uint16_t uEv) -> bool {
			if (auto w = getUserData(pxW))
				return w->onKeypress(uEv);

			return false;
		});

		winWidget->pxDrawHandler = [](xWindow *pxW) -> bool {
			if(auto w = getUserData(pxW))
				w->onDrawUpdate();

			return bWidgetDrawHandler(pxW);
		};
		
		vWindowManagerOpenWindow(ID);

		return w;
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
	static DisposableWindow<ID, Window_t> * getUserData(xWindow *pxW) {
		auto w = (DisposableWindow<ID, Window_t> *) pxW->pvUserData;

		return w;
	}
	xWindow *thisWnd;
	int thisWndID;
};