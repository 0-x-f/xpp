#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "../ibutton.h"

class UIButton : public IButton {
	public:
		UIButton(XConfig& button);
	public:
		virtual void OnButtonPress(IWindow* sender, XEvent& event) override;
		virtual void OnButtonRelease(IWindow* sender, XEvent& event) override;
		virtual void OnExpose(IWindow* sender, XEvent& event) override;
	public:
		virtual void SetText(const std::string& text) override;
	public:
		virtual void DrawShadow(GC& tcolor, GC& bcolor);
		virtual void DrawText();
	private:
		GC mColorLightgray;
		GC mColorDarkgray;
	private:
		XFontStruct* mFont;
	private:
		GC mContext;
};

#endif // UI_BUTTON_H


