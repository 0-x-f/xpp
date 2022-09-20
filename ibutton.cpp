#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include "ibutton.h"

IButton::IButton(XConfig& button) : IWindow(button) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		ButtonPressMask | ButtonReleaseMask | ExposureMask
	);
}

void IButton::SetText(const std::string& text) {
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

//	XDrawString16(
	XDrawImageString(
		this->mConfig.display,
		this->mWindow,
		ctx,
//		DefaultGC(this->mConfig.display, DefaultScreen(this->mConfig.display)),
		this->mConfig.x,
		this->mConfig.y,
		this->mText.c_str(),
		this->mText.length()
	);
}

void IButton::Event(XEvent& event) {
	switch (event.type) {
		case ButtonPress: {
			this->OnButtonPress(this, event);
		} break;
		case ButtonRelease: {
			this->OnButtonRelease(this, event);
		} break;
		case Expose: {
			this->OnExpose(this, event);
		} break;
	}
}


