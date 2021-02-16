/*
 * <FLTK> Drawing Things in FLTK
 */

#include"fltk.h"
#include"Window.h"
#include"Point.h"
#include"Graph.h"
#include"std_lib_facilities.h"

/*
███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████ 
*/
int main(int argc, char** argv)
{
    using namespace Graph_lib;
    Window win{Point{100, 100}, 1080, 720, "helloworld"};
    Rectangle rec{Point{100, 100}, 100, 100};
    rec.set_color(FL_CYAN);
    rec.set_style(Line_style(FL_DASH,5));
    rec.set_fill_color(Color(FL_RED, Color::visible));
    win.attach(rec);

    return Fl::run();
}

