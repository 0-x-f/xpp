#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <string>

#include "iwindow.h"
#include "ievents.h"
#include "xconfig.h"

class UIButton : public IWindow, public IButtonPressEvent, public IButtonReleaseEvent {
	public:
		UIButton(XConfig& window);
	public:
		virtual void SetText(const std::string& text);
	public:
		virtual void Event(XEvent& event);
	private:
		std::string mText;
};

#endif // UI_BUTTON_H

