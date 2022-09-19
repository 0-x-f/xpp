#include <iostream>

#include "iwindow.h"
#include "uiwindow.h"

UIWindow::UIWindow(XConfig& window) : IWindow(window) {
	XSelectInput(
		window.display, this->mWindow,
		KeyPressMask | ButtonPressMask | ButtonReleaseMask
	);
}

void UIWindow::Event(XEvent& event) {
	switch (event.type) {
		case KeyPress: {
			this->OnKeyPress(this, event);
		} break;
	}
}


