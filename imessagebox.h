#ifndef IMESSAGEBOX_H
#define IMESSAGEBOX_H

#include <string>

#include "iwindow.h"
#include "events/ibuttonpress.h"
#include "events/ibuttonrelease.h"
#include "events/iexpose.h"
#include "xconfig.h"

enum EMessageBoxType {
	OK = 0,
	YesNo
};

class IMessageBox :
	public IWindow,
	public IButtonPressEvent,
	public IButtonReleaseEvent,
	public IExposeEvent {

	public:
		IMessageBox(XConfig& config, EMessageBoxType type);
	public:
		virtual void SetText(const std::string& text);
	protected:
		std::string mText;
	protected:
		EMessageBoxType mType;
};

#endif // IMESSAGEBOX_H


