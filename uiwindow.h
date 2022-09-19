#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "iwindow.h"
#include "ievents.h"
#include "xconfig.h"

class UIWindow : public IWindow, public IKeyPressEvent {
	public:
		UIWindow(XConfig& window);
	public:
		virtual void Event(XEvent& event);
};

#endif // UI_WINDOW_H


