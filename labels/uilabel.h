#ifndef UI_LABEL_H
#define UI_LABEL_H

#include "../ilabel.h"

class UILabel : public ILabel {
	public:
		UILabel(XConfig& label);
	public:
		virtual void OnExpose(IWindow* sender, XEvent& event) override;
	public:
		virtual void SetText(const std::string& text) override;
	public:
		virtual void DrawText();
	private:
		XFontStruct* mFont;
	private:
		GC mContext;
};

#endif // UI_LABEL_H


