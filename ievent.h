#ifndef IEVENT_H
#define IEVENT_H

#include <X11/Xutil.h>

class IEvent {
	public:
		virtual void Event(XEvent& event) = 0;
};

#endif // IEVENT_H


