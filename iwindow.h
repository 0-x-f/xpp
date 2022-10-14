#ifndef IWINDOW_H
#define IWINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <vector>
#include <string>

#include "ievent.h"
#include "xconfig.h"

class UIClassList {
	private:
		std::vector<std::string> mClassList;
	public:
		void Add(const std::string& className);
		void Remove(const std::string& className);
		bool Contains(const std::string& className) const;
		void Toggle(const std::string& className);
}; 

class IWindow : public IEvent {
	public:
		IWindow(XConfig& window);
	public:
		virtual void Show();
		virtual void Hide();
	public:
		virtual Window GetWindow() const;
		virtual XConfig GetConfig() const;
	public:
		virtual int GetX() const;
		virtual int GetY() const;
		virtual unsigned int GetWidth() const;
		virtual unsigned int GetHeight() const;
	public:
		virtual bool IsOwner(XEvent& event) const;
	public:
		virtual void AddChild(IWindow& child);
		virtual void RemoveChild(const std::string& className);
	public:
		virtual IWindow* FindChild(const std::string& className) const;
		virtual std::vector<IWindow*> FindChildAll(
			const std::string& className
		) const;
	public:
		UIClassList ClassList;
	protected:
		std::vector<IWindow*> mChildItems;
	protected:
		Window mWindow;
		XConfig mConfig;
};

#endif // IWINDOW_H


