#pragma once

template <int ID, class Window_t> class DisposableWindow {
public:
	static Window_t* getInstance(bool create = true) {

		if (!create) { //only check if instance exists
			return getObject(pxWindowManagerGetWindow(ID));
		}

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
			if (auto w = getObject(pxW)) {
				auto close = w->onClose();
				if (close && bWindowisDisposable(pxW))
					delete w;
				return close;
			}

			return false;
		});

		vWindowSetOnCloseRequestHandler(winWidget, [](xWindow *pxW) -> bool {
			if (auto w = getObject(pxW))
				return w->onCloseRequest();

			return true;
		});

		vWindowSetOnOpenHandler(winWidget, [](xWindow *pxW) -> bool {
			if (auto w = getObject(pxW))
				return w->onOpen();

			return true;
		});

		vWindowSetOnOpenRequestHandler(winWidget, [](xWindow *pxW) -> bool {
			if (auto w = getObject(pxW))
				return w->onOpenRequest();

			return true;
		});

		vWidgetSetOnKeypressHandler(winWidget, [](xWidget *pxW, uint16_t uEv) -> bool {
			if (auto w = getObject(pxW))
				return w->onKeypress(uEv);

			return false;
		});

		winWidget->pxDrawHandler = [](xWindow *pxW) -> bool {
			if(auto w = getObject(pxW))
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
	static Window_t * getObject(xWindow *pxW) {
		if (!pxW)
			return NULL;
		auto w = (Window_t *) pxW->pvUserData;

		return w;
	}
	xWindow *thisWnd;
	int thisWndID;
};