#ifndef IBUTTON_PRESS_H
#define IBUTTON_PRESS_H

#include "../iwindow.h"
#include "../ievent.h"

class IButtonPressEvent : public IEvent {
	public:
		virtual void SetButtonPress(XCallback& callback);
	public:
		virtual void OnButtonPress(IWindow* sender, XEvent& event) = 0;
	protected:
		XCallback mButtonPressEvent;
};

#endif // IBUTTON_PRESS_H


