/*
 * <PPPUC++> Chapter12 A Display Model <Axis custom interface implementation>
 * Axis xa {Axis::x,			// orientation (x,y,z) 
 *			Point{20, 300},		// Points
 *			280,				// length
 *			10,					// number of notches
 *			"x axis"			// label
 * };
 * I'll make Axis derived from Fl_Widget
*/

#ifndef AXIS_H
#define AXIS_H
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <vector>
#endif

class Axis : public Fl_Widget {
public:
	enum class orientation { x, y };
	Axis( int x, int y, int length, int notches, orientation o = orientation::x, const char* label = 0);
	void setcolor(Fl_Color bg);
private:
	int length_;
	int notches_;
	Fl_Color color_ = 0;
	const int width_ = 10;
	orientation o_ = orientation::x;
	virtual void draw() override;
};
