#include <string>
#include <vector>
#include <functional>

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

IWindow::~IWindow() {
	//XDestroyWindow(this->mConfig.display, this->mWindow);
	for(unsigned int i = 0; i < this->mChildItems.size(); i++) {
		delete this->mChildItems[i];
	}
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

void IWindow::AddChild(IWindow* child) {

	const Window cWindow = child->GetWindow();

	for(unsigned int i = 0; i < this->mChildItems.size(); i++) {
		if(this->mChildItems[i]->GetWindow() == cWindow) {
			return;
		}
	}

	this->mChildItems.push_back(child);
}

void IWindow::RemoveChild(const std::string& className) {

	auto newEnd = std::remove_if(
			this->mChildItems.begin(), 
			this->mChildItems.end(), 
			[&className](IWindow* item) {
				return item->ClassList.Contains(className);
			}
	);

	this->mChildItems.erase(newEnd, this->mChildItems.end());
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

void IWindow::Clear() {
	XClearWindow(this->mConfig.display, this->mWindow);
}

void UIClassList::Add(const std::string& className) {
	if (!this->Contains(className)) 
		this->mClassList.push_back(className);
}

void UIClassList::Remove(const std::string& className) {

	auto newEnd = std::remove_if(
			this->mClassList.begin(), 
			this->mClassList.end(), 
			[&className](const std::string& item) {
				return item == className;
			}
	);

	this->mClassList.erase(newEnd, this->mClassList.end());
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
