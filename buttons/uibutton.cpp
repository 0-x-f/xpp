#include "uibutton.h"

UIButton::UIButton(XConfig& config) : IButton(config) {
	XColor		lightgray_color;
	XColor		darkgray_color;
	XGCValues	gcv_lightgray;
	XGCValues	gcv_darkgray;

	int screen = DefaultScreen(config.display);
	Colormap colormap = DefaultColormap(config.display, screen);

	XParseColor(config.display, colormap, "rgb:cc/cc/cc", &lightgray_color);
	XAllocColor(config.display, colormap, &lightgray_color);

	gcv_lightgray.foreground = lightgray_color.pixel;
	this->gc_lightgray = XCreateGC(
		config.display,
		RootWindow(config.display, screen),
		GCForeground,
		&gcv_lightgray
	);

	XParseColor(config.display, colormap, "rgb:88/88/88", &darkgray_color);
	XAllocColor(config.display, colormap, &darkgray_color);
	gcv_darkgray.foreground = darkgray_color.pixel;
	this->gc_darkgray = XCreateGC(
		config.display,
		RootWindow(config.display, screen),
		GCForeground,
		&gcv_darkgray
	);
}

void UIButton::OnButtonPress(IWindow* sender, XEvent& event) {

	XConfig conf = sender->GetConfig();
	Window win = sender->GetWindow();

	XDrawLine(conf.display, win, this->gc_darkgray,
		0, 0, conf.width - 1, 0);

	XDrawLine(conf.display, win, this->gc_darkgray,
		0, 0, 0, conf.height - 1);

	XDrawLine(conf.display, win, this->gc_lightgray,
		conf.width - 1, 0, conf.width - 1, conf.height - 1);

	XDrawLine(conf.display, win, this->gc_lightgray,
		0, conf.height - 1, conf.width - 1, conf.height - 1);

	this->IButton::OnButtonPress(sender, event);
}

void UIButton::DrawShadow(Window& window, XConfig& config) {

	XDrawLine(config.display, window, this->gc_lightgray,
		0, 0, config.width - 1, 0);

	XDrawLine(config.display, window, this->gc_lightgray,
		0, 0, 0, config.height - 1);

	XDrawLine(config.display, window, this->gc_darkgray,
		config.width - 1, 0, config.width - 1, config.height - 1);

	XDrawLine(config.display, window, this->gc_darkgray,
		0, config.height - 1, config.width - 1, config.height - 1);
}

void UIButton::OnButtonRelease(IWindow* sender, XEvent& event) {
	this->DrawShadow(this->mWindow, this->mConfig);
	this->IButton::OnButtonRelease(sender, event);
}

void UIButton::OnExpose(IWindow* sender, XEvent& event) {
	this->DrawShadow(this->mWindow, this->mConfig);
}

void UIButton::Event(XEvent& event) {
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


