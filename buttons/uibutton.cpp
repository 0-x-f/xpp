#include "uibutton.h"

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
		&screenLightGrayColor,
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
	XColor colorScreenDef, colorExactDef;

	XAllocNamedColor(
		this->mConfig.display,
		XDefaultColormap(
			this->mConfig.display,
			DefaultScreen(this->mConfig.display)
		),
		"black",
		&colorScreenDef,
		&colorExactDef
	);

	values.foreground = colorScreenDef.pixel;
	values.background = this->mConfig.background;

	GC ctx = XCreateGC(
		this->mConfig.display,
		this->mWindow,
		GCForeground | GCBackground,
		&values
	);

	XDrawImageString(
		this->mConfig.display,
		this->mWindow,
		ctx,
		this->mConfig.x / 2,
		this->mConfig.y / 2,
		this->mText.c_str(),
		this->mText.length()
	);
}


