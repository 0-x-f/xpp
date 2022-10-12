#include "itextbox.h"

ITextBox::ITextBox(XConfig& button, ETextBoxType type) : IWindow(button) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		KeyPressMask | ExposureMask
	);

	this->mType = type;
}

void ITextBox::SetContent(const std::string& content) {
	this->mContent = content;
}

std::string ITextBox::GetContent() const {
	return this->mContent;
}


