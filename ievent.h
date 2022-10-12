#ifndef IEVENT_H
#define IEVENT_H

#include "iwindow.h"
#include <X11/Xutil.h>

using Callback = std::function<void(IWindow*, XEvent&, void*)>;

struct XCallback {
	void*		data;
	Callback	callback;
};

class IEvent {
	public:
		virtual void Event(XEvent& event) = 0;
};

#endif // IEVENT_H


