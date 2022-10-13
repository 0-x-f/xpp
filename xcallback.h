#ifndef X_CALLBACK_H
#define X_CALLBACK_H

#include <functional>

#include "iwindow.h"

using Callback = std::function<void(IWindow*, XEvent&, void*)>;

struct XCallback {
	void*		data;
	Callback	callback;
};

#endif // X_CALLBACK_H


