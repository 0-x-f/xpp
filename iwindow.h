#ifndef IWINDOW_H
#define IWINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <functional>

#include "xconfig.h"

class IWindow {
	public:
		IWindow(XConfig& window);
	public:
		virtual void Show();
		virtual void Hide();
	public:
		virtual Window GetWindow() const;
		virtual XConfig GetConfig() const;
	public:
		virtual int GetX() const;
		virtual int GetY() const;
	protected:
		Window mWindow;
		XConfig mConfig;

};

using Callback = std::function<void(IWindow*, XEvent&, void*)>;

struct XCallback {
	void*		data;
	Callback	callback;
};


#endif // IWINDOW_H
