#include "iwindow.h"

IWindow::IWindow(XConfig& window) {
	this->mConfig = window;
	this->mWindow = XCreateSimpleWindow(
		this->mConfig.display,
		this->mConfig.parent,
		this->mConfig.x,
		this->mConfig.y,
		this->mConfig.width,
		this->mConfig.height,
		this->mConfig.borderWidth,
		this->mConfig.border,
		this->mConfig.background
	);
}

Window IWindow::GetWindow() const {
	return this->mWindow;
}

XConfig IWindow::GetConfig() const {
	return this->mConfig;
}

int IWindow::GetX() const {
	return this->mConfig.x;
}

int IWindow::GetY() const {
	return this->mConfig.y;
}

unsigned int IWindow::GetWidth() const {
	return this->mConfig.width;
}

unsigned int IWindow::GetHeight() const {
	return this->mConfig.height;
}

void IWindow::Show() {
	XMapWindow(this->mConfig.display, this->mWindow);
}

void IWindow::Hide() {
	XUnmapWindow(this->mConfig.display, this->mWindow);
}

bool IWindow::IsOwner(XEvent& event) const {
	return event.xany.window == this->GetWindow();
}


