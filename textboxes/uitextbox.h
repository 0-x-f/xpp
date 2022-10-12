#ifndef UI_TEXTBOX_H
#define UI_TEXTBOX_H

#include "../itextbox.h"

class UITextBox : public ITextBox {
	public:
		UITextBox(XConfig& config, ETextBoxType type);
	public:
		virtual void OnKeyPress(IWindow* sender, XEvent& event) override;
		virtual void OnExpose(IWindow* sender, XEvent& event) override;
	public:
		virtual void SetContent(const std::string& content) override;
	public:
		virtual void DrawShadow(GC& tcolor, GC& bcolor);
		virtual void DrawContent();
	private:
		GC mColorLightgray;
		GC mColorDarkgray;
	private:
		XFontStruct* mFont;
	private:
		GC mContext;
};

#endif // UI_TEXTBOX_H


