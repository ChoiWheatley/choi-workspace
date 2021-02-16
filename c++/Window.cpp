#include "Window.h"

namespace Graph_lib
{

Window::Window(int ww, int hh, const string& title)
:Fl_Window(ww,hh,title.c_str()), w(ww), h(hh)
{
	init();
}

Window::Window(Point xy, int ww, int hh, const string& title)
:Fl_Window(xy.x,xy.y,ww,hh,title.c_str()), w(ww), h(hh)
{ 
	init();
}

void Window::attach(Shape& s)
{
    shapes.push_back(&s);
}
void Window::detach(Shape& s)
{
    for (int i = shapes.size(); 0 < i; --i) {
        if (shapes[i-1] == &s)
            shapes.erase(shapes.begin() + (i-1));
    }
}

void Window::init()
{
   resizable(this);
   show();
} 

//---------------------------------------------------- 

void Window::draw()
{
	Fl_Window::draw();
    for (int i = 0; i < shapes.size(); ++i) shapes[i]->draw();
}


}// namespace Graph_lib
