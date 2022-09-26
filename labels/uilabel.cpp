#include "uilabel.h"

UILabel::UILabel(XConfig& config) : ILabel(config) {
	// Screen color contains RGB values provided by the hardware
	// Exact color contains exact RGB values

	XColor			screenTextColor, exactTextColor;
	XGCValues		textColorValues;

	// Allocations for label text

	XAllocNamedColor(
		this->mConfig.display,
		XDefaultColormap(
			this->mConfig.display,
			DefaultScreen(this->mConfig.display)
		),
		"#000000",
		&screenTextColor,
		&exactTextColor
	);

	this->mFont = XLoadQueryFont(
		this->mConfig.display,
		"6x13"
	);

	textColorValues.foreground = screenTextColor.pixel;
	textColorValues.background = this->mConfig.background;
	textColorValues.font = this->mFont->fid;

	this->mContext = XCreateGC(
		this->mConfig.display,
		this->mWindow,
		GCForeground | GCBackground | GCFont,
		&textColorValues
	);
}

void UILabel::OnExpose(IWindow* sender, XEvent& event) {
	this->ILabel::OnExpose(sender, event);

	this->DrawText();
}

void UILabel::SetText(const std::string& text) {
	this->ILabel::SetText(text);

	this->DrawText();
}

void UILabel::DrawText() {
	int xCenter = (this->mConfig.width - (6 * this->mText.length())) / 2;
	int yCenter = (
		this->mConfig.height
		- (this->mFont->ascent + this->mFont->descent)) / 2
		+ this->mFont->ascent;

	XClearWindow(this->mConfig.display, this->mWindow);

	XDrawImageString(
		this->mConfig.display,
		this->mWindow,
		this->mContext,
		xCenter,
		yCenter,
		this->mText.c_str(),
		this->mText.length()
	);
}


