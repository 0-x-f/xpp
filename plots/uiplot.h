#ifndef PLOT_H
#define PLOT_H

#include <X11/Xlib.h> 

#include <vector>
#include <functional>

#include "../iplot.h"
#include "../xconfig.h"

class UIPlot :
	public IPlot {

	public:
		UIPlot(XConfig& plot);
	public:
		virtual void DrawPlot() override;
	private:
		void Calc();
	protected:
		std::vector<double> mValues;
	protected:
		double mMaxY;
		double mMinY;
	protected:
		unsigned mUnitSeg;
	protected:
		GC mContext;
};

#endif // PLOT_H

