#ifndef PLOT_H
#define PLOT_H

#include <X11/Xlib.h> 

#include <vector>
#include <functional>

#include "../iplot.h"
#include "../xconfig.h"
#include "../labels/uilabel.h"

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
		virtual void Event(XEvent& event) override;
	public:
		virtual void OnExpose(IWindow* sender, XEvent& event) override;
	public:
		virtual void Clear() override;
	public:
		virtual void DrawPlot() override;
	private:
		void DrawCoordinateAxes();
		void DrawFunction();
		void DrawGrid();
		void DrawGridLines(
			unsigned short direction,
			unsigned int length,
			unsigned int distance,
			unsigned int origin,
			unsigned int indent
		); 
		void DrawLabel(const UIPoint& a, const std::string& text);
	private:
		void DrawLine(const UIPoint& a, const UIPoint& b, const GC& gc);
	private:
		void CalculateFunction();
		void CalculateGeometry();
		inline double CalculateUnitSegment(
			double a, 
			double b, 
			unsigned int length
		);
	private:
		unsigned int mMinGridIndentation;
		unsigned int mMaxGridIndentation;
	private:
		std::vector<double> mValues;
	private:
		double mMaxY;
		double mMinY;
	private:
		UIPoint mCenter;
	private:
		double mUnitSeg;
	private:
		GC mCoordinateAxesGC;
		GC mFunctionColorGC; 
		GC mGridGC;
	private:
		unsigned short int padding;
};

#endif // PLOT_H
