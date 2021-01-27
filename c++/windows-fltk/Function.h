/*
 * <PPPUC++> 12.7.4 Graphing a function
 * Function sine {
 *		sin,		// Function Pointer sin()
 *		0,			// Range [0,100)
 *		100,		// Range [0,100)
 *		20,			// draw from (0,0) to (20,150)
 *		150,		// draw from (0,0) to (20,150)
 *		1000,		// 1000 points to draw
 *		50,			// scale x values * 50
 *		50			// scale y values * 50
 * }
 * 
 */

#ifndef FUNCTION_H
#define FUNCTION_H
#include <cmath>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#endif
#include <iomanip>
#include <string>

class Function : public Fl_Widget {
public:
	Function(double (*funcptr)(double x),
		int range_min, int range_max, 
		int pnt_x, int pnt_y,
		int accuracy,
		int scale_x,
		int scale_y);
	~Function() { free(funcptr_); }
	// setter
	void setcolor(Fl_Color bg) { color_ = bg; redraw(); }
	void setlinestyle(int style, int line_width = 0) { line_style_ = style; line_width_ = line_width; }
	// getter
	Fl_Color color() const { return color_; }
	int line_style() const { return line_style_; }

private:
	// memeber
	double(*funcptr_)(double);
	int range_min_;
	int range_max_;
	int pnt_x_;
	int pnt_y_;
	int accuracy_;
	int scale_x_;
	int scale_y_;
	// cosmetic
	Fl_Color color_ = 0;
	int line_style_ = 0;
	int line_width_  = 0;
	// methods
	virtual void draw() override;
};

// helper functions
inline int offset(double origin, int move, int scale) {
	return (int)((origin * scale) + move);
}
