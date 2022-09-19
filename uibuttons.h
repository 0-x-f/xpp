#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <string>

#include "iwindow.h"
#include "ievents.h"
#include "xconfig.h"

class UIButton : public IWindow, public IButtonPressEvent, public IButtonReleaseEvent, public IExposeEvent {
	public:
		UIButton(XConfig& button);
	public:
		virtual void Event(XEvent& event);
	private:
		std::string mText;
};

class UISimpleButton : public UIButton {
	public:
		UISimpleButton(XConfig& button);
	public:
		virtual void OnButtonPress(IWindow* sender, XEvent& event) override;
		virtual void OnButtonRelease(IWindow* sender, XEvent& event) override;
		virtual void OnExpose(IWindow* sender, XEvent& event) override;
	public:
		void SetText(const std::string& text);
	public:
		virtual void DrawButtonShadow(Window& window, XConfig& config);
	private:
		GC gc_lightgray;
		GC gc_darkgray;
};

#endif // XLIB_UI_H


