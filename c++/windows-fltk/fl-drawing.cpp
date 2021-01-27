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

#ifndef AXIS_H
#define AXIS_H
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <vector>
#endif
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Window.H>
#include "Axis.h"

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

Point points[] = {
	{100, 200},
	{250, 200},
	{300, 300},
	{250, 400},
	{100, 400},
	{50 , 300},
};

Point gaps[] = {
	{175, 250},
	{195, 320},
	{165, 320},
};

/*
███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████ 
*/
MyWidget* wid = new MyWidget(0, 0, 640, 480);
int main(int argc, char** argv)
{
	MyWindow*	win = new MyWindow(1080, 720, "냠냠 옴뇸뇸?");
	MyWidget*	wid = new MyWidget(10, 10, win->w(), win->h());
	Axis* xa = new Axis(100, 600, 500, 25, Axis::orientation::x, "x axis");
	Axis* ya = new Axis(100, 100, 500, 32, Axis::orientation::y, "y axis");
	xa->setcolor(FL_DARK_RED);
	ya->setcolor(FL_DARK_CYAN);
	win->show(argc, argv);
	return Fl::run();
}

void MyWindow::draw()
{
	Fl_Window::draw();
	// Draw Text
	fl_font(FL_HELVETICA, 50);
	fl_draw("MyWindow!", 300, 100);
	fl_translate(100, 300);
	std::cout << "fl_height() = " << fl_height() << '\n';
}

void MyWidget::draw()
{
	// Draw something
	fl_draw_box(FL_UP_BOX, 10, 10, 100, 100, FL_BLUE);
	// draw red triangle by three points
	const static std::vector<Point> vertices{
		{300, 200},
		{350, 100},
		{400, 200}
	};
	fl_color(FL_RED);
	fl_translate(500, 0);
	fl_begin_loop();
	for (const Point& i : points) {
		fl_vertex(i.x, i.y);
	}
	fl_end_loop();
	fl_color(0);
}
