#include "iexpose.h"

void IExposeEvent::SetExpose(XCallback& callback) {
	this->mExposeEvent = callback;
}

void IExposeEvent::OnExpose(IWindow* sender, XEvent& event) {
	if (this->mExposeEvent.callback) {
		this->mExposeEvent.callback(
			sender,
			event,
			this->mExposeEvent.data
		);
	}
}


