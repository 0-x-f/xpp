#include "ibuttonrelease.h"

void IButtonReleaseEvent::SetButtonRelease(XCallback& callback) {
	this->mButtonReleaseEvent = callback;
}

void IButtonReleaseEvent::OnButtonRelease(IWindow* sender, XEvent& event) {
	if (this->mButtonReleaseEvent.callback) {
		this->mButtonReleaseEvent.callback(
			sender,
			event,
			this->mButtonReleaseEvent.data
		);
	}
}


