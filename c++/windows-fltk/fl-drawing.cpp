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
 * 2021. 02. 03
 *  -- <PPPUC++> Chapter 6 Exercises{1, 2, 4}
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
// void Fl_Window::size_range(int minw, int minh, int maxw=0, int maxh=0, int dw=0, int dh=0, int aspect=0)
	MyWindow  *	win 		= new MyWindow(1080, 720, "나의 창문");
	Rectangle tic_tac_toe[9]{
		{10, 10, 10, 10, 0, 0, FL_WHITE},
		{21, 10, 10, 10, 0, 0, FL_RED},
		{32, 10, 10, 10, 0, 0, FL_WHITE},
		{10, 21, 10, 10, 0, 0, FL_RED},
		{21, 21, 10, 10, 0, 0, FL_WHITE},
		{32, 21, 10, 10, 0, 0, FL_RED},
		{10, 32, 10, 10, 0, 0, FL_WHITE},
		{21, 32, 10, 10, 0, 0, FL_RED},
		{32, 32, 10, 10, 0, 0, FL_WHITE}
	};
	for (int i = 0; i < 9; i++)
		win->add(tic_tac_toe[i]);


	win->size_range(250, 100, 0, 0);
	win->show();
	return Fl::run();
}

void MyWindow::draw()
{
	Fl_Window::draw();
}

void MyWidget::draw()
{
}

