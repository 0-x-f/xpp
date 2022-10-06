
#ifndef IPLOT_H
#define IPLOT_H
  
#include <vector>
#include <functional>

#include "iwindow.h"
#include "events/iexpose.h"
#include "xconfig.h"

struct PlotIn {
	double	start;
	double	stop;
	double	step;
};

using PlotFunc = std::function<double(const double x)>;

class IPlot :
	public IWindow,
	public IExposeEvent {

	public:
		IPlot(XConfig& plot);
	public:
		virtual void DrawPlot() = 0;
	public:
		virtual void SetFunc(PlotFunc pf);
		virtual void SetX(const PlotIn& pi);
	public:
		virtual void OnExpose(IWindow* sender, XEvent& event) override;
	public:
		virtual void Event(XEvent& event) override;
	protected:
		PlotFunc mPlotFunc;
		PlotIn mPlotIn;
};

#endif // IPLOT_H

