#ifndef UI_MESSAGEBOX_H
#define UI_MESSAGEBOX_H

#include "../imessagebox.h"

class UIMessageBox : public IMessageBox {
	public:
		UIMessageBox(XConfig& config, EMessageBoxType type);
	public:
		virtual void Event(XEvent& event) override;
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
		std::vector<std::string> Split(const std::string& text);
	private:
		GC mColorLightgray;
		GC mColorDarkgray;
	private:
		XFontStruct* mFont;
	private:
		GC mContext;
};

#endif // UI_MESSAGEBOX_H


