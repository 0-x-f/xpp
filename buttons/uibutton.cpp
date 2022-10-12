#include "uibutton.h"

UIButton::UIButton(XConfig& config) : IButton(config) {
	// Screen color contains RGB values provided by the hardware
	// Exact color contains exact RGB values

	XColor		screenLightGrayColor, exactLightGrayColor;
	XColor		screenDarkGrayColor, exactDarkGrayColor;
	XGCValues	lightGrayValues;
	XGCValues	darkGrayValues;

	XColor			screenTextColor, exactTextColor;
	XGCValues		textColorValues;

	// Allocations for button shadow

	XAllocNamedColor(
		this->mConfig.display,
		XDefaultColormap(
			this->mConfig.display,
			DefaultScreen(this->mConfig.display)
		),
		"#cccccc",
		&screenLightGrayColor,
		&exactLightGrayColor
	);

	XAllocNamedColor(
		this->mConfig.display,
		XDefaultColormap(
			this->mConfig.display,
			DefaultScreen(this->mConfig.display)
		),
		"#888888",
		&screenDarkGrayColor,
		&exactDarkGrayColor
	);
 
	lightGrayValues.foreground = screenLightGrayColor.pixel;
	this->mColorLightgray = XCreateGC(
		this->mConfig.display,
		this->mConfig.parent,
		GCForeground,
		&lightGrayValues
	);

	darkGrayValues.foreground = screenDarkGrayColor.pixel;
	this->mColorDarkgray = XCreateGC(
		this->mConfig.display,
		this->mConfig.parent,
		GCForeground,
		&darkGrayValues
	);

	// Allocations for button text

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

	textColorValues.foreground = exactTextColor.pixel;
	textColorValues.background = this->mConfig.background;
	textColorValues.font = this->mFont->fid;

	this->mContext = XCreateGC(
		this->mConfig.display,
		this->mWindow,
		GCForeground | GCBackground | GCFont,
		&textColorValues
	);
}

void UIButton::OnButtonPress(IWindow* sender, XEvent& event) {
	this->IButton::OnButtonPress(sender, event);

	this->DrawShadow(this->mColorDarkgray, this->mColorLightgray);
}

void UIButton::OnButtonRelease(IWindow* sender, XEvent& event) {
	this->IButton::OnButtonRelease(sender, event);

	this->DrawShadow(this->mColorLightgray, this->mColorDarkgray);
}

void UIButton::OnExpose(IWindow* sender, XEvent& event) {
	this->IButton::OnExpose(sender, event);

	this->DrawText();
	this->DrawShadow(this->mColorLightgray, this->mColorDarkgray);
}

void UIButton::SetText(const std::string& text) {
	this->IButton::SetText(text);

	this->DrawText();
}

void UIButton::DrawShadow(GC& tcolor, GC& bcolor) {
	XDrawLine(
		this->mConfig.display,
		this->mWindow,
		tcolor,
		0,
		0,
		this->mConfig.width - 1,
		0
	);

	XDrawLine(
		this->mConfig.display,
		this->mWindow,
		tcolor,
		0,
		0,
		0,
		this->mConfig.height - 1
	);

	XDrawLine(
		this->mConfig.display,
		this->mWindow,
		bcolor,
		this->mConfig.width - 1,
		0,
		this->mConfig.width - 1,
		this->mConfig.height - 1
	);

	XDrawLine(
		this->mConfig.display,
		this->mWindow,
		bcolor,
		0,
		this->mConfig.height - 1,
		this->mConfig.width - 1,
		this->mConfig.height - 1
	);
}

void UIButton::DrawText() {
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

void UIButton::Event(XEvent& event) {
	if (this->IWindow::IsOwner(event)) {
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
}


