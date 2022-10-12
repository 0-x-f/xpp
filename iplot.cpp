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

void IPlot::OnExpose(IWindow* sender, XEvent& event) {
	this->IExposeEvent::OnExpose(sender, event); 

	this->DrawPlot(); 
}

void IPlot::Event(XEvent& event) {
	switch (event.type) {
		case Expose: {
			this->OnExpose(this, event);
		} break;
	}
}


