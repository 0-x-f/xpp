#ifndef IKEY_PRESS_H
#define IKEY_PRESS_H

#include "../iwindow.h"
#include "../ievent.h"

class IKeyPressEvent : public IEvent {
	public:
		virtual void SetKeyPress(XCallback& callback);
	public:
		virtual void OnKeyPress(IWindow* sender, XEvent& event) = 0;
	protected:
		XCallback mKeyPressEvent;
};

#endif // IKEY_PRESS_H


