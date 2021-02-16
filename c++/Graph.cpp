#include "Graph.h"

namespace Graph_lib 
{

void Shape::draw() const
{
    Fl_Color oldc = fl_color();
    fl_color(lcolor.as_int());
    fl_line_style(ls.style(), ls.width());
    draw_lines();
    fl_color(oldc);     //reset color to previous and style to default
    fl_line_style(0);
}
void Shape::draw_lines() const
{
    if (color().visibility() && 1 < points.size())
        for (unsigned int i = 1; i < points.size(); i++)
            fl_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
}
void Shape::move(int dx, int dy)
{
    for (unsigned int i = 0; i < points.size(); ++i) {
        points[i].x += dx;
        points[i].y += dy;
    }
}


// graph f(x) for x in [r1:r2) using count line segments with (0, 0) displayed at xy
// x coordinates are scaled by xscale and y coordinates are scaled by yscale
Function::Function(Fct f, double r1, double r2, Point orig, int count, double xscale, double yscale)
{
    if (r2 < r1) swap(r1, r2);
    if (count <= 0) throw std::runtime_error("non positive graphing count");
    double dist = (r2-r1)/count;
    double r = r1;
    double fr = f(r);
    for (int i = 0; i < count; ++i) {
        add(Point(orig.x + int(r*xscale), orig.y - int(fr*yscale)));
		r+=dist;
    }
}


void Rectangle::draw_lines() const 
{
    if (fill_color().visibility() == Color::visible) {
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x, point(0).y, w, h);
        fl_color(color().as_int());
    }
    if (color().visibility()) {
        fl_color(color().as_int());
        fl_rect(point(0).x, point(0).y, w, h);
    }
}


}// namespace Graph_lib
