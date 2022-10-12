#ifndef IBUTTON_H
#define IBUTTON_H

#include <string>

#include "iwindow.h"
#include "events/ibuttonpress.h"
#include "events/ibuttonrelease.h"
#include "events/iexpose.h"
#include "xconfig.h"

class IButton :
	public IWindow,
	public IButtonPressEvent,
	public IButtonReleaseEvent,
	public IExposeEvent {

	public:
		IButton(XConfig& button);
	public:
		virtual void SetText(const std::string& text);
	protected:
		std::string mText;
};

#endif // IBUTTON_H


