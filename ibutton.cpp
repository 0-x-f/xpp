#include "ibutton.h"

IButton::IButton(XConfig& button) : IWindow(button) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		ButtonPressMask | ButtonReleaseMask | ExposureMask
	);
}

void IButton::SetText(const std::string& text) {
	this->mText = text;
}

void IButton::Event(XEvent& event) {
	switch (event.type) {
		case ButtonPress: {
			this->OnButtonPress(this, event);
		} break;
		case ButtonRelease: {
			this->OnButtonRelease(this, event);
		} break;
		case Expose: {
			this->OnExpose(this, event);
		} break;
	}
}


