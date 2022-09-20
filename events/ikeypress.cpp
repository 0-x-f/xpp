#include "ikeypress.h"

void IKeyPressEvent::SetKeyPress(XCallback& callback) {
	this->mKeyPressEvent = callback;
}

void IKeyPressEvent::OnKeyPress(IWindow* sender, XEvent& event) {
	if (this->mKeyPressEvent.callback) {
		this->mKeyPressEvent.callback(
			sender,
			event,
			this->mKeyPressEvent.data
		);
	}
}


