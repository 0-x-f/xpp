#include <X11/Xlib.h>

#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

#include "uiplot.h"
#include "../xconfig.h"

UIPlot::UIPlot(XConfig& plot) : IPlot(plot) {

	this->mMaxY = std::numeric_limits<double>::quiet_NaN();
	this->mMinY = std::numeric_limits<double>::quiet_NaN();

	Display* dpy = this->mConfig.display;
	Window win = this->mWindow;
	XGCValues gcv;

	// GC for coordinate axes
	gcv.foreground = 0x000000;
	this->mCoordinateAxesGC = XCreateGC(dpy, win, GCForeground, &gcv);

	// GC for function
	gcv.foreground = 0xD91212;
	this->mFunctionColorGC = XCreateGC(dpy, win, GCForeground, &gcv);
 
	// GC for grid
	gcv.foreground = 0x1ED3C0;
	this->mGridGC = XCreateGC(dpy, win, GCForeground, &gcv);

	this->padding = 10;

	this->mMinGridIndentation = 25;
	this->mMaxGridIndentation = 150;
}

void UIPlot::CalculateFunction() {

	unsigned int xCount = this->mPlotIn.Count();

	this->mValues = std::vector<double>(xCount, 0);

	for(int i = 0; i < xCount; i++) {

		// calculate the value
		this->mValues[i] = this->mPlotFunc(
				this->mPlotIn.GetX(i)
		);

		// serch max value
		if (std::isnan(this->mMaxY) 
			|| (this->mMaxY < this->mValues[i] 
				&& !std::isinf(this->mValues[i]))) 
			this->mMaxY = this->mValues[i];

		// serch min value
		if (std::isnan(this->mMinY) || this->mMinY > this->mValues[i]) 
			this->mMinY = this->mValues[i];
	};
}

inline double UIPlot::CalculateUnitSegment(
	double a, 
	double b, 
	unsigned int length
) {

	if ((a < 0) ^ (b < 0)) {
		return 1.0 * (length - this->padding*2) / (fabs(a) + fabs(b));
	} else {
		return 1.0 * (length - this->padding*2) / std::max(fabs(a), fabs(b));
	}
}

void UIPlot::CalculateGeometry() {

	// calculate unit segment
	double unitSegY = this->CalculateUnitSegment(
		this->mMaxY, 
		this->mMinY, 
		this->mConfig.height
	);

	double unitSegX = this->CalculateUnitSegment(
		this->mPlotIn.start, 
		this->mPlotIn.stop, 
		this->mConfig.width
	);

	this->mUnitSeg = std::min(unitSegY, unitSegX);

	// calculate coordinates center
	this->mCenter.y = this->mMaxY <= 0 ? 0 : round(unitSegY * this->mMaxY);

	double minX = std::min(this->mPlotIn.start, this->mPlotIn.stop);
	this->mCenter.x = minX >= 0 ? 0 : round(unitSegX * fabs(minX)); 

	// add padding to plot
	this->mCenter.y += this->padding;
	this->mCenter.x += this->padding;
}

void UIPlot::DrawLine(const UIPoint& a, const UIPoint& b, const GC& gc) {
	XDrawLine(
		this->mConfig.display,
		this->mWindow,
		gc,
		a.x, a.y,
		b.x, b.y
	);
}

void UIPlot::DrawCoordinateAxes() {

	// draw OX
	UIPoint a = UIPoint(0, this->mCenter.y);
	UIPoint b = UIPoint(this->mConfig.width, this->mCenter.y); 
    
	this->DrawLine(a, b, this->mCoordinateAxesGC);    
    
	// draw OY    
	a = UIPoint(this->mCenter.x, 0);
	b = UIPoint(this->mCenter.x, this->mConfig.height);

	this->DrawLine(a, b, this->mCoordinateAxesGC);
}

void UIPlot::DrawGrid() {

	UIPoint a, b;

	unsigned int width = this->mConfig.width;
	unsigned int height = this->mConfig.height;

	unsigned int indent = this->mUnitSeg;

	// indent adjustment
	if (indent < this->mMinGridIndentation) {
		while (indent < this->mMinGridIndentation) {
			indent += this->mUnitSeg;
		}
	} else if (indent > this->mMaxGridIndentation) {
		for(int i = 2; indent > this->mMaxGridIndentation; i++) {
			indent /= i;
		}
	}

	// vertical lines
	a.y = 0; b.y = height;

	for (int i = this->mCenter.x % indent; i <= width; i+=indent) {

		if (i == this->mCenter.x)
			continue;

		a.x = b.x = i;
		DrawLine(a, b, this->mGridGC);
	}

	// horizontal lines
	a.x = 0; b.x = width;

	for (int i = this->mCenter.y % indent; i <= height; i+=indent) {

		if (i == this->mCenter.y)
			continue;

		a.y = b.y = i;
		DrawLine(a, b, this->mGridGC);
	}
}

void UIPlot::DrawFunction() {

	UIPoint pPoint;
	bool pPointIsNan = true;

	unsigned int vCount = this->mValues.size();

	for (int i = 0; i < vCount; i++) {

		if (std::isnan(this->mValues[i]) || std::isinf(this->mValues[i])) {
			pPointIsNan = true;
			continue;
		}

		UIPoint cPoint = UIPoint(
			this->mCenter.x + this->mPlotIn.GetX(i) * this->mUnitSeg, 
			this->mCenter.y - (this->mValues[i] * this->mUnitSeg)
		);

		if (pPointIsNan) {
			pPointIsNan = false;
		} else {
			this->DrawLine(pPoint, cPoint, this->mFunctionColorGC);
		}

		pPoint = cPoint;
	}
}

void UIPlot::DrawPlot() {

	if (this->mPlotFunc == nullptr)
		return;

	// calculation of function values in mPlotIn
	this->CalculateFunction(); 

	// caclulation plot geometry (unit segment, coordinates center)
	this->CalculateGeometry();

	// draw grid
	this->DrawGrid();

	// draw coordinate axes (OX, OY)
	this->DrawCoordinateAxes();

	// draw function
	this->DrawFunction();
}

void UIPlot::OnExpose(IWindow* sender, XEvent& event) {
	this->IExposeEvent::OnExpose(sender, event); 

	this->DrawPlot(); 
}

void UIPlot::Event(XEvent& event) {
	if (this->IWindow::IsOwner(event)) {
		switch (event.type) {
			case Expose: {
				this->OnExpose(this, event);
			} break;
		}
	}
}


