#include "uitextbox.h"

UITextBox::UITextBox(XConfig& config, ETextBoxType type)
	: ITextBox(config, type) {
	// Screen color contains RGB values provided by the hardware
	// Exact color contains exact RGB values

	XColor		screenLightGrayColor, exactLightGrayColor;
	XColor		screenDarkGrayColor, exactDarkGrayColor;
	XGCValues	lightGrayValues;
	XGCValues	darkGrayValues;

	XColor		screenTextColor, exactTextColor;
	XGCValues	textColorValues;

	// Allocations for text box shadow

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

void UITextBox::OnKeyPress(IWindow* sender, XEvent& event) {
	this->ITextBox::OnKeyPress(sender, event);

	char buffer[8];

	int count = XLookupString(
		&event.xkey,
		buffer,
		sizeof(buffer),
		NULL,
		NULL
	);

	switch (count) {
		case 0: break;
		case 1: {
			char c = buffer[0];

			switch (c) {
				case 8: {
					if (0 != this->mContent.size()) {
						this->mContent.pop_back();
					}
				} break;
				default: {
					switch (this->mType) {
						case ETextBoxType::Text:
						case ETextBoxType::Password: {
							this->mContent.push_back(c);
						} break;
						case ETextBoxType::Number: {
							if ((c >= '0' && c <= '9')
								|| (c == '.')
								|| (c == ',')) {

								this->mContent.push_back(c);
							}
						} break;
					}
				} break;
			}
		} break;
	}

	this->DrawContent();
	this->DrawShadow(this->mColorDarkgray, this->mColorLightgray);
}

void UITextBox::OnExpose(IWindow* sender, XEvent& event) {
	this->ITextBox::OnExpose(sender, event);

	this->DrawContent();
	this->DrawShadow(this->mColorDarkgray, this->mColorLightgray);
}

void UITextBox::SetContent(const std::string& content) {
	this->ITextBox::SetContent(content);

	this->DrawContent();
}

void UITextBox::DrawContent() {
	int x = 8;
	int yCenter = (
		this->mConfig.height
		- (this->mFont->ascent + this->mFont->descent)) / 2
		+ this->mFont->ascent;

	XClearWindow(this->mConfig.display, this->mWindow);

	std::string tmp;

	if (ETextBoxType::Password == this->mType) {
		tmp = std::string(this->mContent.length(), '*');
	} else {
		tmp = std::string(this->mContent);
	}

	XDrawImageString(
		this->mConfig.display,
		this->mWindow,
		this->mContext,
		x,
		yCenter,
		tmp.c_str(),
		tmp.length()
	);
}

void UITextBox::DrawShadow(GC& tcolor, GC& bcolor) {
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


