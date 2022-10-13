#include "imessagebox.h"

IMessageBox::IMessageBox(XConfig& config, EMessageBoxType type) :
	IWindow(config) {

	XSelectInput(
		this->mConfig.display, this->mWindow,
		ButtonPressMask | ExposureMask
	);

	this->mType = type;
}

void IMessageBox::SetText(const std::string& text) {
	this->mText = text;
}


