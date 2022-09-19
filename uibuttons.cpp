#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include "uibuttons.h"

// UIButton
UIButton::UIButton(XConfig& button) : IWindow(button) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		ButtonPressMask | ButtonReleaseMask | ExposureMask
	);
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

// UISimpleButton
UISimpleButton::UISimpleButton(XConfig& button) : UIButton(button) {

	XColor		lightgray_color;
	XColor		darkgray_color;
	XGCValues	gcv_lightgray;
	XGCValues	gcv_darkgray;
	
	int screen = DefaultScreen(button.display);
	Colormap colormap = DefaultColormap(button.display, screen);
	
	XParseColor(button.display, colormap, "rgb:cc/cc/cc", &lightgray_color);
	XAllocColor(button.display, colormap, &lightgray_color);
	gcv_lightgray.foreground = lightgray_color.pixel;	
	this->gc_lightgray = XCreateGC(
		button.display, 
		RootWindow(button.display, screen),
		GCForeground, 
		&gcv_lightgray
	);
		
	XParseColor(button.display, colormap, "rgb:88/88/88", &darkgray_color);
	XAllocColor(button.display, colormap, &darkgray_color);
	gcv_darkgray.foreground = darkgray_color.pixel;	
	this->gc_darkgray = XCreateGC(
		button.display, 
		RootWindow(button.display, screen),
		GCForeground, 
		&gcv_darkgray
	);
}

void UISimpleButton::OnButtonPress(IWindow* sender, XEvent& event) {

	XConfig conf = sender->GetConfig();
	Window win = sender->GetWindow();

	XDrawLine(conf.display, win, this->gc_darkgray, 
		0, 0, conf.width-1, 0);

	XDrawLine(conf.display, win, this->gc_darkgray, 
		0, 0, 0, conf.height-1);

	XDrawLine(conf.display, win, this->gc_lightgray, 
		conf.width-1, 0, conf.width-1, conf.height-1);

	XDrawLine(conf.display, win, this->gc_lightgray, 
		0, conf.height-1, conf.width-1, conf.height-1);
	
	this->UIButton::OnButtonPress(sender, event);
}

void UISimpleButton::DrawButtonShadow(Window& window, XConfig& config) {

	XDrawLine(config.display, window, this->gc_lightgray, 
		0, 0, config.width-1, 0);

	XDrawLine(config.display, window, this->gc_lightgray, 
		0, 0, 0, config.height-1);
	
	XDrawLine(config.display, window, this->gc_darkgray, 
		config.width-1, 0, config.width-1, config.height-1);
	
	XDrawLine(config.display, window, this->gc_darkgray, 
		0, config.height-1, config.width-1, config.height-1);
}

void UISimpleButton::OnButtonRelease(IWindow* sender, XEvent& event) {
	this->DrawButtonShadow(this->mWindow, this->mConfig);
	this->UIButton::OnButtonPress(sender, event);
}

void UISimpleButton::OnExpose(IWindow* sender, XEvent& event) {
	this->DrawButtonShadow(this->mWindow, this->mConfig);
	this->UIButton::OnExpose(sender, event);
}
