#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

#include "../iwindow.h"
#include "../uiwindow.h"
#include "../uibuttons.h"

void foo(IWindow* sender, const XEvent& event, void* data) {
	UIButton* b = (UIButton*)sender;

	printf("Window: %d, (X, Y) = (%d, %d) | %s\n",
		b->GetWindow(), b->GetX(), b->GetY(),
		static_cast<char*>(data));
}

int main(int argc, char** argv) {

	Display* display = XOpenDisplay(NULL);

	XConfig wConfig = {
		.display = display,
		.parent = XDefaultRootWindow(display),
		.x = 0,
		.y = 0,
		.width = 800,
		.height = 600,
		.borderWidth = 0,
		.border = 0,
		.background = 0xFFFFFF,
	};
	UIWindow mainWindow(wConfig);

	XConfig bConfig = {
		.display = wConfig.display,
		.parent = mainWindow.GetWindow(),
		.x = 50,
		.y = 50,
		.width = 250,
		.height = 50,
		.borderWidth = 0,
		.border = 0,
		.background = 0xFFFAAF,
	};
	UISimpleButton button(bConfig);
	
	printf("Main window: %d\nButton: %d\n",
		mainWindow.GetWindow(), button.GetWindow());

	XCallback callback = {
		.data = (void*)("Hello, Button!"),
		.callback = foo,
	};

	XCallback callback2 = {
		.data = (void*)("Buy, Button!"),
		.callback = foo,
	};

	button.SetButtonPress(callback);	
	button.SetButtonRelease(callback2);

	mainWindow.Show();
	button.Show();

	int quit = 0;

	while (!quit) {

		XEvent event = { 0 };
		XNextEvent(wConfig.display, &event);
		
		const Window eWindow = event.xany.window;

		if (eWindow == button.GetWindow()) {
			button.Event(event);
		} else if (eWindow == mainWindow.GetWindow()) {
			mainWindow.Event(event);
		}
	}

	XCloseDisplay(wConfig.display);

	return 0;
}


