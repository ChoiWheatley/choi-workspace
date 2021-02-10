/*
    Author : ChoiWheatley
    History : 2021. 02. 10.
    This program is my custom window class derived from Fl_Window
*/
#ifndef WINDOW_H
#define WINDOW_H 1

#include "fltk.h"
#include "Point.h"
#include "std_lib_facilities.h"

#endif

namespace Graph_lib 
{

class Window : public Fl_Window {
public:
	Window(int w, int h, const string& title);
	Window(Point xy, int w, int h, const string& title);
	virtual ~Window() { }

	int x_max() const { return w; }
	int y_max() const { return h; }
	
	void resize(int ww, int hh) { w=ww, h=hh; size(ww,hh); }
	void set_label(const string& s) { label(s.c_str()); }
	
protected:
	virtual void draw() override;

private:
	int w, h;						// window size
	void init();
};// class Window

// helper functions
inline int x_max() { return Fl::w(); } // width of screen in pixels
inline int y_max() { return Fl::h(); } // height of screen in pixels


}// namespace Graph_lib

