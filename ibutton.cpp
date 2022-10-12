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


