#ifndef UI_EVENTS_H
#define UI_EVENTS_H

#include <X11/Xlib.h>

#include "iwindow.h" 

class IButtonPressEvent {
	public:
		virtual void SetButtonPress(XCallback& callback);
	public:
		virtual void OnButtonPress(IWindow* sender, XEvent& event);
	protected:
		XCallback mButtonPressEvent;
};

class IButtonReleaseEvent {
	public:
		virtual void SetButtonRelease(XCallback& callback);
	public:
		virtual void OnButtonRelease(IWindow* sender, XEvent& event);
	protected:
		XCallback mButtonReleaseEvent;
};

class IKeyPressEvent {
	public:
		virtual void SetKeyPress(XCallback& callback);
	public:
		virtual void OnKeyPress(IWindow* sender, XEvent& event);
	protected:
		XCallback mKeyPressEvent;
};

class IExposeEvent {
	public:
		virtual void SetExpose(XCallback& callback);
	public:
		virtual void OnExpose(IWindow* sender, XEvent& event);
	protected:
		XCallback mExposeEvent;
};

#endif // UI_EVENTS_H
