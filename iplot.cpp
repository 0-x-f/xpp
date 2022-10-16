#include "iplot.h"
#include "events/iexpose.h"

IPlot::IPlot(XConfig& plot) : IWindow(plot) {
	XSelectInput(
		this->mConfig.display, this->mWindow,
		ExposureMask
	);
}

void IPlot::SetFunc(PlotFunc pf) {
	this->mPlotFunc = pf;
}

void IPlot::SetX(const PlotIn& pi) {
	this->mPlotIn = pi;
}
PlotIn IPlot::GetX() const {
	return this->mPlotIn;
}

