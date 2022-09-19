
#include <X11/Xlib.h>

#include "ievents.h"
#include "iwindow.h" 

// IButtonPressEvent
void IButtonPressEvent::SetButtonPress(XCallback& callback) {
	this->mButtonPressEvent = callback;
}  

void IButtonPressEvent::OnButtonPress(IWindow* sender, XEvent& event) {
	if (this->mButtonPressEvent.callback) {
		this->mButtonPressEvent.callback(
			sender,
			event,
			this->mButtonPressEvent.data
		);	 
	}
}   

// IButtonReleaseEvent
void IButtonReleaseEvent::SetButtonRelease(XCallback& callback) {
	this->mButtonReleaseEvent = callback;
}  
  
 void IButtonReleaseEvent::OnButtonRelease(IWindow* sender, XEvent& event) {
	if (this->mButtonReleaseEvent.callback) {
		this->mButtonReleaseEvent.callback(
			sender,
			event,
			this->mButtonReleaseEvent.data
		);	 
	}		
}  
   
// IKeyPressEvent
void IKeyPressEvent::SetKeyPress(XCallback& callback) {
	this->mKeyPressEvent = callback;
}  
  
 void IKeyPressEvent::OnKeyPress(IWindow* sender, XEvent& event) {
	if (this->mKeyPressEvent.callback) {
		this->mKeyPressEvent.callback(
			sender,
			event,
			this->mKeyPressEvent.data
		);	 
	}		
}  

// IExposeEvent
void IExposeEvent::SetExpose(XCallback& callback) {
	this->mExposeEvent = callback;
}  
  
 void IExposeEvent::OnExpose(IWindow* sender, XEvent& event) {
	if (this->mExposeEvent.callback) {
		this->mExposeEvent.callback(
			sender,
			event,
			this->mExposeEvent.data
		);	 
	}		
}  
   
