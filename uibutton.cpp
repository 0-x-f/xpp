#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include "uibutton.h"

UIButton::UIButton(XConfig& button) : IWindow(button) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		ButtonPressMask | ButtonReleaseMask
	);
}

void UIButton::SetText(const std::string& text) {
	this->mText = text;

	XGCValues values;
	XColor colorScreenDef, colorExactDef;

	XAllocNamedColor(
		this->mConfig.display,
		XDefaultColormap(
			this->mConfig.display,
			DefaultScreen(this->mConfig.display)
		),
		"red",
		&colorScreenDef,
		&colorExactDef
	);

	values.foreground = colorScreenDef.pixel;

	GC ctx = XCreateGC(
		this->mConfig.display,
		this->mWindow,
		GCForeground | GCBackground,
		&values
	);
}

void UIButton::Event(XEvent& event) {
	switch (event.type) {
		case ButtonPress: {
			this->OnButtonPress(this, event);
		} break;
		case ButtonRelease: {
			this->OnButtonRelease(this, event);
		}
	}
}


