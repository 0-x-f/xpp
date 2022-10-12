#ifndef ITEXT_BUTTON_H
#define ITEXT_BUTTON_H

#include <string>

#include "iwindow.h"
#include "events/iexpose.h"
#include "events/ikeypress.h"
#include "xconfig.h"

class ITextBox :
	public IWindow,
	public IExposeEvent,
	public IKeyPressEvent {

	public:
		ITextBox(XConfig& button);
	public:
		virtual void SetContent(const std::string& content);
		virtual std::string GetContent() const;
	public:
		virtual void Event(XEvent& event) override;
	protected:
		std::string mContent;
};

#endif // ITEXT_BUTTON_H


