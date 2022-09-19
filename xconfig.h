#ifndef XCONFIG_UI_H
#define XCONFIG_UI_H

#include <X11/Xlib.h>

struct XConfig {
	Display*		display;
	Window			parent;
	int				x;
	int				y;
	unsigned int	width;
	unsigned int	height;
	unsigned int	borderWidth;
	unsigned long	border;
	unsigned long	background;
};

#endif // XCONFIG_UI_H
