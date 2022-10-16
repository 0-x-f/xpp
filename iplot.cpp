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

void IPlot::SetPlotIn(const PlotIn& pi) {
	this->mPlotIn = pi;
}
PlotIn IPlot::GetPlotIn() const {
	return this->mPlotIn;
}

