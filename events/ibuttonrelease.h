#ifndef IBUTTON_RELEASE_H
#define IBUTTON_RELEASE_H

#include "../iwindow.h"
#include "../ievent.h"

class IButtonReleaseEvent : public IEvent {
	public:
		virtual void SetButtonRelease(XCallback& callback);
	public:
		virtual void OnButtonRelease(IWindow* sender, XEvent& event) = 0;
	protected:
		XCallback mButtonReleaseEvent;
};

#endif // IBUTTON_RELEASE_H


