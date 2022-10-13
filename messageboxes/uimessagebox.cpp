#include "uimessagebox.h"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

UIMessageBox::UIMessageBox(XConfig& config, EMessageBoxType type) :
	IMessageBox(config, type) {

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

void UIMessageBox::OnButtonPress(IWindow* sender, XEvent& event) {
	this->IMessageBox::OnButtonPress(sender, event);

	this->DrawShadow(this->mColorDarkgray, this->mColorLightgray);
}

void UIMessageBox::OnButtonRelease(IWindow* sender, XEvent& event) {
	this->IMessageBox::OnButtonRelease(sender, event);

	this->DrawShadow(this->mColorLightgray, this->mColorDarkgray);
}

void UIMessageBox::OnExpose(IWindow* sender, XEvent& event) {
	this->IMessageBox::OnExpose(sender, event);

	this->DrawText();
	this->DrawShadow(this->mColorLightgray, this->mColorDarkgray);
}

void UIMessageBox::SetText(const std::string& text) {
	this->IMessageBox::SetText(text);

	this->DrawText();
}

void UIMessageBox::DrawShadow(GC& tcolor, GC& bcolor) {
/*
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
*/
}

std::vector<std::string> UIMessageBox::Split(const std::string& text) {
	int padding = 6;

	double realWidth = this->mConfig.width - 2 * padding;

	int lettersPerLine = static_cast<int>(
		std::floor(realWidth) / 6.0
	);

	int countOfLines = std::ceil(
		(double)text.length() / lettersPerLine
	);

	int textLength = text.length();
	std::vector<std::string> lines;

	for (int i = 0; i < countOfLines; i++) {
		std::string tmp(
			text.substr(
				i * lettersPerLine,
				lettersPerLine
			)
		);

		lines.push_back(tmp);
	}

	return lines;
}

void UIMessageBox::DrawText() {
	int x = 6;
	int y = this->mFont->ascent;

	// Split string without grammar rules
	auto lines = this->Split(this->mText);

	// Added height for text
	XResizeWindow(
		this->mConfig.display,
		this->mWindow,
		this->mConfig.width,
		lines.size() * (this->mFont->ascent + this->mFont->descent)
			+ this->mFont->descent
	);

	XClearWindow(this->mConfig.display, this->mWindow);

	for (int i = 0; i < lines.size(); i++) {
		XDrawImageString(
			this->mConfig.display,
			this->mWindow,
			this->mContext,
			x,
			y,
			lines.at(i).c_str(),
			lines.at(i).length()
		);

		y += (this->mFont->ascent + this->mFont->descent);
	}
}

void UIMessageBox::Event(XEvent& event) {
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


