#include "ibuttonpress.h"

void IButtonPressEvent::SetButtonPress(XCallback& callback) {
	this->mButtonPressEvent = callback;
}

void IButtonPressEvent::OnButtonPress(IWindow* sender, XEvent& event) {
	if (this->mButtonPressEvent.callback) {
		this->mButtonPressEvent.callback(
			sender,
			event,
			this->mButtonPressEvent.data
		);
	}
}


