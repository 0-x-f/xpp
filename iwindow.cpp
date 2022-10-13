#include <string>
#include <vector>

#include "iwindow.h"

IWindow::IWindow(XConfig& window) {
	this->mConfig = window;
	this->mWindow = XCreateSimpleWindow(
		this->mConfig.display,
		this->mConfig.parent,
		this->mConfig.x,
		this->mConfig.y,
		this->mConfig.width,
		this->mConfig.height,
		this->mConfig.borderWidth,
		this->mConfig.border,
		this->mConfig.background
	);
}

Window IWindow::GetWindow() const {
	return this->mWindow;
}

XConfig IWindow::GetConfig() const {
	return this->mConfig;
}

int IWindow::GetX() const {
	return this->mConfig.x;
}

int IWindow::GetY() const {
	return this->mConfig.y;
}

unsigned int IWindow::GetWidth() const {
	return this->mConfig.width;
}

unsigned int IWindow::GetHeight() const {
	return this->mConfig.height;
}

void IWindow::Show() {
	XMapWindow(this->mConfig.display, this->mWindow);
}

void IWindow::Hide() {
	XUnmapWindow(this->mConfig.display, this->mWindow);
}

bool IWindow::IsOwner(XEvent& event) const {
	return event.xany.window == this->GetWindow();
}

void IWindow::AddChild(IWindow& child) {
	this->mChildItems.push_back(&child);
}

void IWindow::RemoveChild(const std::string& className) {

	unsigned int iSize = this->mChildItems.size();

	for(unsigned int i = 0; i < iSize; i++) {

		if (this->mChildItems[i]->ClassList.Contains(className) != true) 
			continue;

		// if it is not the last item
		if (i != iSize-1) 
			this->mChildItems[i] = this->mChildItems[iSize];

		this->mChildItems.pop_back();
		iSize--;
	}
}

IWindow* IWindow::FindChild(const std::string& className) const {

	for(unsigned int i = 0; i < this->mChildItems.size(); i++) {
		if (this->mChildItems[i]->ClassList.Contains(className)) 
			return this->mChildItems[i];
	}

	return nullptr;
}

std::vector<IWindow*> IWindow::FindChildAll(
	const std::string& className
) const {

	std::vector<IWindow*> items;

	for(unsigned int i = 0; i < this->mChildItems.size(); i++) {
		if (this->mChildItems[i]->ClassList.Contains(className)) 
			items.push_back(this->mChildItems[i]);
	}

	return items;
}

void UIClassList::Add(const std::string& className) {
	if (!(this->Contains(className))) 
		this->mClassList.push_back(className);
}

void UIClassList::Remove(const std::string& className) {

	unsigned int iSize = this->mClassList.size();

	for(unsigned int i = 0; i < iSize; i++) {

		if (this->mClassList[i] != className) 
			continue;

		// if it is not the last item
		if (i != iSize-1) 
			this->mClassList[i] = this->mClassList[iSize];

		this->mClassList.pop_back();

		return;
	}
}

bool UIClassList::Contains(const std::string& className) const {

	for(unsigned int i = 0; i < this->mClassList.size(); i++) {
		if (this->mClassList[i] == className) 
			return true;
	}

	return false;
}

void UIClassList::Toggle(const std::string& className) {

	unsigned int size = this->mClassList.size();

	this->Remove(className);

	// if the size has not changed -> removal has not occurred -> 
	// item was not -> need to be added
	if (size == this->mClassList.size()) 
		this->mClassList.push_back(className);
}

