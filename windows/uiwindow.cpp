#include "uiwindow.h"

UIWindow::UIWindow(XConfig& window) : IWindow(window) {
	XSelectInput(
		window.display, this->mWindow,
		KeyPressMask | ButtonPressMask | ButtonReleaseMask
	);
}

void UIWindow::OnKeyPress(IWindow* sender, XEvent& event) {
	if (this->mKeyPressEvent.callback) {
		this->mKeyPressEvent.callback(
			sender,
			event,
			this->mKeyPressEvent.data
		);
	}
}

void UIWindow::Event(XEvent& event) {
	switch (event.type) {
		case KeyPress: {
			this->OnKeyPress(this, event);
		} break;
	}
}


