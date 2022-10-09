#include <X11/Xlib.h>

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include<algorithm>
#include "plot.h"
#include "../xconfig.h"

UIPlot::UIPlot(XConfig& plot) : IPlot(plot) {

	this->mMaxY = std::numeric_limits<double>::quiet_NaN();
	this->mMinY = std::numeric_limits<double>::quiet_NaN();
	
	Display* display = this->mConfig.display;

	XGCValues gcv;
	gcv.background = 0xFFFFFF;
	gcv.foreground = 0x000000;

	this->mContext = XCreateGC(
		display,
		this->mWindow,
		GCForeground | GCBackground,
		&gcv
	);
}

void UIPlot::Calc() {

	this->mValues = std::vector<double>(this->mPlotIn.Count(), 0);

	for(int i = 0; i<this->mPlotIn.Count(); i++) {
		
		// calculate the value
		this->mValues[i] = this->mPlotFunc(
			this->mPlotIn.start + this->mPlotIn.step * i
		);
		
		// serch max value
		if (std::isnan(this->mMaxY) || this->mMaxY < this->mValues[i]) 
			this->mMaxY = this->mValues[i];

		// serch min value
		if (std::isnan(this->mMinY) || this->mMinY > this->mValues[i]) 
			this->mMinY = this->mValues[i];
	};
}


