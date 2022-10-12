#ifndef ILABEL_H
#define ILABEL_H

#include <string>

#include "iwindow.h"
#include "events/iexpose.h"
#include "xconfig.h"

class ILabel :
	public IWindow,
	public IExposeEvent {

	public:
		ILabel(XConfig& button);
	public:
		virtual void SetText(const std::string& text);
	protected:
		std::string mText;
};

#endif // ILABEL_H


