#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "../iwindow.h"
#include "../events/ikeypress.h"
#include "../xconfig.h"

class UIWindow : public IWindow, public IKeyPressEvent {
	public:
		UIWindow(XConfig& window);
	public:
		virtual void OnKeyPress(IWindow* sender, XEvent& event) override;
	public:
		virtual void Event(XEvent& event) override;
};

#endif // UI_WINDOW_H


