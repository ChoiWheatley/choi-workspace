/*
 * <PPPUC++> Chapter12 GUI first example
 */

#include "PPP2code/Simple_window.h"      // get access to our window library
#include "PPP2code/Graph.h"              // get access to our graphics library facilities

int main()
{
    using namespace Graph_lib;

    Point tl {100, 100};
    Simple_window win{tl, 600, 400, "Canvas"};
    Polygon poly;

    poly.add(Point{300,200});
    poly.add(Point{350,100});
    poly.add(Point{400,200});

    poly.set_color(Color::red);
    win.attach(poly);
    win.wait_for_button();
}