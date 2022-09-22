#include "uibutton.h"

#include <cstring>

UIButton::UIButton(XConfig& config) : IButton(config) {
	// Screen color contains RGB values provided by the hardware
	// Exact color contains exact RGB values

	XColor		screenLightGrayColor, exactLightGrayColor;
	XColor		screenDarkGrayColor, exactDarkGrayColor;
	XGCValues	lightGrayValues;
	XGCValues	darkGrayValues;

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
}

void UIButton::OnButtonPress(IWindow* sender, XEvent& event) {
	this->DrawShadow(this->mColorDarkgray, this->mColorLightgray);

	this->IButton::OnButtonPress(sender, event);
}

void UIButton::OnButtonRelease(IWindow* sender, XEvent& event) {
	this->DrawShadow(this->mColorLightgray, this->mColorDarkgray);

	this->IButton::OnButtonRelease(sender, event);
}

void UIButton::OnExpose(IWindow* sender, XEvent& event) {
	this->DrawShadow(this->mColorLightgray, this->mColorDarkgray);
	this->DrawText();

	this->IButton::OnExpose(sender, event);
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
	XGCValues values;
	XColor screenTextColor, exactTextColor;
	XFontStruct* fontStruct;
	Font font;

	XAllocNamedColor(
		this->mConfig.display,
		XDefaultColormap(
			this->mConfig.display,
			DefaultScreen(this->mConfig.display)
		),
		"black",
		&screenTextColor,
		&exactTextColor
	);

	fontStruct = XLoadQueryFont(
		this->mConfig.display,
		"6x13"
	);

	values.foreground = exactTextColor.pixel;
	values.background = this->mConfig.background;
	values.font = fontStruct->fid;

	GC ctx = XCreateGC(
		this->mConfig.display,
		this->mWindow,
		GCForeground | GCBackground | GCFont,
		&values
	);

	int xCenter = (this->mConfig.width - (6 * this->mText.length())) / 2;
	int yCenter = (
		this->mConfig.height
		- (fontStruct->ascent + fontStruct->descent)) / 2
		+ fontStruct->ascent;

	XDrawImageString(
		this->mConfig.display,
		this->mWindow,
		ctx,
		xCenter,
		yCenter,
		this->mText.c_str(),
		this->mText.length()
	);
}


