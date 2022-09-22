#ifndef IEXPOSE_H
#define IEXPOSE_H

#include "../iwindow.h"
#include "../ievent.h"

class IExposeEvent : public IEvent {
	public:
		virtual void SetExpose(XCallback& callback);
	public:
		virtual void OnExpose(IWindow* sender, XEvent& event) = 0;
	protected:
		XCallback mExposeEvent;
};

#endif // IEXPOSE_H


