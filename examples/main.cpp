#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

#include "../iwindow.h"
#include "../windows/uiwindow.h"
#include "../buttons/uibutton.h"

void foo(IWindow* sender, const XEvent& event, void* data) {
	UIButton* b = (UIButton*)sender;

	switch (event.type) {
		case ButtonPress: {
			switch (event.xbutton.button) {
				case Button1: {
					printf("Left mouse button press ");
				} break;
				case Button3: {
					printf("Right mouse button press ");
				} break;
				default: {
					printf("Other mouse button press ");
				} break;
			}
		} break;
		case ButtonRelease: {
			switch (event.xbutton.button) {
				case Button1: {
					printf("Left mouse button release ");
				} break;
				case Button3: {
					printf("Right mouse button release ");
				} break;
				default: {
					printf("Other mouse button release ");
				} break;
			}
		} break;
		case KeyPress: {
			printf("Key '%d' press ", event.xkey.keycode);
		} break;
	}

	printf("| Message: %s\n", static_cast<char*>(data));
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
	UIButton button(bConfig);
	button.SetText("Open fridge");

	XCallback callback1 = {
		.data = (void*)("Hello, Key!"),
		.callback = foo,
	};

	XCallback callback2 = {
		.data = (void*)("Hello, Button!"),
		.callback = foo,
	};

	XCallback callback3 = {
		.data = (void*)("Buy, Button!"),
		.callback = foo,
	};

	mainWindow.SetKeyPress(callback1);
	button.SetButtonPress(callback2);
	button.SetButtonRelease(callback3);

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


