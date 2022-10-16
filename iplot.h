#ifndef IPLOT_H
#define IPLOT_H
  
#include <vector>
#include <functional>
#include <cmath>

#include "iwindow.h"
#include "events/iexpose.h"
#include "xconfig.h"

#define EXP	0.00001

struct PlotIn {
	double	start;
	double	stop;
	double	step;

	unsigned int Count() {
		return round(fabs((stop-start)/step))+1;
	}

	double GetX(unsigned int i) {

		double x = start + step * i;

		return fabs(x) < EXP ? 0 : x;
	}
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
		virtual PlotIn GetX() const;
	protected:
		PlotFunc mPlotFunc;
		PlotIn mPlotIn;
};

#endif // IPLOT_H


