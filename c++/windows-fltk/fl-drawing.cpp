/*
 * <FLTK> Drawing Things in FLTK
 *
 * < Author > ChoiWheatley
 * < Doc Link > https://www.fltk.org/doc-1.3/drawing.html
 *
 * < ToDo >
 * <> Mac Visual Studio 설치하여 해당 리포지토리 끌어와서 fltk 빌드 가능한지 확인하기
 *
 *
 * < History >
 * 2021. 02. 05
 *	-- Chapter126 Exercise {6, 7, 8, 9, 10???!!!, 11, 12}
 * 2021. 02. 03
 *  -- <PPPUC++> Chapter12  Exercises{1, 2, 4, 5}
 * 2021. 01. 30.
 *  -- Drawing Images & Circle & Ellipse & Resizable & Mask  
 * 2021. 01. 28.
 *  -- Rectangle & Text 
 * 2021. 01. 27.
 *  -- Axis, Graphing function
 * 2021. 01. 26.
 *  -- PPPUC++ 본격 진도빼기 without custom header
 * 2021. 01. 21.
 *	-- 윈도우에서 fltk 재도전 하기. Visual Studio에서 제대로 돌아간다.
 *	-- 목표 : [ Drawing Fast Shapes ] & [ Drawing Complex Shapes ] & [ Drawing Text ] & [ Fonts ]
 * 
 * < Compile Options via Visual Studio >
 * reference from : https://alf-p-steinbach.github.io/Install-FLTK-for-use-with-Visual-C-/
 * 
 */

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_BMP_Image.H>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include "Axis.h"
#include "Function.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
// import images
#include "choe.xpm"

class MyWindow : public Fl_Window {
public:
	MyWindow(int w, int h, const char* label = 0) : Fl_Window{ w, h, label } {}
	~MyWindow() {}
	virtual void draw();
private:
};

class MyWidget : public Fl_Widget {
public:
	MyWidget(int x, int y, int w, int h, const char* label = 0) : Fl_Widget(x, y, w, h, label) {}
	~MyWidget() {}
private:
	virtual void draw() override;
};

struct Point {
	double x;
	double y;
};


/*
███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████ 
*/
int main(int argc, char** argv)
{
	MyWindow  *	win 		= new MyWindow(1000, 1000, "Ch12 Exercise7: Draw a 2-D House");

	win->size_range(250, 100, 0, 0);
	win->show();
	return Fl::run();
}

using namespace std;
vector<Point> roof{
	{450, 0},
	{300, 200},
	{600, 200},
	{450, 0}
};
vector<Point> door_dividing{
	{450, 400-115+5},
	{450, 400-5}
};
vector<Point> land{
	{50, 400},
	{950, 400}
};
vector<Point> burrow{
	{300, 400},
	{200, 600},
	{300, 600},
	{230, 900},
	{400, 900},
	{450, 800},
	{650, 900},
	{750, 900},
	{600, 600},
	{750, 400},
	{300, 400}
};
Rectangle goggle{300,245,300,50};
Rectangle door{450-23,400-115, 45, 115};
Circle door_handle1{450-12, 350, 5};
Circle door_handle2{450+12, 350, 5};
Rectangle ladder_bound{310, 400, 50, 500};
Rectangle trunk{700, 200, 30, 200};
Circle tree_leaves1{700,230,25};
Circle tree_leaves2{725,210,40};
Circle tree_leaves3{720,200,30};
Circle tree_leaves4{715,195,10};

void MyWindow::draw()
{
	Fl_Window::draw();
// roof
	fl_color(0x45737300);
	fl_begin_polygon();
	for (auto i : roof)
		fl_vertex(i.x, i.y);
	fl_end_polygon();
	fl_color(0);
// building
	Rectangle building{300,200,300,200};
	building.fill_color(0x5a686800);
	building.line_style(0x10252600, 0, 3);
	this->add(building);
}

void MyWidget::draw()
{
}

