#ifndef PLOT_H
#define PLOT_H

#include <X11/Xlib.h> 

#include <vector>
#include <functional>

#include "../iplot.h"
#include "../xconfig.h"

struct UIPoint {
	unsigned int x;
	unsigned int y;

	UIPoint() {
		x = 0;
		y = 0;
	}

	UIPoint(unsigned int xp, unsigned int yp) {
		x = xp;
		y = yp;
	}
};

class UIPlot :
	public IPlot {

	public:
		UIPlot(XConfig& plot);
	public:
		virtual void DrawPlot() override;
	private:
		void CalculateFunction();
		void CalculateGeometry();
		inline double CalculateUnitSegment(
			double a, 
			double b, 
			unsigned int length
		);
	private:
		void DrawLine(const UIPoint& a, const UIPoint& b);
	private:
		unsigned short int padding;
	protected:
		std::vector<double> mValues;
	protected:
		double mMaxY;
		double mMinY;
	protected:
		UIPoint mCenter;
	protected:
		unsigned mUnitSeg;
	protected:
		GC mContext;
};

#endif // PLOT_H

