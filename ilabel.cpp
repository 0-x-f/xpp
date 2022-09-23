#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include "ilabel.h"

ILabel::ILabel(XConfig& label) : IWindow(label) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		ExposureMask
	);
}

void ILabel::SetText(const std::string& text) {
	this->mText = text;
}

void ILabel::Event(XEvent& event) {
	switch (event.type) {
		case Expose: {
			this->OnExpose(this, event);
		} break;
	}
}


