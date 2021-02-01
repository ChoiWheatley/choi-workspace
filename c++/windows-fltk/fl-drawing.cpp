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
int main(int argc, char** argv)
{
	MyWindow*	win 		= new MyWindow(1080, 720, "나의 창문");
    /*
	MyWidget*	wid 		= new MyWidget(10, 10, 100, 100);
	Axis* xa 				= new Axis(100, 600, 500, 25, Axis::orientation::x, "x axis");
	Axis* xb 				= new Axis(100, 650, 500, 60, Axis::orientation::x, "X axis2");
	Axis* ya 				= new Axis(100, 100, 500, 32, Axis::orientation::y, "y axis");
	Function* sine			= new Function(sin,		0, 100, 20, 300, 1000, 50, 100);
	Function* cosine		= new Function(cos,		0, 100, 20, 300, 1000, 50, 100);
	Function* logarithm		= new Function(log10,	0, 100, 20, 450, 1000, 50, 100);
	Rectangle* rec1 		= new Rectangle(10, 10, 100, 100);
    Rectangle* rec2         = new Rectangle(10, 120, 100, 100);
    */
    Circle*    cir1         = new Circle(300, 300, 100, "x");
	Ellipse*   ell1			= new Ellipse(500, 300, 75, 150, "hello");

    cir1->fill_color(FL_RED);
    cir1->line_color(FL_GREEN);
    cir1->line_style(FL_DASH, 4);
	
	ell1->fill_color(FL_CYAN);
	ell1->line_color(FL_RED);
	ell1->line_style(FL_SOLID, 5);



// DRAW IMAGE!!!!!!!
    auto myimage = new Fl_JPEG_Image("../images/IMG_2342.jpg");
    auto mypicbox = new Fl_Box(12, 12, 100, 100);
    myimage->scale(95, 95, 0, 0);
    mypicbox->image(myimage);
    mypicbox->redraw();
// draw bitmap
    auto mybmp = new Fl_BMP_Image("../images/IMG_2342.bmp");
	if(mybmp->fail()) std::cerr << "something went wrong opening bmp file!!\n";
    mybmp->scale(100, 100);
    Fl::visual(FL_RGB);

/*
	cosine->setcolor(FL_DARK_MAGENTA);
	cosine->setlinestyle(FL_SOLID, 4);
	sine->setcolor(FL_DARK_GREEN);
	sine->setlinestyle(FL_DASHDOT, 3);
	xa->setcolor(FL_DARK_RED);
	ya->setcolor(FL_DARK_CYAN);
    rec1->line_style(FL_RED, FL_DOT, 3);
    rec1->fill_color(FL_BLUE);
    rec2->fill_color(FL_DARK_MAGENTA);
*/

// void Fl_Window::size_range(int minw, int minh, int maxw=0, int maxh=0, int dw=0, int dh=0, int aspect=0)
	win->size_range(250, 100, 1920, 1080);
	win->show();
	return Fl::run();
}

void MyWindow::draw()
{
	Fl_Window::draw();
	// Draw Text
	fl_color(0);
	fl_font(FL_HELVETICA, 50);
	fl_draw("MyWindow!", 300, 100);
    fl_font(FL_HELVETICA, 0);
}

void MyWidget::draw()
{
	// draw red triangle by three points
	const static std::vector<Point> vertices{
		{300, 200},
		{350, 100},
		{400, 200}
	};
	fl_color(FL_RED);
    fl_line_style(FL_DOT , 5);
	fl_begin_loop();
	for (const Point& i : vertices) {
		fl_vertex(i.x, i.y);
	}
	fl_end_loop();
// draw xpm 
	if(!fl_draw_pixmap(choe, 500, 300, FL_WHITE)) std::cerr << "something is wrong drawing an image!!\n";
// draw jpg
	Fl_JPEG_Image img1{"../images/IMG_2269.JPG"};
	if (img1.fail()) std::cerr << "somthing is wrong opening jpeg file!!\n";
    img1.scale(300, 300, 0);
	img1.draw(700, 0);
// draw one more
    Fl_JPEG_Image img2{"../images/IMG_2344.jpg"};
    if (img2.fail()) std::cerr << "img2 failed!\n";
    img2.scale(300, 300);
    img2.draw(700, 310);
// draw multiple images
    int startX = 10, startY = 300;
    std::vector<Fl_JPEG_Image*> images{
        new Fl_JPEG_Image("../images/IMG_2357.jpg"),
        new Fl_JPEG_Image("../images/IMG_2359.jpg"),
        new Fl_JPEG_Image("../images/IMG_2361.jpg"),
        new Fl_JPEG_Image("../images/IMG_2376.jpg")
    };
    for (Fl_JPEG_Image* i : images) if (i->fail()) std::cerr << "opening file error! \n"; 
    for (Fl_JPEG_Image* i : images) i->scale(300, 300, 0);
    for (int i = 0; i < images.size(); i++) {
        images[i]->draw(startX + 300 * i + 10, startY);
    }
    

	
	Fl::visual(FL_RGB);
	
	fl_color(0);
    fl_line_style(0);
}

