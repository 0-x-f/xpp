#include "itextbox.h"

ITextBox::ITextBox(XConfig& button) : IWindow(button) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		KeyPressMask | ExposureMask
	);
}

void ITextBox::SetContent(const std::string& content) {
	this->mContent = content;
}

std::string ITextBox::GetContent() const {
	return this->mContent;
}

void ITextBox::Event(XEvent& event) {
	switch (event.type) {
		case KeyPress: {
			this->OnKeyPress(this, event);
		} break;
		case Expose: {
			this->OnExpose(this, event);
		} break;
	}
}


